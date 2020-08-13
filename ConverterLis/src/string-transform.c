#include <glib/gstdio.h>

#include "unicode.h"

typedef GPtrArray	Pattern;

typedef struct _PatternTranslate{
	Pattern		*ptrn;		/* pattern for name */
	GHashTable	*tr;		/* HASH table with translate patterns, key - pattern type, value - *Pattern */
} PtrnTrans;

static	PtrnTrans	*parr = NULL;
static	uint32		ptrn_count = 0;

static Pattern*	pattern_new( const char8 *ptrn )
{
	Pattern	*res;
	char8	**list_str, **list_pos;

	g_return_val_if_fail( ptrn != NULL, NULL );

	res = g_ptr_array_new();

	list_str = g_strsplit( ptrn, "*", -1 );

	for( list_pos = list_str; *list_pos != NULL; ++list_pos ){
		if( (*list_pos)[0] == 0 )
			g_ptr_array_add( res, NULL );
		else
			g_ptr_array_add( res, g_strdup( *list_pos ) );
	}
	g_strfreev( list_str );

	if( res->len == 1 )
		g_ptr_array_add( res, NULL );

	return res;
}

static bool32 pattern_str_valid( const Pattern *ptrn, const char8 *str )
{
	char8	**list;
	uint32	idx;

	if( ptrn == 0 )
		str += 66;

	g_return_val_if_fail( ptrn != NULL, FALSE );
	g_return_val_if_fail( str != NULL, FALSE );

	list = (char8**)ptrn->pdata;

	if( list[0] != NULL ){
		if( g_str_has_prefix( str, list[0] ) == FALSE )
			return FALSE;
		else
			str += strlen( list[0] );
	}

	if( list[ptrn->len - 1] != NULL && g_str_has_suffix( str, list[ptrn->len-1] ) == FALSE )
		return FALSE;

	for( idx = 1; idx < ptrn->len - 1; ++idx ){
		str = strstr( str, list[idx] );
		if( str == NULL )
			return FALSE;
	}

	if( list[ptrn->len - 1] != NULL && g_str_has_suffix( str, list[ptrn->len-1] ) == FALSE )
		return FALSE;

	return TRUE;
}

void string_transform_init(char8	*path_file_names_txt)
{
	FILE		*file;
	uint16		*buf16;
	uint32		len32;
	char8		*buf8;
	GArray		*res;
	PtrnTrans	pt;
	Pattern		*patt;
	char8		**list_str, **list_pos;
	char8		**ptrn, **ptrn_pos;
	char8		**type, **type_pos;

	/* reading strings for localized transforms */

//	file = g_fopen( SETTINGSLOCDIR( "names.txt", UTF8), "rb" );
	file = g_fopen( path_file_names_txt, "rb" );
	if( file == NULL ){
		g_printerr( "cannot open file '%s'\n", path_file_names_txt );
		g_return_if_reached();
	}
	fseek( file, 0, SEEK_END );
	len32 = ftell( file ) / sizeof(uint16);
	fseek( file, 0, SEEK_SET );

	buf16 = g_new( uint16, len32 + 1 );
	fread( buf16, sizeof(uint16), len32, file );
	buf16[len32] = 0;
	fclose( file );

	buf8 = utf16_to_utf8( utf16_type( buf16[0] ), buf16, len32, NULL, NULL, NULL );
	g_free( buf16 );

	list_str = g_strsplit( buf8, "\n", -1 );
	g_free( buf8 );

	res = g_array_new( FALSE, FALSE, sizeof(PtrnTrans) );
	for( list_pos = list_str; *list_pos != NULL; ++list_pos ){
		if( (*list_pos)[0] != '"' )
			continue;
		g_strstrip( *list_pos );
		ptrn = g_strsplit( *list_pos, "\"", -1 );
		pt.ptrn = NULL;
		pt.tr = g_hash_table_new( g_str_hash, g_str_equal );
		for( ptrn_pos = ptrn; *ptrn_pos != NULL; ++ptrn_pos ){
			if( (*ptrn_pos)[0] == 0 ){
				++ptrn_pos;
				if( pt.ptrn != NULL && *ptrn_pos == NULL )
					break;
				g_return_if_fail( pt.ptrn == NULL && *ptrn_pos != NULL );
				pt.ptrn = pattern_new( *ptrn_pos );
			}
			else{
				type = g_strsplit( g_strstrip(*ptrn_pos), ",", -1 );

				++ptrn_pos;
				g_return_if_fail( *ptrn_pos != NULL );

				patt = pattern_new( *ptrn_pos );
				if( patt->len != pt.ptrn->len ){
					g_printerr( "\n ERROR pattern '%s'", *list_pos );
					g_return_if_fail( patt->len == pt.ptrn->len );
				}

				for( type_pos = type; *type_pos != NULL; ++type_pos )
					g_hash_table_insert( pt.tr, *type_pos, patt );
				g_free( type );
			}
		}
		g_strfreev( ptrn );
		if( pt.ptrn != NULL )
			g_array_append_val( res, pt );
	}
	g_strfreev( list_str );

	ptrn_count = res->len;
	parr = (PtrnTrans*)g_array_free( res, FALSE );
}

