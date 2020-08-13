#include <gtk/gtk.h>

#include "common.h"
#include "program.h"

typedef uint32	ToolDriverID;

static ToolDriverID	tool_id = 0;

/*** function prog_dir return PATH from main program launch directory ***/
typedef char8* (*ProgDirFunc)( const char8*, const char8*, ProgDirLocale );
static ProgDirFunc prog_dir_func = NULL;
static GPtrArray	*parr_printf_str = NULL;
static char8		*prop_str = NULL;
static char8		*replace_str = NULL;

/* get pointer to main application window, type - "GTK", "HWND" and so on */
typedef void* (*ProgGetMainwindowPointer)( char8 *type );

static ProgGetMainwindowPointer	prog_get_mainwindow_pointer_func = NULL;
static ProgGetMainwindowPointer	prog_get_top_window_pointer_func = NULL;

/* return unit scale by name from main program configuration file */
typedef float64 (*ProgRcGetUnit)( gchar* name );
static ProgRcGetUnit prog_rc_get_unit_func = NULL;

typedef void (*ProgPutPref6s)( const char8 *path, const char8 *data );
typedef const char8* (*ProgGetPref6s)( const char8 *path );
static ProgPutPref6s			put_pref6s_func = NULL;
static ProgGetPref6s			get_pref6s_func = NULL;

/* transform input string by type, returned string should by freed by g_free() */
typedef char8*	(*ProgStringTransform)( const char8 *string, const char8 *type );
static ProgStringTransform	prog_string_transform_func = NULL;

typedef ToolDriverID (*ToolDriverIdByName)( const char8 *tool_driver_name );
typedef char8** (*ListModuleNamesByDriverId)( ToolDriverID id );
typedef char8** (*ListNumbersByModuleName)( ToolDriverID id, const char8 *module_name );
typedef void (*SetModuleData)( ToolDriverID id, const char8 *module_name, const char8 *number, const char8 *data_name, const void *data, size_t length );
typedef void (*GetModuleData)( ToolDriverID id, const char8 *module_name, const char8 *number, const char8 *data_name, void **data, size_t *length );
typedef void (*CalibrationRun)( ToolDriverID id );
typedef void (*SetModuleProp)( ToolDriverID id, const char8 *module_name, const char8 *number, const char8 *prop_name, const char8 *prop_type, const void *data, size_t length );
typedef void (*GetModuleProp)( ToolDriverID id, const char8 *module_name, const char8 *number, const char8 *prop_name, const char8 *prop_type, void **data, size_t *length );

static ToolDriverIdByName tool_driver_id_by_name_func = NULL;
static ListModuleNamesByDriverId list_module_names_by_driver_id_func = NULL;
static ListNumbersByModuleName list_numbers_by_module_name_func = NULL;
static SetModuleData set_module_data_func = NULL;
static GetModuleData get_module_data_func = NULL;
static CalibrationRun calibration_run_func = NULL;
static SetModuleProp set_module_prop_func = NULL;
static GetModuleProp get_module_prop_func = NULL;

static bool32 prepare_tool_id()
{
	if( tool_id != 0 )
		return TRUE;

	g_return_val_if_fail( tool_driver_id_by_name_func != NULL, FALSE );
	tool_id = tool_driver_id_by_name_func( PACKAGE );

	return tool_id != 0;
}

EXTERN void init_prog_dir_func( GetFunction get_func )
{
	prog_dir_func = (ProgDirFunc)get_func( "prog_dir" );
	g_warn_if_fail( prog_dir_func != NULL );
}

