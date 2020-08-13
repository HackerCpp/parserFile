#ifndef DATABLOCK_H_
#define DATABLOCK_H_

#include <gio/gio.h>
#include "common.h"

#define GFM_FILE_SIGNATURE		"GFM\n"
#define GFM_FILE_HEADER			"[HEADER]"
#define GFM_FILE_FORMS			"[FORMS]"
#define GFM_FILE_DATA_BLOCK		"[DATA_BLOCK]"

/* minimal data piece */
typedef struct _ParameterPosition{
	ufixed32_3			time_sec_3;			/* time per milliseconds */
	fixed32_5			depth_m_5;			/* depth per 0.01mm */
} ParamPos;

/* minimal data piece */
typedef struct _ParameterData{
	union{
		float64		value;			/* parameter value */
		uint64		offset;			/* offset from the beginning of GFM file for complex data */
	};
	ParamPos		position;		/* parameter logging position: time, depth and so on */
} ParamData;

typedef enum _ParameterLoggingType{
	LOG_INT8, LOG_UINT8, LOG_INT16, LOG_UINT16, LOG_INT32, LOG_UINT32, LOG_INT64, LOG_UINT64,
	LOG_FIXED32_3, LOG_UFIXED32_3, LOG_FIXED32_4, LOG_UFIXED32_4, LOG_FIXED32_5, LOG_UFIXED32_5,
	LOG_FIXED32_6, LOG_UFIXED32_6, LOG_FIXED32_7, LOG_UFIXED32_7,
	LOG_FLOAT32, LOG_FLOAT64, LOG_TYPES_COUNT
} ParLogType;

typedef struct _ParamArray ParamArray;

typedef enum _ParameterResamplingFlags{
	NEAREST			= 1<<0,			/* use nearest value data on interval */
	INTERPOLATE		= 1<<1,			/* linear interpolation value by 2 nearest values */
	PEAK_VALUE		= 1<<2,			/* use peak parameter's value on interval */
	AVERAGE			= 1<<3,			/* use average parameter's value on interval */
	MAGNETIC_MARK	= 1<<4,			/* parameter is magnetic mark */
	SUMMARIZE		= 1<<5,

	SELECTED		= 0xFFFFFFFF	/* selected mask, parameter should be exported */
} ResamplFlg;

typedef struct _ParameterDescription{
	char8			*entmnem;		/* entire line mnemonic */
	fixed32_5		mp_m_5;			/* measure point per 0.01mm */

	char8			*desc;			/* parameter description string */

	ParLogType		type;			/* type in logging vector data */
	uint32			count;			/* count of elements in logging vector data */
	uint64			offset;			/* offset in logging vector data (use in reading procedure) */
	gboolean		no_lis;
	ResamplFlg		flags;			/* parameter export flags */

	ParamArray		*parr;			/* array of ParamData */
} ParamDesc;

typedef struct _DataBlock DataBlock;

EXTERN GPtrArray*	data_blocks;

EXTERN GPtrArray*	params;

void data_block_new_read_from_file( uint16 symbol, uint32 data_block_size, GInputStream *in );

/* return null terminated array of ParamDesc */
EXTERN const ParamDesc** data_block_get_paramdesc_array( DataBlock *db );

EXTERN void data_blocks_free();

/* return 0 if data blocks is empty other non zero */
EXTERN int32 data_block_get_start_stop( fixed32_5 *start_m_5, fixed32_5 *stop_m_5, ufixed32_3 *end_time_sec_3 );

EXTERN const char8* data_blocks_get_calibration_str();

/*** interface of ParamArray ***/
/* depth slice direction for parr_depth_slice function */
typedef enum _DepthSliceDirection{ DS_UP = -1, DS_UNKNOWN = 0, DS_DOWN = 1 } DSDirection;

/* monotonous depth slice; begin, end indexes for ParamArray */
typedef struct _DepthSlice{
	size_t			begin;
	size_t			end;
	DSDirection		dir;
} DepthSlice;

EXTERN ParamArray*	parr_create();
EXTERN void		parr_clear( ParamArray *parr );
EXTERN void		parr_destroy( ParamArray *parr );
EXTERN void		parr_dup_data( const ParamArray *src, ParamArray *dest );

EXTERN size_t	parr_add_data( ParamArray *parr, ParamData data );

/* size of continue ParamPoint's array, can use for ParamPoint access optimization */
#define POINT_CONTINUE_SIZE	256
EXTERN ParamData*	parr_get_data( ParamArray *parr, size_t index );
EXTERN ParamData*	parr_get_last_data( ParamArray *parr );

EXTERN size_t	parr_param_count( ParamArray *parr );

EXTERN size_t	parr_depth_slice( ParamArray *parr, fixed32_5 begin_m_5, fixed32_5 end_m_5, DepthSlice **arr );
EXTERN void		parr_time_slice( ParamArray *parr, ufixed32_3 begin_sec_3, ufixed32_3 end_sec_3, size_t *ib, size_t *ie );

EXTERN void		parr_get_depth_interval( ParamArray *parr, fixed32_5 *top_m_5, fixed32_5 *bottom_m_5, DSDirection *dir );

EXTERN void		parr_remove_depth_overlap( ParamArray *parr );

#endif /* DATABLOCK_H_ */
