#ifndef UTILS_H_
#define UTILS_H_

#include "common.h"

char8* utf16_to_utf8( GUnicodeType type, const uint16 *str, glong len, gsize *bytes_read, gsize *bytes_written, GError **error );

uint16* utf8_to_utf16( GUnicodeType type, const char8 *str, glong len, gsize *bytes_read, gsize *bytes_written, GError **error );

uint16 utf16_symbol( GUnicodeType type );
GUnicodeType utf16_type( uint16 symbol );

/* replace all sub_str in 'src' string by new_str, returned string should be freed by g_free */
char8* str_replace_substr_new( const char8 *src, int32 src_len, const char8 *sub_str, const char8 *new_sub_str );

/* the same as above function but return string is constant and should`t be freed */
const char8* str_replace_substr( const char8 *src, int32 src_len, const char8 *sub_str, const char8 *new_sub_str );

/* replace all substrings in 'src' string by new strings (pairs should be ended by NULL), returned string should be freed by g_free */
char8* str_replace_substr_new_v( const char8 *src, int32 src_len, ... ) G_GNUC_NULL_TERMINATED;

/* replace all substrings in 'src' string by new strings (pairs should be ended by NULL), return string is constant and should`t be freed */
const char8* str_replace_substr_v( const char8 *src, int32 src_len, ... ) G_GNUC_NULL_TERMINATED;

/* create string by 'format' as classical sprintf, return string is constant and should`t be freed */
const char8* sprintf_const( const char8 *format, ... ) G_GNUC_PRINTF(1, 2);

/* remove symbols <delimiters> from <string> in place, return <string> itself, not a copy */
char8* str_remove_delimiter( char8 *string, const char8 *delimiters );

/* searches the string <str> for the first occurrence of string <sub>, return pointer to symbol after found substring */
char8* str_find_substr_end( const char8 *str, const char8 *sub );


void compress_data( const void *in_data, uint32 in_len, void **out_data, uint32 *out_len );

void decompress_data( const void *in_data, uint32 in_len, void **out_data, uint32 *out_len );


/* return UNIX time format: seconds since 1970-01-01 00:00:00 UTC */
time64 get_current_unix_time();

/* return the same as 'g_date_time_new_now_local()', cann't obtain correct TimeZone parameters in Windows OS
 * then return correct date and time but incorrect time zone */
GDateTime* date_time_new_now_local();

/* return the same as 'g_date_time_new_from_unix_local()', cann't obtain correct TimeZone parameters in Windows OS
 * then return correct date and time but incorrect time zone */
GDateTime* date_time_new_from_unix_local( time64 t );

/* return current time zone name */
const char8* get_current_timezone();


void kedrrc_open();
void kedrrc_save();

/* return unit scale by name from kedrrc */
float64 kedrrc_get_unit( const char8 *name );

/* put string preferences 'data' on path "path1:path2:path..." */
void kedrrc_put_pref6s( const char8 *path, const char8 *data );
/* get string preferences 'data' on path "path1:path2:path..." */
const char8* kedrrc_get_pref6s( const char8 *path );

/* put float64 'data' on path "path1:path2:path..." */
void kedrrc_put_pref6s_float64( const char8 *path, float64 data );
/* get float64 'data' on path "path1:path2:path...", return FALSE if path is not exist */
bool32 kedrrc_get_pref6s_float64( const char8 *path, float64 *data );
/* put int32 'data' on path "path1:path2:path..." */
void kedrrc_put_pref6s_int32( const char8 *path, int32 data );
/* get int32 'data' on path "path1:path2:path...", return FALSE if path is not exist */
bool32 kedrrc_get_pref6s_int32( const char8 *path, int32 *data );


void string_transform_init();

/* some transform types for curves names */
#define ORIGINAL_LOCAL	"FULL"
#define SHORT_LOCAL		"SHORT"
#define SMALL_LOCAL		"SMALL"

/* transform input string by type, returned string should by freed by g_free() */
char8*	string_transform( const char8 *string, const char8 *type );

