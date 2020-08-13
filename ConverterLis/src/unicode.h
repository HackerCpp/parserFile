#ifndef UNICODE_H_
#define UNICODE_H_

#include "common.h"

/* types for converters UTF-16 <-> UTF-8 */
typedef enum{
	UT_DEFAULT = 0,
	UT_BE,
	UT_LE
} UnicodeType;

EXTERN char8* utf16_to_char8bit( UnicodeType type, const uint16 *str, glong len, const char8 *to_codeset,
		gsize *bytes_read, gsize *bytes_written, GError **error);

EXTERN char8* utf16_to_utf8( UnicodeType type, const uint16 *str, glong len,
		gsize *bytes_read, gsize *bytes_written, GError **error);

EXTERN uint16* char8bit_to_utf16( UnicodeType type, const char8 *str, glong len, const char8 *from_codeset,
		gsize *bytes_read, gsize *bytes_written, GError **error);

EXTERN uint16* utf8_to_utf16( UnicodeType type, const char8 *str, glong len,
		gsize *bytes_read, gsize *bytes_written, GError **error);

EXTERN uint16 utf16_symbol( UnicodeType type );
EXTERN UnicodeType utf16_type( uint16 symbol );

/* replace all sub_str in 'src' string by new_str, returned string should be freed by g_free */
char8* utf8_replace_substr_new( const char8 *src, int32 src_len, const char8 *sub_str, const char8 *new_sub_str );

/* the same as above function but return string is constant and should`t be freed */
const char8* utf8_replace_substr( const char8 *src, int32 src_len, const char8 *sub_str, const char8 *new_sub_str );

#endif /* UNICODE_H_ */