EXTERN int init_prog_func( GetFunction get_func )
{
	if( prog_dir_func == NULL )
		init_prog_dir_func( get_func );

	prog_get_mainwindow_pointer_func = (ProgGetMainwindowPointer)get_func( "get_mainwindow_func" );
	g_warn_if_fail( prog_get_mainwindow_pointer_func != NULL );
	prog_get_top_window_pointer_func = (ProgGetMainwindowPointer)get_func( "get_top_window_func" );
	g_warn_if_fail( prog_get_top_window_pointer_func != NULL );

	prog_rc_get_unit_func = (ProgRcGetUnit)get_func( "rc_get_unit_func" );
	g_warn_if_fail( prog_rc_get_unit_func != NULL );
	put_pref6s_func = (ProgPutPref6s)get_func( "prog_put_pref6s" );
	g_warn_if_fail( put_pref6s_func != NULL );
	get_pref6s_func = (ProgGetPref6s)get_func( "prog_get_pref6s" );
	g_warn_if_fail( get_pref6s_func != NULL );

	prog_string_transform_func = (ProgStringTransform)get_func( "prog_string_transform" );
	g_warn_if_fail( prog_string_transform_func != NULL );

	tool_driver_id_by_name_func = (ToolDriverIdByName)get_func( "prog_tool_driver_id_by_name" );
	g_warn_if_fail( tool_driver_id_by_name_func != NULL );
	list_module_names_by_driver_id_func = (ListModuleNamesByDriverId)get_func( "prog_list_module_names_by_driver_id" );
	g_warn_if_fail( list_module_names_by_driver_id_func != NULL );
	list_numbers_by_module_name_func = (ListNumbersByModuleName)get_func( "prog_list_numbers_by_module_name" );
	g_warn_if_fail( list_numbers_by_module_name_func != NULL );
	set_module_data_func = (SetModuleData)get_func( "prog_set_module_data" );
	g_warn_if_fail( set_module_data_func != NULL );
	get_module_data_func = (GetModuleData)get_func( "prog_get_module_data" );
	g_warn_if_fail( get_module_data_func != NULL );
	calibration_run_func = (CalibrationRun)get_func( "prog_calibration_run" );
	g_warn_if_fail( calibration_run_func != NULL );
	set_module_prop_func = (SetModuleProp)get_func( "prog_set_module_prop" );
	g_warn_if_fail( set_module_prop_func != NULL );
	get_module_prop_func = (GetModuleProp)get_func( "prog_get_module_prop" );
	g_warn_if_fail( get_module_prop_func != NULL );

	return 0;
}

EXTERN void destroy_prog_func()
{
	if( replace_str != NULL )
		g_free( replace_str );
	replace_str = NULL;

	if( parr_printf_str != NULL )
		g_ptr_array_free( parr_printf_str, TRUE );
	parr_printf_str = NULL;

	if( prop_str != NULL )
			g_free( prop_str );
		prop_str = NULL;
}

EXTERN char* prog_dir( const char8 *path, const char8 *file, ProgDirLocale locale )
{
	static char *buf = NULL;

	if( prog_dir_func )
		return prog_dir_func( path, file, locale );

	g_free( buf );
	buf = g_strdup_printf( "./%s/%s", path, file );
	return buf;
}

/* get pointer to main application window, type - "GTK", "HWND" and so on */
EXTERN void* prog_get_mainwindow_pointer( char8 *type )
{
	g_return_val_if_fail( prog_get_mainwindow_pointer_func != NULL, NULL );

	return prog_get_mainwindow_pointer_func( type );
}

/* get pointer to top application window, type - "GTK", "HWND" and so on */
EXTERN void* prog_get_top_window_pointer( char8 *type )
{
	g_return_val_if_fail( prog_get_top_window_pointer_func != NULL, NULL );

	return prog_get_top_window_pointer_func( type );
}

/* return unit scale by name from main program configuration file */
EXTERN float64 prog_rc_get_unit( gchar* name )
{
	g_return_val_if_fail( prog_rc_get_unit_func != NULL, 1.0 );

	return prog_rc_get_unit_func( name );
}

/* put string preferences 'data' on path "path1:path2:path..." */
EXTERN void prog_put_pref6s( const char8 *path, const char8 *data )
{
	gchar	*full;

	g_return_if_fail( put_pref6s_func != NULL );

	full = g_strconcat( DIR_SUFFIX ":" PACKAGE ":", path, NULL );
	put_pref6s_func( full, data );
	g_free( full );
}

