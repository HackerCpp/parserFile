#include "common.h"
#include "utils.h"

#include <libxml/tree.h>
#include <string.h>
#include <math.h>

static xmlDocPtr kedrrcdoc = 0;

static GData*	units = 0; 					/* list of unit's scales from kedrrc */

/* some helpers for reading kedrrc */
static void load_units_list();
static void create_default_kedrrc();
static xmlNodePtr find_node( xmlNodePtr node, const char8* path );
/*                                 */

static float64 kedrrc_get_unit_id( GQuark id )
{
	gpointer data;
	g_return_val_if_fail( units != NULL, 0.0 );
	data = g_datalist_id_get_data( &units, id );
	if( data == NULL ){
		g_printerr( "\n** UNIT '%s' NOT FOUND", g_quark_to_string( id ) );
		g_return_val_if_reached( 0.0 );
	}
	return *(float64*)data;
}

float64 kedrrc_get_unit( const char8 *name )
{
	return kedrrc_get_unit_id( g_quark_from_string(name) );
}

void kedrrc_open()
{
	g_return_if_fail( kedrrcdoc == NULL );

	if( g_file_test( SETTINGSDIR( "kedrrc.xml", UTF8 ), G_FILE_TEST_EXISTS ) )
		kedrrcdoc = xmlParseFile( SETTINGSDIR( "kedrrc.xml", UTF8 ) );
	if( kedrrcdoc == NULL ){
		g_printerr( "\n** CREATE DEFAULT kedrrc.xml" );
		g_warn_if_reached();
		create_default_kedrrc();
		kedrrc_save();
	}
	load_units_list();
}

void kedrrc_save()
{
	xmlSaveFormatFileEnc( SETTINGSDIR( "kedrrc.xml", UTF8 ), kedrrcdoc, "UTF-8", 1 );
}

