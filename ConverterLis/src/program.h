#ifndef PROGRAM_H_
#define PROGRAM_H_

#include "common.h"

/********************************************************************
***  function for initializing/destroying work with main program ***
********************************************************************/

/* initializing function for obtaining paths to some directories (bin, calibration etc.) */
EXTERN void init_prog_dir_func( GetFunction get_func );

/* initializing program interface for current plug-in, if successful return NULL else return error string */
EXTERN int init_prog_func( GetFunction get_func );
/* freeing program interface for current plug-in */
EXTERN void destroy_prog_func();
/********************************************************************/

/* get pointer to main application window, type - "GTK", "HWND" and so on */
EXTERN void* prog_get_mainwindow_pointer( char8 *type );

/* get pointer to top application window, type - "GTK", "HWND" and so on */
EXTERN void* prog_get_top_window_pointer( char8 *type );

/* return unit scale by name from main program configuration file */
EXTERN float64 prog_rc_get_unit( gchar* name );

/********************************************************************/

/* put string preferences 'data' on path "path1:path2:path..." */
EXTERN void prog_put_pref6s( const char8 *path, const char8 *data );
/* put float64 preferences 'value' on path "path1:path2:path..." */
EXTERN void prog_put_pref6s_float64( const char8 *path, float64 value );
/* put int32 preferences 'value' on path "path1:path2:path..." */
EXTERN void prog_put_pref6s_int32( const char8 *path, int32 value );

/* get string preferences 'data' on path "path1:path2:path..." */
EXTERN const char8* prog_get_pref6s( const char8 *path );
/* get float64 preferences 'value' on path "path1:path2:path...", return TRUE if preference exists */
EXTERN bool32 prog_get_pref6s_float64( const char8 *path, float64 *value );
/* get int32 preferences 'value' on path "path1:path2:path...", return TRUE if preference exists */
EXTERN bool32 prog_get_pref6s_int32( const char8 *path, int32 *value );

/********************************************************************
***  functions showing messages  ***
********************************************************************/
typedef enum{
  PROG_MESSAGE_INFO,
  PROG_MESSAGE_WARNING,
  PROG_MESSAGE_QUESTION,
  PROG_MESSAGE_ERROR,
  PROG_MESSAGE_OTHER
} ProgMessageType;

/* show modal and non-modal message dialog, if 'message_caption' is NULL it's ignored */
void prog_show_message( ProgMessageType type, bool32 is_modal, const char8 *title,
		const char8 *message_caption, const char8 *message_text, ... ) G_GNUC_PRINTF(5, 6);

/* return TRUE if user pressed YES */
bool32 prog_show_yesno_message( const char8 *title, const char8 *message_text, ... ) G_GNUC_PRINTF(2, 3);

/********************************************************************/

/* some transform types for curves names */
#define FULL_LOCAL		"FULL"
#define SHORT_LOCAL		"SHORT"
#define SMALL_LOCAL		"SMALL"
#define LAS_FORM		"LAS"

/* transform input string by type, returned string should by freed by g_free() */
char8*	prog_string_transform( const char8 *string, const char8 *type );

EXTERN float64 prog_strtod( const char8 *nptr, char8 **endptr);

/* searches the string <str> for the first occurrence of string <sub>, return pointer to symbol after found substring */
EXTERN char8* prog_str_find_substr_end( const char8 *str, const char8 *sub );

/* replace all sub_str in 'src' string by new_str, returned string should be freed by g_free */
EXTERN char8* prog_replace_substr_new( const char8 *src, int32 src_len, const char8 *sub_str, const char8 *new_sub_str );

EXTERN const char8* prog_replace_substr( const char8 *src, int32 src_len, const char8 *sub_str, const char8 *new_sub_str );

EXTERN const char8* prog_replace_substr_v( const char8 *src, int32 src_len, ... );

/* the same is 'g_strdup_printf' but return string is constant and should`t be freed */
EXTERN const char8* prog_str_printf( const char8 *format, ... ) G_GNUC_PRINTF(1, 2);

/* return NULL-terminated string list of module's names for current tool's driver */
EXTERN char8** prog_list_module_names();

/* return NULL-terminated string list of numbers for current tool's driver and module's name */
EXTERN char8** prog_list_numbers_by_module_name( const char8 *module_name );