/* put float64 preferences 'value' on path "path1:path2:path..." */
EXTERN void prog_put_pref6s_float64( const char8 *path, float64 value )
{
	char8	*str;

	str = g_strdup_printf( "%g", value );
	prog_put_pref6s( path, str );
	g_free( str );
}

/* put int32 preferences 'value' on path "path1:path2:path..." */
EXTERN void prog_put_pref6s_int32( const char8 *path, int32 value )
{
	char8	*str;

	str = g_strdup_printf( "%d", value );
	prog_put_pref6s( path, str );
	g_free( str );
}

/* get string preferences 'data' on path "path1:path2:path..." */
EXTERN const char8* prog_get_pref6s( const char8 *path )
{
	gchar		*full;
	const gchar	*res;

	g_return_val_if_fail( get_pref6s_func != NULL, NULL );

	full = g_strconcat( DIR_SUFFIX ":" PACKAGE ":", path, NULL );
	res = get_pref6s_func( full );
	g_free( full );
	return res;
}

/* get float64 preferences 'value' on path "path1:path2:path...", return TRUE if preference exists */
EXTERN bool32 prog_get_pref6s_float64( const char8 *path, float64 *value )
{
	const char8		*str;

	g_return_val_if_fail( value != NULL, FALSE );

	str = prog_get_pref6s( path );
	g_return_val_if_fail( str != NULL, FALSE );

	*value = prog_strtod( str, NULL );

	return TRUE;
}

/* get int32 preferences 'value' on path "path1:path2:path...", return TRUE if preference exists */
EXTERN bool32 prog_get_pref6s_int32( const char8 *path, int32 *value )
{
	const char8		*str;

	g_return_val_if_fail( value != NULL, FALSE );

	str = prog_get_pref6s( path );
	g_return_val_if_fail( str != NULL, FALSE );

	*value = prog_strtod( str, NULL );

	return TRUE;
}

static void show_message_internal( ProgMessageType type, bool32 is_modal, const char8 *title, const char8 *message_caption, const char8 *message_full )
{
	GtkWidget	*dialog;

	if( message_caption == NULL ){
		dialog = gtk_message_dialog_new( GTK_WINDOW(prog_get_top_window_pointer("GTK")), GTK_DIALOG_DESTROY_WITH_PARENT, type, GTK_BUTTONS_OK, message_full );
	}
	else{
		dialog = gtk_message_dialog_new( GTK_WINDOW(prog_get_top_window_pointer("GTK")), GTK_DIALOG_DESTROY_WITH_PARENT, type, GTK_BUTTONS_OK, message_caption );
		gtk_message_dialog_format_secondary_markup( GTK_MESSAGE_DIALOG(dialog), message_full );
	}

	gtk_window_set_title( GTK_WINDOW(dialog), title );

	if( is_modal == TRUE ){
		gtk_dialog_run( GTK_DIALOG(dialog) );
		gtk_widget_destroy( dialog );
	}
	else{
		g_signal_connect_swapped( dialog, "response", G_CALLBACK(gtk_widget_destroy), dialog );
		gtk_widget_show_all( dialog );
	}
}

typedef struct _ShowMessageData{
	ProgMessageType		type;
	char8				*title;
	char8				*message_caption;
	char8				*message_full;
} MesData;

static gboolean show_message_data( MesData *data )
{
	g_return_val_if_fail( data != NULL, FALSE );

	show_message_internal( data->type, FALSE, data->title, data->message_caption, data->message_full );
	g_free( data->title );
	g_free( data->message_caption );
	g_free( data->message_full );
	g_free( data );
	return FALSE;
}

/* show modal and non-modal message dialog, if 'message_caption' is NULL it's ignored */
void prog_show_message( ProgMessageType type, bool32 is_modal, const char8 *title, const char8 *message_caption, const char8 *message_text, ... )
{
	char8		*message_full;
	va_list		args;
	MesData		*data;

	va_start( args, message_text );
	message_full = g_strdup_vprintf( message_text, args );
	va_end( args );

	if( g_main_context_is_owner( g_main_context_default()) == TRUE ){
		show_message_internal( type, is_modal, title, message_caption, message_full );
		g_free( message_full );
		return;
	}

	data = g_new( MesData, 1 );
	data->type = type;
	data->title = g_strdup( title );
	data->message_caption = g_strdup( message_caption );
	data->message_full = message_full;

	g_main_context_invoke( NULL, (GSourceFunc)show_message_data, data );
}