char8*	string_transform( const char8 *string, const char8 *type )
{
	GString	*str;
	Pattern	*ptrn_tr;
	Pattern	*ptrn;
	uint32	idx;
	char8	*pos;

	g_return_val_if_fail( string != NULL , NULL );
	g_return_val_if_fail( type != NULL , g_strdup( string ) );
	g_return_val_if_fail( parr != NULL , g_strdup( string ) );
	g_return_val_if_fail( ptrn_count != 0 , g_strdup( string ) );

	for( idx = 0; idx < ptrn_count; ++idx )
		if( pattern_str_valid( parr[idx].ptrn, string ) != FALSE )
			break;

	if( idx == ptrn_count )
		return g_strdup( string );

	g_return_val_if_fail( parr[idx].tr != NULL , g_strdup( string ) );

	ptrn_tr = g_hash_table_lookup( parr[idx].tr, type );
	g_return_val_if_fail( ptrn_tr != NULL , g_strdup( string ) );

	ptrn = parr[idx].ptrn;

	/* translate string */
	if( g_ptr_array_index(ptrn, 0) != NULL )
		string += strlen( (const char8*)g_ptr_array_index(ptrn, 0) );
	str = g_string_new( (const char8*)g_ptr_array_index(ptrn_tr, 0) );

	for( idx = 1; idx < ptrn->len; ++idx ){
		if( g_ptr_array_index(ptrn, idx) == NULL )
			continue;
		pos = strstr( string, (const char8*)g_ptr_array_index(ptrn, idx) );
		if( pos == NULL ){
			g_warn_if_reached();
			continue;
		}
		g_string_append_len( str, string, pos - string );
		if( g_ptr_array_index(ptrn_tr, idx) != NULL )
			g_string_append( str, (const char8*)g_ptr_array_index(ptrn_tr, idx) );
		string = pos + strlen( (const char8*)g_ptr_array_index(ptrn, idx) );
	}
	g_string_append( str, string );

	return g_string_free( str, FALSE );
}

/* extract filename prefix from parameter mnemonic,  returned string should by freed by g_free() */
char8*	string_extract_filename( const char8 *mnem )
{
	char8	*filename;
	char8	*name_separator;

	name_separator = strchr( mnem , ':' );
	g_return_val_if_fail( name_separator != NULL, NULL );

	filename = strchr( mnem, '.' );
	if( filename == NULL || filename - name_separator > 0 )
		filename = g_strndup( mnem, name_separator - mnem );
	else
		filename = g_strndup( mnem, filename - mnem );

	return filename;
}