/* set data for current tool's driver, module's name and module's number */
EXTERN void prog_set_module_data( const char8 *module_name, const char8 *number, const char8 *data_name, const void *data, size_t length );
#define prog_set_default_module_data( module_name, data_name, data, length )	prog_set_module_data( module_name, "{}", data_name, data, length )

/* get data for current tool's driver, module's name and module's number, received 'data' should be freed by g_free() */
EXTERN void prog_get_module_data_new( const char8 *module_name, const char8 *number, const char8 *data_name, void **data, size_t *length );

/* get data for current tool's driver, module's name and module's number (or alternative number ), received 'data' should be freed by g_free() */
EXTERN void prog_get_module_data_new_2numbers( const char8 *module_name, const char8 *number, const char8 *default_number,
		const char8 *data_name, void **data, size_t *length );

/* set module property for current tool's driver, module's name and module's number */
EXTERN void prog_set_module_prop( const char8 *module_name, const char8 *number, const char8 *prop_name, const char8 *prop_type, const void *data, size_t length );

/* set integer value module property for current tool's driver, module's name and module's number */
COMMON_INLINE static void prog_set_module_prop_int32( const char8 *module_name, const char8 *number, const char8 *prop_name, int32 value )
{
	prog_set_module_prop( module_name, number, prop_name, "INT32", &value, sizeof(value) );
}
#define prog_set_default_module_prop_int32( module_name, prop_name, value )		prog_set_module_prop_int32( module_name, "{}", prop_name, value )

/* set floating point value module property for current tool's driver, module's name and module's number */
COMMON_INLINE static void prog_set_module_prop_float32( const char8 *module_name, const char8 *number, const char8 *prop_name, float32 value )
{
	prog_set_module_prop( module_name, number, prop_name, "FLOAT32", &value, sizeof(value) );
}
#define prog_set_default_module_prop_float32( module_name, prop_name, value )		prog_set_module_prop_float32( module_name, "{}", prop_name, value )

/* set string module property for current tool's driver, module's name and module's number */
EXTERN void prog_set_module_prop_str( const char8 *module_name, const char8 *number, const char8 *prop_name, const char8 *str );
#define prog_set_default_module_prop_str( module_name, prop_name, str )		prog_set_module_prop_str( module_name, "{}", prop_name, str )

/* get module property for current tool's driver, module's name and module's number, received 'data' should be freed by g_free() */
EXTERN void prog_get_module_prop_new( const char8 *module_name, const char8 *number, const char8 *prop_name, const char8 *prop_type, void **data, size_t *length );

/* return string module property for current tool's driver, module's name and module's number, returned string should be freed by g_free() */
EXTERN char8* prog_get_module_prop_str_new( const char8 *module_name, const char8 *number, const char8 *prop_name );
#define prog_get_default_module_prop_str_new( module_name, prop_name )		prog_get_module_prop_str_new( module_name, "{}", prop_name )

/* return string module property for current tool's driver, module's name and module's number */
EXTERN const char8* prog_get_module_prop_str( const char8 *module_name, const char8 *number, const char8 *prop_name );
#define prog_get_default_module_prop_str( module_name, prop_name )		prog_get_module_prop_str( module_name, "{}", prop_name )

/* get module property for current tool's driver, module's name and module's number, return true if property really read */
EXTERN bool32 prog_get_module_prop( const char8 *module_name, const char8 *number, const char8 *prop_name, const char8 *prop_type, void *buf, size_t buf_size );

/* get integer module property for current tool's driver, module's name and module's number, return true if property really read */
COMMON_INLINE static bool32 prog_get_module_prop_int32( const char8 *module_name, const char8 *number, const char8 *prop_name, int32 *value )
{
	return prog_get_module_prop( module_name, number, prop_name, "INT32", value, sizeof(*value) );
}
#define prog_get_default_module_prop_int32( module_name, prop_name, value )		prog_get_module_prop_int32( module_name, "{}", prop_name, value )

/* get floating point module property for current tool's driver, module's name and module's number, return true if property really read */
COMMON_INLINE static bool32 prog_get_module_prop_float32( const char8 *module_name, const char8 *number, const char8 *prop_name, float32 *value )
{
	return prog_get_module_prop( module_name, number, prop_name, "FLOAT32", value, sizeof(*value) );
}
#define prog_get_default_module_prop_float32( module_name, prop_name, value )		prog_get_module_prop_float32( module_name, "{}", prop_name, value )

#endif /* PROGRAM_H_ */
