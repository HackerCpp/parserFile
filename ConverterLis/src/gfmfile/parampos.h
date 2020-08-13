#ifndef PARAMPOS_H_
#define PARAMPOS_H_

#include "basic_types.h"
#include "datablock.h"

typedef struct _ParamPositionDescription ParamPosDesc;

EXTERN ParamPosDesc* ppd_new();
EXTERN void ppd_free( ParamPosDesc *ppd );

EXTERN void ppd_add_info( ParamPosDesc *ppd, char8 *param_name, ParLogType param_type, goffset offset );
EXTERN void ppd_extract( ParamPosDesc *ppd, const void *values, ParamPos *position );

EXTERN bool32 ppd_add_info_NEW_FORMAT( ParamPosDesc *ppd, char8 *param_name, ParLogType param_type, uint32 records_count, const char8 *desc );

#endif /* PARAMPOS_H_ */