/* extract filename prefix from parameter mnemonic,  returned string should by freed by g_free() */
char8*	string_extract_filename( const char8 *mnem );


#include <libxml/tree.h>

float64	xml_read_value( xmlNodePtr node, const char *prop );
void	xml_write_value( xmlNodePtr node, const char *prop, float64 value );

float64	xml_read_value_unit( xmlNodePtr node, const char *out_unit, float64 default_val, const char *default_unit );
void	xml_write_value_unit( xmlNodePtr node, float64 val, const char *val_unit, const char *out_unit );

void	xml_read_array( xmlNodePtr node, const char8 *prop, uint32 *num_arr, float64 **arr );
void	xml_write_array( xmlNodePtr node, const char8 *prop, uint32 num_arr, const float64 *arr );

void	xml_read_array_int32( xmlNodePtr node, const char8 *prop, uint32 num_arr, int32 *arr );
void	xml_write_array_int32( xmlNodePtr node, const char8 *prop, uint32 num_arr, const int32 *arr );

void	xml_read_rgba( xmlNodePtr node, const char *prop, float64 *red, float64 *green, float64 *blue, float64 *alpha );
void	xml_write_rgba( xmlNodePtr node, const char *prop, float64 red, float64 green, float64 blue, float64 alpha );

void	xml_read_dashes( xmlNodePtr node, uint32 *num_dashes, float64 **dashes );

char8*	xml_dump_node_to_str( xmlNode *node );

#define xml_read_color(NODE,COLOR) \
	xml_read_rgba( NODE, \
			"color", \
			&((COLOR)->red), \
			&((COLOR)->green), \
			&((COLOR)->blue), \
			NULL )

#define xml_read_color_a(NODE,COLOR) \
	xml_read_rgba( NODE, \
			(xmlChar*)"color", \
			&((COLOR)->red), \
			&((COLOR)->green), \
			&((COLOR)->blue), \
			&((COLOR)->alpha) )


typedef struct _cairo_surface cairo_surface_t;
typedef struct _GdkPixbuf GdkPixbuf;
cairo_surface_t* gdk_cairo_surface_create_from_pixbuf( const GdkPixbuf *pixbuf );
cairo_surface_t* gdk_cairo_image_surface_create_from_png_resource( const char *resource_path, GError **error );


typedef struct _GtkWindow              GtkWindow;
typedef enum
{
  SHOW_MESSAGE_INFO,
  SHOW_MESSAGE_WARNING,
  SHOW_MESSAGE_QUESTION,
  SHOW_MESSAGE_ERROR,
  SHOW_MESSAGE_OTHER
} ShowMessageType;

/* show modal and non-modal message dialog, if 'message_caption' is NULL it's ignored */
void show_message_dialog( GtkWindow *parent, ShowMessageType type, bool32 is_modal, const char8 *title,
		const char8 *message_caption, const char8 *message_text, ... ) G_GNUC_PRINTF(6, 7);

/* return TRUE if user pressed YES */
bool32 show_yesno_message_dialog( GtkWindow *parent, const char8 *title, const char8 *message_text, ... ) G_GNUC_PRINTF(3, 4);

/* show input string dialog, if canceled return NULL */
const char8* input_string_dialog( GtkWindow *parent, const char8 *title, const char8 *text, const char8 *default_str );

/* show input double dialog, if canceled return FALSE */
bool32 input_float64_dialog( GtkWindow *parent, const char8 *title, const char8 *text, float64 *data );

/* set default key binding for same widgets (cut/copy clip-board for Russian keys ant so on) */
void set_default_key_binding();


typedef struct _OutputFileStream		OutputFile;

OutputFile*	out_file_new( const char8 *file_name, uint32 buffer_length );
void		out_file_close( OutputFile *of );
uint32		out_file_write( OutputFile *of, const void *data, uint32 length );


void open_file_external( const char8 *file_name, ProgDirLocale locale );

#endif /* UTILS_H_ */