/* return TRUE if user pressed YES */
bool32 prog_show_yesno_message( const char8 *title, const char8 *message_text, ... )
{
	GtkWidget	*dialog;
	char8		*message_full;
	va_list		args;
	bool32		res;

	va_start( args, message_text );
	message_full = g_strdup_vprintf( message_text, args );
	va_end( args );

	dialog = gtk_message_dialog_new( GTK_WINDOW(prog_get_top_window_pointer("GTK")), GTK_DIALOG_MODAL, GTK_MESSAGE_QUESTION, GTK_BUTTONS_YES_NO, message_full );
	gtk_window_set_title( GTK_WINDOW(dialog), title );
	g_free( message_full );

	res = gtk_dialog_run( GTK_DIALOG(dialog) ) == GTK_RESPONSE_YES;

	gtk_widget_destroy( dialog );
	return res;
}

/* transform input string by type, returned string should by freed by g_free() */
char8*	prog_string_transform( const char8 *string, const char8 *type )
{
	g_return_val_if_fail( prog_string_transform_func != NULL, g_strdup(string) );

	return prog_string_transform_func( string, type );
}

EXTERN float64 prog_strtod( const char8 *nptr, char8 **endptr)
{
	float64	val;
	char8	*end;
	char8	*copy;
	float64	val_copy;
	char8	*end_copy;

	g_return_val_if_fail( nptr != NULL, 0 );

	val = g_strtod( nptr, &end );
	if( end[0] == ',' ){
		copy = g_strdup( nptr );
		copy[end - nptr] = '.';
		val_copy = g_strtod( copy, &end_copy );
		if( (end_copy - copy) > (end - nptr) ){
			val = val_copy;
			end = (char8*)nptr + (end_copy - copy);
		}
		g_free( copy );
	}
	if( endptr != NULL )
		*endptr = end;

	return val;
}

/* searches the string <str> for the first occurrence of string <sub>, return pointer to symbol after found substring */
EXTERN char8* prog_str_find_substr_end( const char8 *str, const char8 *sub )
{
    const char8 *ptr;
    const char8 *end;
    const char8 *p;
    const char8 *s;
    uint32      str_len;
    uint32      sub_len;

    g_return_val_if_fail( str != NULL, NULL );
    g_return_val_if_fail( sub != NULL, NULL );

    str_len = strlen( str );
    sub_len = strlen( sub );

    if( sub_len == 0 )
        return (char8*)str;

    if( str_len < sub_len )
        return NULL;

    ptr = str;
    end = str + str_len - sub_len;

    while( ptr <= end ){
        p = ptr;
        for( s = sub; *s; ++s, ++p )
            if( *p != *s )
                break;
        if( !*s )
            return (char8*)p;
        ++ptr;
    }

    return NULL;
}

/* replace all sub_str in 'src' string by new_str, returned string should be freed by g_free */
EXTERN char8* prog_replace_substr_new( const char8 *src, int32 src_len, const char8 *sub_str, const char8 *new_sub_str )
{
	GString		*str;
	const char8	*pos;
	char8		*pos_sub;
	uint32		rem;
	uint32		sub_len;

	g_return_val_if_fail( src != NULL, NULL );
	g_return_val_if_fail( sub_str != NULL, NULL );
	g_return_val_if_fail( new_sub_str != NULL, NULL );

	str = g_string_new( NULL );
	pos = src;
	if( src_len != -1 )
		rem = src_len;
	else
		rem = strlen( src );
	sub_len = strlen( sub_str );

	while( ( pos_sub = g_strstr_len( pos, rem, sub_str ) ) != NULL ){
		g_string_append_len( str, pos, pos_sub - pos );
		g_string_append( str, new_sub_str );
		pos_sub += sub_len;
		rem -= pos_sub - pos;
		pos = pos_sub;
	}
	g_string_append_len( str, pos, rem );

	return g_string_free( str, FALSE );
}

