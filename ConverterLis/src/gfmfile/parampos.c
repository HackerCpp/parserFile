#include <glib.h>

#include "parampos.h"
#include "data_types.h"
#include <program_h>

struct _ParamPositionDescription{
	ParLogType	time_type;
	size_t		time_offset;
	float64		time_scale;

	ParLogType	depth_type;
	size_t		depth_offset;
	float64		depth_scale;
};

EXTERN ParamPosDesc* ppd_new()
{
	return g_new0( ParamPosDesc, 1 );
}

EXTERN void ppd_free( ParamPosDesc *ppd )
{
	g_free( ppd );
}

EXTERN void ppd_add_info( ParamPosDesc *ppd, char8 *param_name, ParLogType param_type, goffset offset )
{
	g_return_if_fail( ppd != NULL );

	if( g_str_has_suffix( param_name, ")" ) == TRUE ){
		if( g_str_has_prefix( param_name, "TIME" ) == TRUE ){
			ppd->time_scale = prog_rc_get_unit( param_name + 4 ) / prog_rc_get_unit( "MSEC" );
			ppd->time_type = param_type;
			ppd->time_offset = offset;
		}
		else if( g_str_has_prefix( param_name, "DEPTH" ) == TRUE ){
			ppd->depth_scale = prog_rc_get_unit( param_name + 5 ) / prog_rc_get_unit( "M" ) * 1e+5;
			ppd->depth_type = param_type;
			ppd->depth_offset = offset;
		}
	}
	else{
		if( g_str_has_prefix( param_name, "TIME" ) == TRUE ){
			ppd->time_scale = prog_rc_get_unit( param_name + 5 ) / prog_rc_get_unit( "MSEC" );
			ppd->time_type = param_type;
			ppd->time_offset = offset;
		}
		else if( g_str_has_prefix( param_name, "DEPTH" ) == TRUE ){
			ppd->depth_scale = prog_rc_get_unit( param_name + 6 ) / prog_rc_get_unit( "M" ) * 1e+5;
			ppd->depth_type = param_type;
			ppd->depth_offset = offset;
		}
	}
}

EXTERN void ppd_extract( ParamPosDesc *ppd, const void *values, ParamPos *position )
{
	if( ppd->depth_scale != 0 ){
		position->depth_m_5 = data_types[ppd->depth_type].conv2float64( (int8*)values + ppd->depth_offset ) *
				ppd->depth_scale;
	}
	if( ppd->time_scale != 0 ){
		position->time_sec_3 = data_types[ppd->time_type].conv2float64( (int8*)values + ppd->time_offset ) *
				ppd->time_scale;
	}
}

EXTERN bool32 ppd_add_info_NEW_FORMAT( ParamPosDesc *ppd, char8 *param_name, ParLogType param_type, uint32 records_count, const char8 *desc )
{
    char8   *pos, *end;
    float64 resolution, counts, length;

    resolution = 1.0;
    pos = strstr( desc, "resolution" );
    if( pos != NULL ){
        pos = strstr( pos, "\"" );
        if( pos != NULL ){
            resolution = prog_strtod( pos + 1, NULL );
            if( resolution == 0 )
                resolution = 1.0;
        }
    }

    if( g_str_has_prefix( param_name, "TIME" ) == TRUE ){
        ppd->time_scale = prog_rc_get_unit( param_name + 4 ) / prog_rc_get_unit( "MSEC" ) * resolution;
        ppd->time_type = param_type;
        ppd->time_offset = 0;

        return TRUE;
    }

    if( g_str_has_prefix( param_name, "DEPTH" ) == TRUE ){
        ppd->depth_scale = resolution;
        ppd->depth_type = param_type;
        ppd->depth_offset = data_types[ppd->time_type].size * records_count;

        counts = 0;
        length = 0;
        /* read depth calibration */
        pos = strstr( desc, "<calibration" );
        g_return_val_if_fail( pos != NULL, TRUE );

        counts = prog_strtod( prog_str_find_substr_end( pos, "counts=\"" ), NULL );
        length = prog_strtod( prog_str_find_substr_end( pos, "length=\"" ), NULL );
        pos = prog_str_find_substr_end( pos, "unit=\"" );
        if( pos != NULL ){
            end = strstr( pos, "\"" );
            if( end == NULL )
                pos = NULL;
            else
                pos = g_strndup( pos, end - pos );
        }

        if( counts != 0.0 && length != 0.0 && pos != NULL )
            ppd->depth_scale *= length / counts * prog_rc_get_unit( pos ) / prog_rc_get_unit( "M" ) * 1e+5;

        return TRUE;
    }

    return FALSE;
}
