#ifndef DATA_TYPES_H_
#define DATA_TYPES_H_

#include "datablock.h"

extern struct _ParameterLoggingTypeDescription{
	char*		name;
	ParLogType	type;
	size_t		size;
	float64 (*conv2float64)( void *value );
} data_types[];

typedef struct _DataBlocksContainer{
	GPtrArray		*blocks;
	int32			number;			/* data block container number, need for file name */
} DBContainer;

#endif /* DATA_TYPES_H_ */
