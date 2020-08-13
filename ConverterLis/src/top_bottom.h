#ifndef TOP_BOTTOM_H_
#define TOP_BOTTOM_H_

#include "datablock.h"

enum
{
  COLUMN_CHECKED,
  COLUMN_MNEMONIC,
  COLUMN_COMMENT,
  COLUMN_DESC_POINTER,
  NUM_COLUMNS
};

typedef struct _ExportMode{
	fixed32_5		start_m_5;
	fixed32_5		stop_m_5;
	fixed32_5		step_m_5;
	ufixed32_3		begin_sec_3;
	ufixed32_3		end_sec_3;
	ufixed32_3		step_sec_3;
	bool32			is_time_mode;
} ExportMode;

EXTERN bool32 top_bottom_run( ExportMode *mode );
EXTERN bool32 run();

EXTERN bool32 is_tif_block;

EXTERN float64 invalid_value;

#endif /* TOP_BOTTOM_H_ */