static void create_default_kedrrc()
{
	xmlNodePtr tree, sub;

	kedrrcdoc = xmlNewDoc( (const xmlChar*)"1.0" );
//	kedrrcdoc->encoding = (const xmlChar*)"UTF-8";
	kedrrcdoc->children = xmlNewDocNode( kedrrcdoc, NULL, (const xmlChar*)"kedr-bin", NULL );

	tree = xmlNewChild( kedrrcdoc->children, NULL, (const xmlChar*)"units", NULL );

	sub = xmlNewChild( tree, NULL, (const xmlChar*)"unit", NULL );
	xmlSetProp( sub, (const xmlChar*)"name", (const xmlChar*)"PIX" );
	xmlSetProp( sub, (const xmlChar*)"scale", (const xmlChar*)"2.1928571428571428571428571428571" );

	sub = xmlNewChild( tree, NULL, (const xmlChar*)"unit", NULL );
	xmlSetProp( sub, (const xmlChar*)"name", (const xmlChar*)"CMM" );
	xmlSetProp( sub, (const xmlChar*)"scale", (const xmlChar*)"0.1" );

	sub = xmlNewChild( tree, NULL, (const xmlChar*)"unit", NULL );
	xmlSetProp( sub, (const xmlChar*)"name", (const xmlChar*)"DMM" );
	xmlSetProp( sub, (const xmlChar*)"scale", (const xmlChar*)"1" );

	sub = xmlNewChild( tree, NULL, (const xmlChar*)"unit", NULL );
	xmlSetProp( sub, (const xmlChar*)"name", (const xmlChar*)"MM" );
	xmlSetProp( sub, (const xmlChar*)"scale", (const xmlChar*)"10" );

	sub = xmlNewChild( tree, NULL, (const xmlChar*)"unit", NULL );
	xmlSetProp( sub, (const xmlChar*)"name", (const xmlChar*)"CM" );
	xmlSetProp( sub, (const xmlChar*)"scale", (const xmlChar*)"100" );

	sub = xmlNewChild( tree, NULL, (const xmlChar*)"unit", NULL );
	xmlSetProp( sub, (const xmlChar*)"name", (const xmlChar*)"M" );
	xmlSetProp( sub, (const xmlChar*)"scale", (const xmlChar*)"10000" );

	sub = xmlNewChild( tree, NULL, (const xmlChar*)"unit", NULL );
	xmlSetProp( sub, (const xmlChar*)"name", (const xmlChar*)"FT" );
	xmlSetProp( sub, (const xmlChar*)"scale", (const xmlChar*)"3048" );

	sub = xmlNewChild( tree, NULL, (const xmlChar*)"unit", NULL );
	xmlSetProp( sub, (const xmlChar*)"name", (const xmlChar*)"FOOT" );
	xmlSetProp( sub, (const xmlChar*)"scale", (const xmlChar*)"3048" );

	sub = xmlNewChild( tree, NULL, (const xmlChar*)"unit", NULL );
	xmlSetProp( sub, (const xmlChar*)"name", (const xmlChar*)"IN" );
	xmlSetProp( sub, (const xmlChar*)"scale", (const xmlChar*)"254" );

	sub = xmlNewChild( tree, NULL, (const xmlChar*)"unit", NULL );
	xmlSetProp( sub, (const xmlChar*)"name", (const xmlChar*)"INCH" );
	xmlSetProp( sub, (const xmlChar*)"scale", (const xmlChar*)"254" );

	sub = xmlNewChild( tree, NULL, (const xmlChar*)"unit", NULL );
	xmlSetProp( sub, (const xmlChar*)"name", (const xmlChar*)"MSEC" );
	xmlSetProp( sub, (const xmlChar*)"scale", (const xmlChar*)"1" );

	sub = xmlNewChild( tree, NULL, (const xmlChar*)"unit", NULL );
	xmlSetProp( sub, (const xmlChar*)"name", (const xmlChar*)"MKSEC" );
	xmlSetProp( sub, (const xmlChar*)"scale", (const xmlChar*)"0.001" );

	sub = xmlNewChild( tree, NULL, (const xmlChar*)"unit", NULL );
	xmlSetProp( sub, (const xmlChar*)"name", (const xmlChar*)"USEC" );
	xmlSetProp( sub, (const xmlChar*)"scale", (const xmlChar*)"0.001" );

	sub = xmlNewChild( tree, NULL, (const xmlChar*)"unit", NULL );
	xmlSetProp( sub, (const xmlChar*)"name", (const xmlChar*)"SEC" );
	xmlSetProp( sub, (const xmlChar*)"scale", (const xmlChar*)"1000" );

	sub = xmlNewChild( tree, NULL, (const xmlChar*)"unit", NULL );
	xmlSetProp( sub, (const xmlChar*)"name", (const xmlChar*)"MIN" );
	xmlSetProp( sub, (const xmlChar*)"scale", (const xmlChar*)"60000" );

	sub = xmlNewChild( tree, NULL, (const xmlChar*)"unit", NULL );
	xmlSetProp( sub, (const xmlChar*)"name", (const xmlChar*)"HR" );
	xmlSetProp( sub, (const xmlChar*)"scale", (const xmlChar*)"3600000" );

	sub = xmlNewChild( tree, NULL, (const xmlChar*)"unit", NULL );
	xmlSetProp( sub, (const xmlChar*)"name", (const xmlChar*)"GRAM" );
	xmlSetProp( sub, (const xmlChar*)"scale", (const xmlChar*)"0.001" );

	sub = xmlNewChild( tree, NULL, (const xmlChar*)"unit", NULL );
	xmlSetProp( sub, (const xmlChar*)"name", (const xmlChar*)"KG" );
	xmlSetProp( sub, (const xmlChar*)"scale", (const xmlChar*)"1" );

	sub = xmlNewChild( tree, NULL, (const xmlChar*)"unit", NULL );
	xmlSetProp( sub, (const xmlChar*)"name", (const xmlChar*)"TONNE" );
	xmlSetProp( sub, (const xmlChar*)"scale", (const xmlChar*)"1000" );

	sub = xmlNewChild( tree, NULL, (const xmlChar*)"unit", NULL );
	xmlSetProp( sub, (const xmlChar*)"name", (const xmlChar*)"LB" );
	xmlSetProp( sub, (const xmlChar*)"scale", (const xmlChar*)"0.45359237" );
}

static xmlNodePtr find_node( xmlNodePtr node, const char8* path )
{
	char8**	paths;
	char8**	cur;
	g_return_val_if_fail( path != NULL, NULL );
	if( node == NULL )
		node = xmlDocGetRootElement( kedrrcdoc );
	paths = g_strsplit( path, ":", -1 );
	cur = paths;
	while( *cur != NULL && node != NULL ){
		if( !xmlStrcmp(node->name, (const xmlChar *)*cur) ){
			cur++;
			if( *cur == NULL )
				break;
			node = node->xmlChildrenNode;
		}
		else
			node = node->next;
	}
	g_strfreev( paths );
	if( node == NULL ){
		g_printerr( "\n** PATH '%s' NOT FOUND", path );
		g_return_val_if_reached( NULL );
	}
	return node;
}

static void load_units_list()
{
	xmlNodePtr	cur;
	char		*name_brackets;

	if( kedrrcdoc == NULL )
		return;
	if( units )
		g_datalist_clear( &units );
	else
		g_datalist_init( &units );
	cur = find_node( NULL, "kedr-bin:units" );
	if( cur == NULL )
		return;
	cur = cur->xmlChildrenNode;

	while( cur != NULL ){
		if ((!xmlStrcmp(cur->name, (const xmlChar *)"unit"))){
			xmlChar *name = xmlGetProp(cur, (const xmlChar*)"name");
			xmlChar *scale = xmlGetProp(cur, (const xmlChar*)"scale");
			float64	*d = g_new( float64, 1 );
			*d = g_strtod( (const char8*)scale, NULL );
			name_brackets = g_strdup_printf( "(%s)", (char8*)name );
			g_datalist_set_data_full( &units, (const char8*)name, d, g_free );
			g_datalist_set_data_full( &units, (const char8*)name_brackets, d, g_free );
			g_free(name_brackets);
			xmlFree(name);
			xmlFree(scale);
		}
		cur = cur->next;
	}
}

