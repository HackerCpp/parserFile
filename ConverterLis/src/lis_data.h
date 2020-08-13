#ifndef LIS_DATA_H_
#define LIS_DATA_H_

#include <gio/gio.h>

#include "lis.h"

typedef	GByteArray	LisBlock;

EXTERN void lis_block_add_datum( LisBlock *block, char8 repr_code, ... );

EXTERN void lis_block_add_data( LisBlock *block, const void *data, uint32 data_len );

EXTERN void lis_block_add_compon_block( LisBlock *block, uint8 type_number, char8 repr_code, const char8 *mnemonic, const char8 *units, ... );
EXTERN void lis_block_add_compon_block_list( LisBlock *block, const char8 *repr_codes, char8 **mnemonics, ... );

EXTERN void lis_block_add_entry_block( LisBlock *block, uint8 entry_type, char8 repr_code, ... );

EXTERN void copy_int16_and_swap_bytes( int16 *dst, const int16 *src, uint32 n );

EXTERN void str_copy4( char8 *dest, const char8 *src );

typedef enum _TIFSaveType{
	TIF_NOT_USE		= -1,
	TIF_SAVE		= 0,
	TIF_FINISH		= 1
} TIFSave;

EXTERN void lis_block_write_init();

EXTERN void lis_block_write( LisBlock *block, GOutputStream *out, TIFSave tif_save );

#endif /* LIS_DATA_H_ */
