#ifndef COMPRESS_H_
#define COMPRESS_H_

#include "common.h"

void compress_data( const void *in_data, uint32 in_len, void **out_data, uint32 *out_len );

void decompress_data( const void *in_data, uint32 in_len, void **out_data, uint32 *out_len );


#endif /* COMPRESS_H_ */