static char8* replace_substr_new_v_internal( const char8 *src, int32 src_len, va_list args )
{
	char8		*sub_str, *new_sub_str;
	char8		*str, *tmp;

	g_return_val_if_fail( src != NULL, NULL );

	str = g_strdup( src );

	sub_str = va_arg( args, char8* );
	while( sub_str != NULL ){
		new_sub_str = va_arg( args, char8* );
		if( new_sub_str == NULL ){
			g_printerr( "\n error '%s' has no pair to replace", sub_str );
			g_warn_if_reached();
			break;
		}

		tmp = prog_replace_substr_new( str, src_len, sub_str, new_sub_str );
		g_free( str );
		src_len = -1;
		str = tmp;

		sub_str = va_arg (args, gchar*);
	}

	return str;
}
/* replace all sub_str in 'src' string by new_str, return string is constant and should`t be freed */
EXTERN const char8* prog_replace_substr( const char8 *src, int32 src_len, const char8 *sub_str, const char8 *new_sub_str )
{
	char8	*str;

	str = prog_replace_substr_new( src, src_len, sub_str, new_sub_str );

	if( str == NULL )
		return NULL;

	if( replace_str != NULL )
		g_free( replace_str );

	return replace_str = str;
}

/* replace all substrings in 'src' string by new strings (pairs should be ended by NULL), return string is constant and should`t be freed */
EXTERN const char8* prog_replace_substr_v( const char8 *src, int32 src_len, ... )
{
	va_list		args;
	char8		*str;

	g_return_val_if_fail( src != NULL, NULL );

	va_start( args, src_len );
	str = replace_substr_new_v_internal( src, src_len, args );
	va_end (args);

	if( str == NULL )
		return NULL;

	if( replace_str != NULL )
		g_free( replace_str );

	return replace_str = str;
}

/* the same is 'g_strdup_printf' but return string is constant and should`t be freed */
EXTERN const char8* prog_str_printf( const char8 *format, ... )
{
	va_list		args;
	char8		*str;

	g_return_val_if_fail( format != NULL, NULL );

	va_start( args, format );
	str = g_strdup_vprintf( format, args );
	va_end (args);

	if( str == NULL )
		return NULL;

	if( parr_printf_str == NULL )
		parr_printf_str = g_ptr_array_new_with_free_func( g_free );

	g_ptr_array_add( parr_printf_str, str );

	return str;
}

/* return NULL-terminated string list of module's names for current tool's driver */
EXTERN char8** prog_list_module_names()
{
	g_return_val_if_fail( prepare_tool_id() == TRUE, NULL );
	g_return_val_if_fail( list_module_names_by_driver_id_func != NULL, NULL );

	return list_module_names_by_driver_id_func( tool_id );
}

/* return NULL-terminated string list of numbers for current tool's driver and module's name */
EXTERN char8** prog_list_numbers_by_module_name( const char8 *module_name )
{
	g_return_val_if_fail( prepare_tool_id() == TRUE, NULL );
	g_return_val_if_fail( list_module_names_by_driver_id_func != NULL, NULL );

	return list_numbers_by_module_name_func( tool_id, module_name );
}

/* set data for current tool's driver, module's name and module's number */
EXTERN void prog_set_module_data( const char8 *module_name, const char8 *number, const char8 *data_name, const void *data, size_t length )
{
	g_return_if_fail( prepare_tool_id() == TRUE );
	g_return_if_fail( set_module_data_func != NULL );

	set_module_data_func( tool_id, module_name, number, data_name, data, length );
}

/* get data for current tool's driver, module's name and module's number, received 'data' should be freed by g_free() */
EXTERN void prog_get_module_data_new( const char8 *module_name, const char8 *number, const char8 *data_name, void **data, size_t *length )
{
	g_return_if_fail( prepare_tool_id() == TRUE );
	g_return_if_fail( get_module_data_func != NULL );

	get_module_data_func( tool_id, module_name, number, data_name, data, length );
}

