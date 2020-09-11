#include <glib.h>
#include <string.h>

#include "unicode.h"

static uint16 br[][2] = {
		{ 0x0A00, 0x0D00 }, /* default BE */
		{ 0x0A00, 0x0D00 }, /* BE */
		{ 0x000A, 0x000D }  /* LE */
};

static char8* utf16[] = { "UTF-16BE", "UTF-16BE", "UTF-16LE" };

const char8* utf16_to_char8bit( UnicodeType type, const uint16 *str, glong len, const char8 *to_codeset,
		gsize *bytes_read, gsize *bytes_written, GError **error)
{
	char8	*res = NULL;
	uint16	*conv = NULL;
	uint16	*p;
	uint32	length = 0;
	int 	rem = 0;
	int		i = 0;

	g_return_val_if_fail (str != NULL, NULL);

	if( type == UT_DEFAULT ){
		if( str[0] != 0 && str[1] == 0 )
			type = UT_LE;
		else
			type = UT_BE;
	}

	if( len < 0 ){
		const uint16 *p = str;
		length = 0;
		while( *p++ != (uint16)0 )
			++length;
	}
	else
		length = len;
	for( i = 0; i < length; ++i )
		if( str[i] == br[type][1] )
			++rem;
	conv = g_new( uint16, length + 1 - rem );
	p = conv;
	for( i = 0; i < length; ++i ){
		if( str[i] == br[type][1] )
			continue;
		*p++ = str[i];
	}
	*p = 0;

//	res = (char8*)g_convert( (gchar*)conv, (length - rem) * sizeof(uint16), "UTF-8",
//			utf16[type], bytes_read, bytes_written, error );
	res = (char8*)g_convert( (gchar*)conv, (length - rem) * sizeof(uint16), to_codeset,
			utf16[type], bytes_read, bytes_written, error );

	g_free( conv );

	return res;
}

const char8* utf16_to_utf8( UnicodeType type, const uint16 *str, glong len,
		gsize *bytes_read, gsize *bytes_written, GError **error)
{
	return utf16_to_char8bit( type, str, len, "UTF-8", bytes_read, bytes_written, error );
}

const uint16 utf16_symbol( UnicodeType type )
{
	if( type == UT_LE )
		return 0xFEFF;
	return 0xFFFE;
}

const UnicodeType utf16_type( uint16 symbol )
{
	if( symbol == (gunichar2)0xFEFF )
		return UT_LE;
	if( symbol == (gunichar2)0xFFFE )
		return UT_BE;
	if( (symbol&0xff) != 0 && (symbol>>8) == 0 )
		return UT_LE;
	return UT_BE;
}


const uint16* char8bit_to_utf16( UnicodeType type, const char8 *str, glong len, const char8 *from_codeset,
		gsize *bytes_read, gsize *bytes_written, GError **error)
{
	uint16	*res = NULL;
	uint16	*conv = NULL;
	uint16	*p;
	uint32	length = 0;
	int 	add = 0;
	int		i = 0;

	g_return_val_if_fail (str != NULL, NULL);

	conv = (uint16*)g_convert( str, len, utf16[type], from_codeset, bytes_read, &length, error );
	length /= sizeof(uint16);
	for( i = 0; i < length; ++i )
		if( conv[i] == br[type][0] )
			++add;
	res = g_new( uint16, length + add + 1 );
	p = res;
	for( i = 0; i < length; ++i ){
		if( conv[i] == br[type][0] )
			*p++ = br[type][1];
		*p++ = conv[i];
	}
	*p = 0;
	if( bytes_written )
		*bytes_written = (length + add) * sizeof(uint16);
	g_free( conv );
	return res;
}

const uint16* utf8_to_utf16( UnicodeType type, const char8 *str, glong len,
		gsize *bytes_read, gsize *bytes_written, GError **error)
{
	return char8bit_to_utf16( type, str, len, "UTF-8", bytes_read, bytes_written, error );
}

/* replace all sub_str in 'src' string by new_str, returned string should be freed by g_free */
char8* utf8_replace_substr_new( const char8 *src, int32 src_len, const char8 *sub_str, const char8 *new_sub_str )
{
	GString		*str;
	const char8	*pos;
	char8		*pos_sub;
	uint32		rem;
	uint32		sub_len;

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

/* the same as above function but return string is constant and should`t be freed */
const char8* utf8_replace_substr( const char8 *src, int32 src_len, const char8 *sub_str, const char8 *new_sub_str )
{
	static char8	*replace_str = NULL;

	char8	*str;

	str = utf8_replace_substr_new( src, src_len, sub_str, new_sub_str );

	g_free( replace_str );

	return replace_str = str;
}
