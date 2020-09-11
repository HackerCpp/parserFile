#include <gtk/gtk.h>
#include <string.h>
#include "basic_types.h"
#include "units_scale.h"
#include "string-transform.h"
#include "common.h"

/*** return function addresses by name ***/
void* get_function( const char* name )
{
    if( strcmp( name, "prog_dir" ) == 0 )
        return &prog_dir;

	if( strcmp( name, "rc_get_unit_func" ) == 0 )
		return &gfm_units_get_scale;

	if( strcmp( name, "prog_string_transform" ) == 0 )
		return &string_transform;

	g_printerr( "\n Function '%s' not found", name );
	g_warn_if_reached();

	return NULL;

}