/* get data for current tool's driver, module's name and module's number (or alternative number ), received 'data' should be freed by g_free() */
EXTERN void prog_get_module_data_new_2numbers( const char8 *module_name, const char8 *number, const char8 *default_number,
		const char8 *data_name, void **data, size_t *length )
{
	char8		*str;

	g_return_if_fail( data != NULL && length != NULL );
	g_return_if_fail( prepare_tool_id() == TRUE );
	g_return_if_fail( get_module_data_func != NULL );

	get_module_data_func( tool_id, module_name, number, data_name, data, length );

	if( *data == NULL || *length == 0 )
		get_module_data_func( tool_id, module_name, default_number, data_name, data, length );

	if( *data == NULL || *length == 0 )
		return;

	if( strstr( *data, "{{CurrentNum}}" ) == NULL )
		return;

	/* replace '{{CurrentNum}}' on real 'number' from function call */
	str = prog_replace_substr_new( *data, *length, "{{CurrentNum}}", number );

	g_free( *data );

	*length = strlen( str );
	*data = str;
}

/* set module property for current tool's driver, module's name and module's number */
EXTERN void prog_set_module_prop( const char8 *module_name, const char8 *number, const char8 *prop_name, const char8 *prop_type, const void *data, size_t length )
{
	g_return_if_fail( prepare_tool_id() == TRUE );
	g_return_if_fail( set_module_prop_func != NULL );

	set_module_prop_func( tool_id, module_name, number, prop_name, prop_type, data, length );
}

/* set string module property for current tool's driver, module's name and module's number */
EXTERN void prog_set_module_prop_str( const char8 *module_name, const char8 *number, const char8 *prop_name, const char8 *str )
{
	g_return_if_fail( str != NULL );

	prog_set_module_prop( module_name, number, prop_name, "STRING", str, strlen(str) + 1 );
}

/* get module property for current tool's driver, module's name and module's number, received 'data' should be freed by g_free() */
EXTERN void prog_get_module_prop_new( const char8 *module_name, const char8 *number, const char8 *prop_name, const char8 *prop_type, void **data, size_t *length )
{
	g_return_if_fail( prepare_tool_id() == TRUE );
	g_return_if_fail( get_module_prop_func != NULL );

	get_module_prop_func( tool_id, module_name, number, prop_name, prop_type, data, length );
}

/* return string module property for current tool's driver, module's name and module's number, returned string should be freed by g_free() */
EXTERN char8* prog_get_module_prop_str_new( const char8 *module_name, const char8 *number, const char8 *prop_name )
{
	char8	*str;
	size_t	length;

	g_return_val_if_fail( prepare_tool_id() == TRUE, NULL );
	g_return_val_if_fail( get_module_prop_func != NULL, NULL );

	get_module_prop_func( tool_id, module_name, number, prop_name, "STRING", (void**)&str, &length );

	if( str == NULL )
		return NULL;

	if( str[length - 1] != 0 ){
		str[length - 1] = 0;
		g_warn_if_reached();
	}

	return str;
}

/* return string module property for current tool's driver, module's name and module's number */
EXTERN const char8* prog_get_module_prop_str( const char8 *module_name, const char8 *number, const char8 *prop_name )
{
	if( prop_str != NULL )
		g_free( prop_str );

	return prop_str = prog_get_module_prop_str_new( module_name, number, prop_name );
}

/* get module property for current tool's driver, module's name and module's number, return true if property really read */
EXTERN bool32 prog_get_module_prop( const char8 *module_name, const char8 *number, const char8 *prop_name, const char8 *prop_type, void *buf, size_t buf_size )
{
	void	*data;
	size_t	length;

	g_return_val_if_fail( prepare_tool_id() == TRUE, FALSE );
	g_return_val_if_fail( get_module_prop_func != NULL, FALSE );

	get_module_prop_func( tool_id, module_name, number, prop_name, prop_type, &data, &length );

	g_return_val_if_fail( data != NULL, FALSE );

	if( buf != NULL )
		memcpy( buf, data, MIN(buf_size, length) );

	g_free(data);

	return TRUE;
}