static xmlNodePtr create_node( xmlNodePtr node, const char8* path )
{
	xmlNodePtr	parent;
	char8		**paths;
	char8		**cur;

	g_return_val_if_fail( path != NULL, NULL );
	if( node == NULL )
		node = xmlDocGetRootElement( kedrrcdoc );
	parent = NULL;
	paths = g_strsplit( path, ":", -1 );
	cur = paths;
	while( *cur != NULL && node != NULL ){
		if( !xmlStrcmp(node->name, (const xmlChar *)*cur) ){
			cur++;
			if( *cur == NULL )
				break;
			parent = node;
			node = node->xmlChildrenNode;
		}
		else
			node = node->next;
	}

	if( parent == NULL )
		parent = xmlDocGetRootElement( kedrrcdoc );

	while( *cur != NULL ){
		node = xmlNewChild( parent, NULL, (const xmlChar*)*cur, NULL );
		parent = node;
		++cur;
	}

	g_strfreev( paths );
	return node;
}

static struct _ProgPref6ssection{
	char8	*name;
	int32	name_len;
	char8	*path;
} prog_pref6s[] = {
		{"_kedr",		5,	"kedr-bin:prop:kedr"},
		{"_driver",		7,	"kedr-bin:prop:drivers"},
		{"_exports",	8,	"kedr-bin:prop:exports"},
};

static const char* get_prog_path( const char8 *path )
{
	static char8	*res = NULL;
	int i;

	g_return_val_if_fail( path != NULL, NULL );

	for( i = 0; i < G_N_ELEMENTS(prog_pref6s); ++i ){
		if( strncmp( prog_pref6s[i].name, path, prog_pref6s[i].name_len ) == 0 )
			break;
	}

	g_free( res );
	if( i < G_N_ELEMENTS(prog_pref6s) )
		res = g_strdup_printf( "%s%s", prog_pref6s[i].path, path + prog_pref6s[i].name_len );
	else
		res = g_strdup( path );

	return res;
}

/* put string preferences 'data' on path "path1:path2:path..." */
void kedrrc_put_pref6s( const char8 *path, const char8 *data )
{
	xmlNodePtr		node;
	const char8		*full;

	g_return_if_fail( path != NULL );
	g_return_if_fail( data != NULL );

	full = get_prog_path( path );

	node = find_node( NULL, full );
	if( node == NULL )
		node = create_node( NULL, full );

	xmlNodeSetContent( node, (const xmlChar*)data );
	kedrrc_save();
}

/* get string preferences 'data' on path "path1:path2:path..." */
const char8* kedrrc_get_pref6s( const char8 *path )
{
	static char8	*data = NULL;
	const char8		*full;
	xmlNodePtr		node;

	full = get_prog_path( path );
	node = find_node( NULL, full );

	if( node == NULL )
		return NULL;

	g_free( data );
	data = (char8*)xmlNodeGetContent( node );
	return data;
}

/* put float64 'data' on path "path1:path2:path..." */
void kedrrc_put_pref6s_float64( const char8 *path, float64 data )
{
	char8	*str;

	str = g_strdup_printf( "%g", data );
	kedrrc_put_pref6s( path, str );
	g_free( str );
}

/* get float64 'data' on path "path1:path2:path...", return FALSE if path is not exist */
bool32 kedrrc_get_pref6s_float64( const char8 *path, float64 *data )
{
	const char8		*str;

	str = kedrrc_get_pref6s( path );

	if( str == NULL )
		return FALSE;

	if( data != NULL )
		*data = g_strtod( str, NULL );

	return TRUE;
}

/* put int32 'data' on path "path1:path2:path..." */
void kedrrc_put_pref6s_int32( const char8 *path, int32 data )
{
	char8	*str;

	str = g_strdup_printf( "%d", data );
	kedrrc_put_pref6s( path, str );
	g_free( str );
}

/* get int32 'data' on path "path1:path2:path...", return FALSE if path is not exist */
bool32 kedrrc_get_pref6s_int32( const char8 *path, int32 *data )
{
	const char8		*str;

	str = kedrrc_get_pref6s( path );

	if( str == NULL )
		return FALSE;

	if( data != NULL )
		*data = strtol( str, NULL, 10 );

	return TRUE;
}
