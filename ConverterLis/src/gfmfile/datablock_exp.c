#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "data_types.h"
#include "parampos.h"
#include "unicode.h"
#include <program_h>

#define	CONV2FLOAT64( TYPE ) \
	static float64 TYPE ## _float64( void *value )\
	{\
		return *(TYPE*)value;\
	}

#define	FIXED32_FLOAT64( DIGITS ) \
	static float64 fixed32_ ## DIGITS ## _float64( void *value )\
	{\
		return *(int32*)value / 1e+ ## DIGITS;\
	}

#define	UFIXED32_FLOAT64( DIGITS ) \
	static float64 ufixed32_ ## DIGITS ## _float64( void *value )\
	{\
		return *(uint32*)value / 1e+ ## DIGITS;\
	}

CONV2FLOAT64( int8 )
CONV2FLOAT64( uint8 )
CONV2FLOAT64( int16 )
CONV2FLOAT64( uint16 )
CONV2FLOAT64( int32 )
CONV2FLOAT64( uint32 )
CONV2FLOAT64( int64 )
CONV2FLOAT64( uint64 )
FIXED32_FLOAT64( 3 )
UFIXED32_FLOAT64( 3 )
FIXED32_FLOAT64( 4 )
UFIXED32_FLOAT64( 4 )
FIXED32_FLOAT64( 5 )
UFIXED32_FLOAT64( 5 )
FIXED32_FLOAT64( 6 )
UFIXED32_FLOAT64( 6 )
FIXED32_FLOAT64( 7 )
UFIXED32_FLOAT64( 7 )
CONV2FLOAT64( float32 )
CONV2FLOAT64( float64 )

struct _ParameterLoggingTypeDescription data_types[] = {
		{"INT8",		LOG_INT8,		sizeof(int8),		&int8_float64 },
		{"UINT8",		LOG_UINT8,		sizeof(uint8),		&uint8_float64},
		{"INT16",		LOG_INT16,		sizeof(int16),		&int16_float64},
		{"UINT16",		LOG_UINT16,		sizeof(uint16),		&uint16_float64},
		{"INT32",		LOG_INT32,		sizeof(int32),		&int32_float64},
		{"UINT32",		LOG_UINT32,		sizeof(uint32),		&uint32_float64},
		{"INT64",		LOG_INT64,		sizeof(int64),		&int64_float64},
		{"UINT64",		LOG_UINT64,		sizeof(uint64),		&uint64_float64},
		{"FIXED32.3",	LOG_FIXED32_3,	sizeof(fixed32_3),	&fixed32_3_float64},
		{"UFIXED32.3",	LOG_UFIXED32_3,	sizeof(ufixed32_3),	&ufixed32_3_float64},
		{"FIXED32.4",	LOG_FIXED32_4,	sizeof(fixed32_4),	&fixed32_4_float64},
		{"UFIXED32.4",	LOG_UFIXED32_4,	sizeof(ufixed32_4),	&ufixed32_4_float64},
		{"FIXED32.5",	LOG_FIXED32_5,	sizeof(fixed32_5),	&fixed32_5_float64},
		{"UFIXED32.5",	LOG_UFIXED32_5,	sizeof(ufixed32_5),	&ufixed32_5_float64},
		{"FIXED32.6",	LOG_FIXED32_6,	sizeof(fixed32_6),	&fixed32_6_float64},
		{"UFIXED32.6",	LOG_UFIXED32_6,	sizeof(ufixed32_6),	&ufixed32_6_float64},
		{"FIXED32.7",	LOG_FIXED32_7,	sizeof(fixed32_7),	&fixed32_7_float64},
		{"UFIXED32.7",	LOG_UFIXED32_7,	sizeof(ufixed32_7),	&ufixed32_7_float64},
		{"FLOAT32",		LOG_FLOAT32,	sizeof(float32),	&float32_float64},
		{"FLOAT64",		LOG_FLOAT64,	sizeof(float64),	&float64_float64},
};

struct _DataBlock{
	GPtrArray		*params;		/* array of PraramDesc */
	ParamPosDesc	*posdesc;		/* extract position info */

	uint32           records_count;

	size_t			data_size;
	goffset 		offset;			/* current offset in in/out streams */
	goffset			data_begin;		/* data begin offset in file, use for clear record  */
};

GPtrArray	*data_blocks = NULL;

GPtrArray	*params = NULL;

/* array of all allocated data block's containers in converter */
static GPtrArray	*data_containers = NULL;

static GString		*calc = NULL;

static void data_block_new_read_from_file_NEW_FORMAT( const char8 *header_str, uint32 data_block_size, GInputStream *in );
static char8** data_block_add_params_from_list( DataBlock* db, char8 **ptr );

EXTERN const char8* data_blocks_get_calibration_str()
{
	if( calc == NULL )
		return "";

	return calc->str;
}

EXTERN void data_block_add_values( DataBlock *db, void *values )
{
	ParamDesc	**desc;
	ParamData	pp;
	int i;

	ppd_extract( db->posdesc, values, &pp.position );
	desc = (ParamDesc**)&g_ptr_array_index( db->params, 0 );
	for( i = 0; i < db->params->len; ++i, ++desc ){
		if( *desc == NULL )
			continue;

		if( (*desc)->flags & SELECTED ){
			if( data_types[(*desc)->type].conv2float64 != NULL )
				pp.value = data_types[(*desc)->type].conv2float64( (int8*)values + (*desc)->offset );
			else
				g_warn_if_reached();
			parr_add_data( (*desc)->parr, pp );
		}
	}
}

EXTERN void data_blocks_free()
{
	GPtrArray		*data_containers_loc;
	GPtrArray		*data_blocks_loc;

	if( data_containers == NULL )
		return;

	g_ptr_array_free( params, TRUE );
	params = NULL;

	data_containers_loc = data_containers;
	data_containers = NULL;
	data_blocks_loc = data_blocks;
	data_blocks = NULL;

	g_ptr_array_free( data_containers_loc, TRUE );
	g_ptr_array_free( data_blocks_loc, TRUE );

	g_string_free( calc, TRUE );
	calc = NULL;

//	GPtrArray		*data_blocks_loc;
//	DataBlock		**db;
//	ParamDesc		**desc;
//	int i;
//
//	if( data_blocks == NULL )
//		return;
//
//	data_blocks_loc = data_blocks;
//	data_blocks = NULL;
//	db = (DataBlock**)&g_ptr_array_index( data_blocks_loc, 0 );
//	for( i = 0; i < data_blocks_loc->len; ++i, ++db ){
//		if( *db == NULL ){
//			g_printerr( "ERROR Data block is NULL\n" );
//			g_warn_if_reached();
//			continue;
//		}
//
//		desc = (ParamDesc**)&g_ptr_array_index( (*db)->params, 0 );
//		for( ; *desc != NULL; ++desc ){
//			if( (*desc)->flags & PF_CURVE )
//				parr_clear( (*desc)->parr );
//			g_free( *desc );
//		}
//		g_ptr_array_free( (*db)->params, TRUE );
//		ppd_free( (*db)->posdesc );
//		g_free( *db );
//	}
//	g_ptr_array_free( data_blocks_loc, TRUE );
}

/* return 0 if data blocks is empty other non zero */
EXTERN int32 data_block_get_start_stop( fixed32_5 *start_m_5, fixed32_5 *stop_m_5, ufixed32_3 *end_time_sec_3 )
{
	fixed32_5		min_depth_m_5;
	fixed32_5		max_depth_m_5;
	ufixed32_3		max_time_sec_3;
	DSDirection		dir;
	DSDirection		cur_dir;
	DataBlock		**db;
	ParamDesc		**desc;
	ParamData		*last;
	fixed32_5		l_top_m_5;
	fixed32_5		l_bot_m_5;
	int i;

	g_return_val_if_fail( data_blocks != NULL, 0 );

	min_depth_m_5 = G_MAXINT32;
	max_depth_m_5 = -G_MAXINT32;
	max_time_sec_3 = 0;

	db = (DataBlock**)&g_ptr_array_index( data_blocks, 0 );
	for( i = 0; i < data_blocks->len; ++i, ++db ){
		if( *db == NULL ){
			g_printerr( "ERROR Data block is NULL\n" );
			g_warn_if_reached();
			continue;
		}

		desc = (ParamDesc**)&g_ptr_array_index( (*db)->params, 0 );

		last = parr_get_last_data((*desc)->parr);
		if( last == NULL )
			continue;

		parr_get_depth_interval( (*desc)->parr, &l_top_m_5, &l_bot_m_5, &dir );

		if(dir != DS_UNKNOWN)
			cur_dir = dir;

		for( ; *desc != NULL; ++desc ){
			if( (*desc)->flags & SELECTED ){
				min_depth_m_5 = MIN( min_depth_m_5, l_top_m_5 + (*desc)->mp_m_5 );
				max_depth_m_5 = MAX( max_depth_m_5, l_bot_m_5 + (*desc)->mp_m_5 );
				max_time_sec_3 = MAX( max_time_sec_3, last->position.time_sec_3 );
			}
		}
	}

	if( max_depth_m_5 == -G_MAXINT32 )
		return 0;

	if( start_m_5 ){
		if( cur_dir == DS_DOWN )
			*start_m_5 = min_depth_m_5;
		else
			*start_m_5 = max_depth_m_5;
	}
	if( stop_m_5 ){
		if( cur_dir == DS_DOWN )
			*stop_m_5 = max_depth_m_5;
		else
			*stop_m_5 = min_depth_m_5;
	}
	if( end_time_sec_3 )
		*end_time_sec_3 = max_time_sec_3;

	return 1;
}

static void data_block_free( DataBlock	*db )
{
	ParamDesc	**param;
	int j;

	if( db == NULL )
		return;

	param = (ParamDesc**)&g_ptr_array_index( db->params, 0 );
	for( j = 0; j < db->params->len; ++param, ++j ){
		if( *param == NULL )
			continue;
		g_free( (*param)->entmnem );
		g_free( (*param)->desc );
		parr_clear( (*param)->parr );
		g_free( *param );
	}

	ppd_free( db->posdesc );

	g_slice_free( DataBlock, db );
}

static DBContainer *dbc_new()
{
	DBContainer	*res;

	res = g_slice_new( DBContainer );
	res->blocks = g_ptr_array_new_with_free_func( (GDestroyNotify)data_block_free );

	if( data_containers != NULL )
		g_ptr_array_add( data_containers, res );
	else
		g_warn_if_reached();

	res->number = data_containers->len;

	return res;
}

static void dbc_free( DBContainer *dbc )
{
	if( dbc == NULL )
		return;

	g_ptr_array_free( dbc->blocks, TRUE );

	g_slice_free( DBContainer, dbc );
}

void data_block_new_read_from_file( uint16 symbol, uint32 data_block_size, GInputStream *in )
{
	DBContainer	*dbc;
	DataBlock 	*db;
	uint32		len32;
	uint16		*str16;
	char8		**list, **ptr;
	char8		*str8;
	uint32		data_size;
	uint32		count;
	DataBlock 	**db_arr;
	void		*buf;
	void		*data;
	ParamData	pd;
	ParamArray	*pos_array;
	ParamDesc	**param;
	ParamData	*ppd;
	goffset		offset;
	int i, j;

	/* read text header length */
	g_input_stream_read( in, &len32, sizeof(len32), NULL, NULL );
	data_block_size -= sizeof(len32) + len32;
	str16 = (uint16*)g_malloc( len32 + 2 );
	g_input_stream_read( in, str16, len32, NULL, NULL );
	len32 /= 2;
	str16[ len32 ] = 0;
	str8 = utf16_to_utf8( utf16_type(symbol), str16, len32, NULL, NULL, NULL );
	g_free( str16 );

	/* check DATA_BLOCK version */
	if( g_str_has_prefix( str8, "<?xml version=" ) == FALSE ){
	    data_block_new_read_from_file_NEW_FORMAT( str8, data_block_size, in );
	    g_free( str8 );
	    return;
	}


	if( data_containers == NULL )
		data_containers = g_ptr_array_new_with_free_func( (GDestroyNotify)dbc_free );

	dbc = dbc_new();
	data_size = 0;
	list = g_strsplit( str8, "\n", -1 );
	for( ptr = list; *ptr != NULL; ++ptr ){
		if( strcmp( *ptr, "<PARAMETERS>" ) == 0 )
			break;
	}
	++ptr;
	for( ; *ptr != NULL; ++ptr ){
		db = g_slice_new0( DataBlock );
		db->params = g_ptr_array_new();
//		g_object_ref( in );
//		db->in = G_FILE_INPUT_STREAM(in);
		g_ptr_array_add( dbc->blocks, db );

		ptr = data_block_add_params_from_list( db, ptr );
		if( db->posdesc == NULL ){
			if( data_blocks == NULL ){
				data_blocks = g_ptr_array_new();
			}
			g_ptr_array_add( data_blocks, db );
		}

		data_size += db->data_size;
		if( ptr == NULL )
			break;
		else
			--ptr;
	}
	g_strfreev( list );

	count = data_block_size / data_size;
	g_warn_if_fail( data_block_size % data_size == 4 || data_block_size % data_size == 5 );

	db_arr = (DataBlock**)&g_ptr_array_index( dbc->blocks, 0 );

	db_arr[0]->data_begin = g_seekable_tell( G_SEEKABLE(in) );
	db_arr[0]->offset = db_arr[0]->data_begin;
	for( i = 1; i < dbc->blocks->len; ++i ){
		db_arr[i]->data_begin = db_arr[i-1]->data_begin + count * db_arr[i-1]->data_size;
		db_arr[i]->offset = db_arr[i]->data_begin;
	}

	/* create ParamArray for copy with position and empty data */
	buf = NULL;
	pos_array = parr_create();
	if( db_arr[0]->posdesc != NULL ){
		pd.value = 0;

		buf = g_malloc( count * db_arr[0]->data_size );
		data_block_size -= g_input_stream_read( in, buf, count * db_arr[0]->data_size, NULL, NULL );

		data = buf;
		for( j = 0; j < count; ++j ){
			ppd_extract( db_arr[0]->posdesc, data, &pd.position );
			parr_add_data( pos_array, pd );
			data = (uint8*)data + db_arr[0]->data_size;
		}
	}

	/* read other data blocks */
	for( i = 1; i < dbc->blocks->len; ++i ){
		data = NULL;	/* flag no (*param)->count > 1 */

		param = (ParamDesc**)&g_ptr_array_index( db_arr[i]->params, 0 );
		for( ; *param != NULL; ++param ){
			parr_dup_data( pos_array, (*param)->parr );
			if( (*param)->count > 1 ){
				/* ParamArray with offset data */
				offset = db_arr[i]->offset + (*param)->offset;
				for( j = 0; j < count; ++j, offset += db_arr[i]->data_size ){
					ppd = parr_get_data( (*param)->parr, j );
					ppd->offset = offset;
//					ppd->pointer = NULL;
				}
				++data;	/* set flag (*param)->count > 1 */
			}
			else if( data != NULL ){
				/* in some block */
				g_printerr( "\n** ERROR Some data lost, data_block contain vector and single data" );
				g_warn_if_reached();
			}
		}

//		if( data != NULL ){
//			/* nothing to do, we put offset data */
//			data_block_size -= count * db_arr[i]->data_size;
//			g_input_stream_skip( in, count * db_arr[i]->data_size, NULL, NULL );
//			continue;
//		}

		buf = g_realloc( buf, count * db_arr[i]->data_size );
		g_seekable_seek( G_SEEKABLE(in), db_arr[i]->offset, G_SEEK_SET, NULL, NULL );
		data_block_size -= g_input_stream_read( in, buf, count * db_arr[i]->data_size, NULL, NULL );

		data = buf;
		for( j = 0; j < count; ++j ){
			param = (ParamDesc**)&g_ptr_array_index( db_arr[i]->params, 0 );
			for( ; *param != NULL; ++param ){
				ppd = parr_get_data( (*param)->parr, j );
				if( (*param)->count == 1 )
					ppd->value = data_types[(*param)->type].conv2float64( (int8*)data + (*param)->offset );
//				else
//					g_warn_if_reached();
			}
			data = (uint8*)data + db_arr[i]->data_size;
		}

		// XXX remove depth overlap in parameter's arrays
//		param = (ParamDesc**)&g_ptr_array_index( db_arr[i]->params, 0 );
//		for( ; *param != NULL; ++param )
//			parr_remove_depth_overlap( (*param)->parr );
	}
	g_free( buf );
	parr_destroy( pos_array );

	g_warn_if_fail( data_block_size == 4 || data_block_size == 5 );
	g_input_stream_skip( in, data_block_size, NULL, NULL );
}

/* return null terminated array of ParamDesc */
EXTERN const ParamDesc** data_block_get_paramdesc_array( DataBlock *db )
{
	return (const ParamDesc**)&g_ptr_array_index( db->params, 0 );
}

static const char8* cut_shortcut( const char8 *str )
{
	char8	*out;

	if( str == NULL )
		return NULL;
	out = strstr( str, ":" );
	if( out != NULL )
		return out + 1;

	return str;
}

static void db_read_calc_from_list( char8 **ptr )
{
	GString	*data_in, *data_out, *coeff, *script;
	char8	*str, *pos;

	if( calc == NULL )
		calc = g_string_new( NULL );

	pos = strstr( *ptr, "NAME=" );
	g_return_if_fail( pos != NULL );
	str = strstr( pos, "\"" ) + 1;
	pos = strstr( str, "\"" );
	*pos = 0;
	pos = prog_string_transform( str, FULL_LOCAL );
	g_string_append_printf( calc, "\r\n%s", pos );
	g_free( pos );

	data_in = g_string_new( NULL );
	data_out = g_string_new( NULL );
	coeff = g_string_new( NULL );
	script = g_string_new( NULL );

	for( ++ptr; *ptr != NULL; ++ptr ){
		if( g_str_has_prefix( *ptr, "</CALC>" ) == TRUE ){
			++ptr;
			break;
		}

		if( g_str_has_prefix( *ptr, "<ARCHIVE>" ) == TRUE ){
			/* skip archive data */
			while( g_str_has_prefix( *ptr, "</ARCHIVE>" ) == FALSE )
				++ptr;
			continue;
		}

		if( g_str_has_prefix( *ptr, "<CALIBRATION" ) == TRUE ){
			/* reading calibration date */
			pos = strstr( *ptr, "DATE=" );
			if( pos == NULL ){
				g_warn_if_reached();
				continue;
			}
			str = strstr( pos, "\"" ) + 1;
			pos = strstr( str, "\"" );
			*pos = 0;
			g_string_append_printf( calc, _(" calibration date %s"), str );
			continue;
		}

		if( g_str_has_prefix( *ptr, "    <COEFF " ) == TRUE ){
			/* coefficient name and value */
			pos = strstr( *ptr, "NAME=" );
			if( pos == NULL ){
				g_warn_if_reached();
				continue;
			}
			str = strstr( pos, "\"" ) + 1;
			pos = strstr( str, "\"" );
			*pos = 0;
			g_string_append_printf( coeff, "%s = ", str );

			pos = strstr( pos + 1, "VALUE=" );
			if( pos == NULL ){
				g_warn_if_reached();
				g_string_append( coeff, "\r\n" );
				continue;
			}
			str = strstr( pos, "\"" ) + 1;
			pos = strstr( str, "\"" );
			*pos = 0;
			g_string_append( coeff, str );
			g_string_append( coeff, "\r\n" );
			continue;
		}

		if( g_str_has_prefix( *ptr, "    <DATA_IN " ) == TRUE ){
			/* coefficient name and value */
			pos = strstr( *ptr, "NAME=" );
			if( pos == NULL ){
				g_warn_if_reached();
				continue;
			}
			str = strstr( pos, "\"" ) + 1;
			pos = strstr( str, "\"" );
			*pos = 0;
			g_string_append_printf( data_in, "%s = ", str );

			pos = strstr( pos + 1, "LPARAM=" );
			if( pos == NULL ){
				g_warn_if_reached();
				g_string_append( data_in, "\r\n" );
				continue;
			}
			str = strstr( pos, "\"" ) + 1;
			pos = strstr( str, "\"" );
			*pos = 0;
			pos = prog_string_transform( str, LAS_FORM );
			g_string_append( data_in, cut_shortcut( pos ) );
			g_free( pos );
			g_string_append( data_in, "\r\n" );
			continue;
		}

		if( g_str_has_prefix( *ptr, "    <DATA_OUT " ) == TRUE ){
			/* coefficient name and value */
			pos = strstr( *ptr, "LPARAM=" );
			if( pos == NULL ){
				g_warn_if_reached();
				continue;
			}
			str = strstr( pos, "\"" ) + 1;
			pos = strstr( str, "\"" );
			*pos = 0;
			pos = prog_string_transform( str, LAS_FORM );
			g_string_append_printf( data_out, "%s = ", cut_shortcut( pos ) );
			g_free( pos );

			pos = strstr( *ptr, "NAME=" );
			if( pos == NULL ){
				g_warn_if_reached();
				g_string_append( data_out, "\r\n" );
				continue;
			}
			str = strstr( pos, "\"" ) + 1;
			pos = strstr( str, "\"" );
			*pos = 0;
			g_string_append( data_out, str );
			g_string_append( data_out, "\r\n" );
			continue;
		}

		if( g_str_has_prefix( *ptr, "    <" ) == TRUE )
			continue;

		/* others is script */
		g_string_append( script, *ptr );
		g_string_append( script, "\r\n" );
	}

	g_string_append( calc, "\r\n" );
	g_string_append_len( calc, coeff->str, coeff->len );
	g_string_append( calc, "\r\n" );
	g_string_append_len( calc, data_in->str, data_in->len );
	g_string_append_len( calc, script->str, script->len );
	g_string_append_len( calc, data_out->str, data_out->len );

	g_string_free( data_in, TRUE );
	g_string_free( data_out, TRUE );
	g_string_free( coeff, TRUE );
	g_string_free( script, TRUE );
}

static void create_param_desc_simple( DataBlock* db, char8 *param_name, ParLogType param_type, uint32 *offset, size_t element_count, fixed32_5 mp, const char8 *desc )
{
	ParamDesc	*par;
	char8		*pos;
	char8		*str;

	par = g_new0( ParamDesc, 1 );

	par->entmnem = g_strdup( param_name );

	par->desc = g_strdup( desc );

	par->type = param_type;
	par->offset = *offset;
	par->count = element_count;

	par->parr = parr_create();
	par->mp_m_5 = mp;

	g_print( "\n line '%s' mp '%d' desc '%s'", param_name, par->mp_m_5, desc );

	par->flags = NEAREST;
	if( desc != NULL && strstr( desc, "\"XZCH\"" ) != NULL)
		par->flags = 0;
	else if( desc != NULL && (pos = strstr( desc, "resampling_type" )) != NULL ){
		pos = strstr( pos, "\"" );
		if( pos != NULL ){
			str = pos + 1;
			pos = strstr( str, "\"" );
			if( pos == NULL ){
				g_printerr( "\n ** Error parameter description parsing '%s'", desc );
				g_warn_if_reached();
			}
			else{
				str = g_strndup( str, pos - str );
				if( strstr( str, "MAGNETIC_MARK" ) != NULL )
					par->flags = MAGNETIC_MARK;
				else if( strstr( str, "PEAK_VALUE" ) != NULL )
					par->flags = PEAK_VALUE;
				else if( strstr( str, "AVERAGE" ) != NULL )
					par->flags = AVERAGE;
				else if( strstr( str, "INTERPOLATE" ) != NULL )
					par->flags = INTERPOLATE;
				else if(  strstr( str, "SUMMARIZE" ) != NULL)
					par->flags = SUMMARIZE;
				g_free( str );
			}
		}
		else{
			g_printerr( "\n ** Error parameter description parsing '%s'", desc );
			g_warn_if_reached();
		}
	}

	if((pos = strstr( desc, "draw_type" )) != NULL){
		pos = strstr(pos, "\"");
		if(pos != NULL){
			str = pos + 1;
			pos = strstr(str, "\"");
			if(pos == NULL){
				g_printerr( "\n ** Error parameter description parsing '%s'", desc );
				g_warn_if_reached();
			}
			else{
				str = g_strndup( str, pos - str );
				if(strstr(str, "NONE") != NULL)
					par->no_lis = TRUE;
				g_free(str);
			}
		}
	}


	g_ptr_array_add( db->params, par );

	if( params == NULL ){
		params = g_ptr_array_new();
	}
	g_ptr_array_add( params, par );

	*offset += data_types[param_type].size * element_count;
}

static void create_param_desc_complex( DataBlock* db, char8 *param_name, ParLogType param_type, uint32 *offset, size_t element_count, fixed32_5 mp, const char8 *desc )
{
	char8	*ind_beg;
	char8	*ind_end;
	char8	*name_list[4] = { NULL, NULL, NULL, NULL };
	char8	**list_comma;
	char8	**pos;
	char8	*pos_points;
	char8	*pname;
	int32	num_beg;
	int32	num_end;

	ind_beg = g_strrstr( param_name, ":" );
	if( ind_beg == NULL )
		ind_beg = param_name;

	ind_beg = g_strrstr( ind_beg, "[" );
	ind_end = g_strrstr( ind_beg, "]" );

	if( ind_beg == NULL || ind_end == NULL )
		return create_param_desc_simple( db, param_name, param_type, offset, element_count, mp, desc );

	name_list[0] = g_strndup( param_name, ind_beg+1 - param_name );
	name_list[2] = g_strdup( ind_end );

	++ind_beg;
	ind_end[0] = '\0';
	list_comma = g_strsplit( ind_beg, ",", -1 );
	for( pos = list_comma; *pos; ++pos ){
		pos_points = g_strstr_len( *pos, -1, ".." );
		if( pos_points == NULL ){
			name_list[1] = *pos;
			pname = g_strjoinv( "", name_list );
			create_param_desc_simple( db, pname, param_type, offset, element_count, mp, desc );
			g_free( pname );
		}
		else{
			/* check is interval of symbols (1..A or a..z and so on ) */
			num_end = strlen( *pos );
			if( num_end < 4 ){
				g_printerr( "\n** ERROR in parsing string '%s' (string length < 4) \n", *pos );
				g_warn_if_reached();
				continue;
			}
			if( num_end == 4 && *pos + 1 == pos_points ){
				/* use symbol as index */
				num_beg = (*pos)[0];
				num_end = (*pos)[3];
				name_list[1] = g_malloc0(2);
				for( ; num_beg <= num_end; ++num_beg ){
					name_list[1][0] = num_beg;
					pname = g_strjoinv( "", name_list );
					create_param_desc_simple( db, pname, param_type, offset, element_count, mp, desc );
					g_free( pname );
				}
				g_free( name_list[1] );
				continue;
			}
			/* number as index */
			num_beg = strtol( *pos, &pname, 10 );
			if( pname != pos_points ){
				g_printerr( "\n** ERROR in parsing string '%s' (num_beg) \n", *pos );
				g_return_if_reached();
			}
			num_end = strtol( pos_points + 2, &pname, 10 );
			if( *pname != 0 ){
				g_printerr( "\n** ERROR in parsing string '%s' (num_end) \n", *pos );
				g_return_if_reached();
			}
			for( ; num_beg <= num_end; ++num_beg ){
				name_list[1] = g_strdup_printf( "%d", num_beg );
				pname = g_strjoinv( "", name_list );
				create_param_desc_simple( db, pname, param_type, offset, element_count, mp, desc );
				g_free( name_list[1]);
				g_free( pname );
			}
		}
	}

	g_strfreev( list_comma );
	ind_end[0] = ']';
	g_free( name_list[0] );
	g_free( name_list[2] );
}

#define DEFAULT_MEASURE "M"

/* converting string "20(CM)" to double per 0.01mm */
static double str2cmm( gchar *str )
{
	double	d;
	gchar	*endpos;

	d = 0;
	d = prog_strtod( str, &endpos );
	str = strstr( endpos, "(" );
	if( str == NULL )
		d *= prog_rc_get_unit( DEFAULT_MEASURE ) / prog_rc_get_unit( "M" ) * 1e+5;
	else{
		endpos = strstr( str, ")" );
		if(endpos == NULL ){
			g_printerr( "\n ERROR in parsing '%s'\n", str );
			return 0;
		}
		*endpos = 0;
		d *= prog_rc_get_unit( str + 1 ) / prog_rc_get_unit( "M" ) * 1e+5;
		*endpos = ')';
	}
	return d;
}

typedef enum{
	TOOL_NAME_IDX,
	PARAM_NAME_IDX,
	PARAM_TYPE_IDX,
	PARAM_MP_IDX
} NameIndex;
static char8** data_block_add_params_from_list( DataBlock* db, char8 **ptr )
{
	GHashTable	*shortcuts;
	gint		ref, name;
	char8		*param_name;
	char8		*param_desc;
	ParLogType	param_type;
	size_t		element_count;
	int32		size;
	gchar		**name_list;
	char8		*pos, *pp;
	size_t		type_idx;
	fixed32_5	mp;

	shortcuts = g_hash_table_new( g_direct_hash, g_direct_equal );
	element_count = 0;

	for( ; *ptr != NULL; ++ptr ){
		if( g_str_has_prefix( *ptr, "<SHORTCUT " ) == TRUE ){
			if( element_count != 0 )
				/* this shortcut is not from begin of this block and means the ending of current block */
				break;
			/* store shortcut in hash table */
			ref = name = 0;
			pos = strstr( *ptr, "REF=\"" );
			if( pos != NULL ){
				pos += 5;
				pp = strstr( pos, "\"" );
				if( pp != NULL ){
					*pp = 0;
					ref = g_quark_from_string( pos );
					*pp = '"';
				}
			}

			pos = strstr( *ptr, "NAME=\"" );
			if( pos != NULL ){
				pos += 6;
				pp = strstr( pos, "\"" );
				if( pp != NULL ){
					*pp = 0;
					name = g_quark_from_string( pos );
					*pp = '"';
				}
			}

			if( ref != 0 && name != 0 )
				g_hash_table_insert( shortcuts, GINT_TO_POINTER(ref), GINT_TO_POINTER(name) );
			continue;
		}
		if( g_str_has_prefix( *ptr, "<CALC " ) == TRUE ){
			/* reading CALC plug-in data */
			db_read_calc_from_list( ptr );
			continue;
		}
		if( **ptr == '{' ){
			name_list = g_strsplit( *ptr, ":", 4 );
			if( g_strv_length( name_list ) < 3 ){
				g_strfreev( name_list );
				continue;
			}
			/* searching parameter type */
			g_strstrip( name_list[PARAM_TYPE_IDX] );
			size = 0;
			for( type_idx = 0; type_idx < LOG_TYPES_COUNT; ++type_idx ){
				if( g_str_has_prefix( name_list[PARAM_TYPE_IDX], data_types[type_idx].name ) ){
					param_type = data_types[type_idx].type;
					size = data_types[type_idx].size;
					break;
				}
			}
			if( type_idx == LOG_TYPES_COUNT ){
				g_printerr( "\nError parsing DATA_BLOCK parameter '%s'\n Unknown type\n", *ptr );
				g_return_val_if_reached( NULL );
			}

			/* extracting element count from type */
			pos = g_strstr_len( name_list[PARAM_TYPE_IDX], -1, "[" );
			if( pos == NULL )
				element_count = 1;
			else
				sscanf( pos + 1, "%d", &element_count );

			g_strstrip( name_list[PARAM_NAME_IDX] );

			if( strcmp( name_list[TOOL_NAME_IDX], "{}" ) == 0 ){
				if( db->posdesc == NULL )
					db->posdesc = ppd_new();
				ppd_add_info( db->posdesc, name_list[PARAM_NAME_IDX], param_type, db->data_size );
				db->data_size += size;
			}
			else{
				mp = 0;
				param_desc = NULL;
				if( name_list[PARAM_MP_IDX] != NULL ){
					mp = str2cmm( g_strstrip( name_list[PARAM_MP_IDX] ) );
					param_desc = strstr( name_list[PARAM_MP_IDX], "<desc " );
				}
				else
					param_desc = strstr( name_list[PARAM_TYPE_IDX], "<desc " );

				/* extract tool name from shortcut */
				name = GPOINTER_TO_INT(g_hash_table_lookup( shortcuts, GINT_TO_POINTER(g_quark_from_string( name_list[TOOL_NAME_IDX] )) ));
				if( name != 0 )
					param_name = g_strconcat( g_quark_to_string( name ), ":", name_list[PARAM_NAME_IDX], NULL );
				else
					param_name = g_strdup( name_list[PARAM_NAME_IDX] );

				create_param_desc_complex( db, param_name, param_type, &db->data_size, element_count, mp, param_desc );
				g_free( param_name );
			}
			g_strfreev( name_list );
		}
	}
	g_hash_table_destroy( shortcuts );

	/* add end indicator */
	g_ptr_array_add( db->params, NULL );

	return ptr;
}

static char8** data_block_add_params_from_list_NEW_FORMAT( DataBlock* db, char8 **ptr );

static void data_block_new_read_from_file_NEW_FORMAT( const char8 *header_str, uint32 data_block_size, GInputStream *in )
{
    DBContainer *dbc;
    DataBlock   *db;
    char8       **list, **ptr;
    uint32      data_size;
    uint32      param_size;
    uint32      count;
    void        *buf;
    void        *data;
    ParamData   pd;
    ParamArray  *pos_array;
    ParamDesc   **param;
    ParamData   *ppd;
    goffset     offset;
    int j;

    if( data_containers == NULL )
        data_containers = g_ptr_array_new_with_free_func( (GDestroyNotify)dbc_free );

    /* read records count */
    data_block_size -= g_input_stream_read( in, &count, sizeof(count), NULL, NULL );

    data_size = 0;
    list = g_strsplit( header_str, "\n", -1 );
    for( ptr = list; *ptr != NULL; ++ptr ){
        if( g_str_has_prefix( *ptr, "<PARAMETERS" ) != FALSE )
            break;
    }
    ++ptr;
    db = g_slice_new0( DataBlock );
    db->params = g_ptr_array_new();
    db->records_count = count;

    dbc = dbc_new();
    g_ptr_array_add( dbc->blocks, db );

    ptr = data_block_add_params_from_list_NEW_FORMAT( db, ptr );
    if( db->posdesc == NULL ){
        if( data_blocks == NULL ){
            data_blocks = g_ptr_array_new();
        }
        g_ptr_array_add( data_blocks, db );
    }

    data_size += db->data_size;
    g_strfreev( list );

    g_warn_if_fail( data_block_size % data_size == 4 || data_block_size % data_size == 5 );
    g_warn_if_fail( count == data_block_size / data_size );

    db->data_begin = g_seekable_tell( G_SEEKABLE(in) );

    /* create ParamArray for copy with position and empty data */
    buf = NULL;
    pos_array = parr_create();
    if( db->posdesc != NULL ){
        pd.value = 0;

        /// XXX no time for extracting real position description
        buf = g_malloc( count * 2 *sizeof(uint32) );
        data_block_size -= g_input_stream_read( in, buf, count * 2 *sizeof(uint32), NULL, NULL );

        data = buf;
        for( j = 0; j < count; ++j ){
            ppd_extract( db->posdesc, data, &pd.position );
            parr_add_data( pos_array, pd );
            data = (uint8*)data + sizeof(uint32);
        }
    }

    /* read other data blocks */
    param = (ParamDesc**)&g_ptr_array_index( db->params, 0 );
    for( ; *param != NULL; ++param ){
        param_size = data_types[(*param)->type].size * (*param)->count;
        if( (*param)->parr == NULL ){
            data_block_size -= g_input_stream_skip( in, param_size * count, NULL, NULL );
            continue;
        }
        parr_dup_data( pos_array, (*param)->parr );
        if( (*param)->count == 1 ){
            buf = g_realloc( buf, count * param_size );
            data_block_size -= g_input_stream_read( in, buf, count * param_size, NULL, NULL );

            data = buf;
            for( j = 0; j < count; ++j ){
                ppd = parr_get_data( (*param)->parr, j );
                ppd->value = data_types[(*param)->type].conv2float64( data );
                data = (uint8*)data + param_size;
            }
        }
        else /* if( (*param)->count > 1 ) */{
            offset = g_seekable_tell( G_SEEKABLE(in) );
            for( j = 0; j < count; ++j ){
                ppd = parr_get_data( (*param)->parr, j );
                ppd->offset = offset;
                offset += param_size;
            }
            data_block_size -= g_input_stream_skip( in, param_size * count, NULL, NULL );
        }
    }

    // XXX remove depth overlap in parameter's arrays
//      param = (ParamDesc**)&g_ptr_array_index( db_arr[i]->params, 0 );
//      for( ; *param != NULL; ++param )
//          parr_remove_depth_overlap( (*param)->parr );
    g_free( buf );
    parr_destroy( pos_array );

    param = (ParamDesc**)&g_ptr_array_index( db->params, 0 );
    if( (*param)->parr == NULL )
        g_ptr_array_remove_index( db->params, 0 );

    if( data_blocks == NULL ){
        data_blocks = g_ptr_array_new();
    }
    g_ptr_array_add( data_blocks, db );

    g_warn_if_fail( data_block_size == 4 || data_block_size == 5 );
    g_input_stream_skip( in, data_block_size, NULL, NULL );
}

static char8** data_block_add_params_from_list_NEW_FORMAT( DataBlock* db, char8 **ptr )
{
    GHashTable  *shortcuts;
    gint        ref, name;
    char8       *param_name;
    char8       *param_desc;
    ParLogType  param_type;
    size_t      element_count;
    int32       size;
    gchar       **name_list;
    char8       *pos, *pp;
    size_t      type_idx;
    fixed32_5   mp;

    shortcuts = g_hash_table_new( g_direct_hash, g_direct_equal );
    element_count = 0;

    for( ; *ptr != NULL; ++ptr ){
        if( g_str_has_prefix( *ptr, "<SHORTCUT " ) == TRUE ){
            if( element_count != 0 )
                /* this shortcut is not from begin of this block and means the ending of current block */
                break;
            /* store shortcut in hash table */
            ref = name = 0;
            pos = strstr( *ptr, "REF=\"" );
            if( pos != NULL ){
                pos += 5;
                pp = strstr( pos, "\"" );
                if( pp != NULL ){
                    *pp = 0;
                    ref = g_quark_from_string( pos );
                    *pp = '"';
                }
            }

            pos = strstr( *ptr, "NAME=\"" );
            if( pos != NULL ){
                pos += 6;
                pp = strstr( pos, "\"" );
                if( pp != NULL ){
                    *pp = 0;
                    name = g_quark_from_string( pos );
                    *pp = '"';
                }
            }

            if( ref != 0 && name != 0 )
                g_hash_table_insert( shortcuts, GINT_TO_POINTER(ref), GINT_TO_POINTER(name) );
            continue;
        }
        if( g_str_has_prefix( *ptr, "<CALC " ) == TRUE ){
            /* reading CALC plug-in data */
            db_read_calc_from_list( ptr );
            continue;
        }
        if( **ptr == '[' ){
            pos = strchr( *ptr, '{' );
            if( pos == NULL )
                continue;
            name_list = g_strsplit( pos, ":", 4 );
            if( g_strv_length( name_list ) < 3 ){
                g_strfreev( name_list );
                continue;
            }
            /* searching parameter type */
            g_strstrip( name_list[PARAM_TYPE_IDX] );
            size = 0;
            for( type_idx = 0; type_idx < LOG_TYPES_COUNT; ++type_idx ){
                if( g_str_has_prefix( name_list[PARAM_TYPE_IDX], data_types[type_idx].name ) ){
                    param_type = data_types[type_idx].type;
                    size = data_types[type_idx].size;
                    break;
                }
            }
            if( type_idx == LOG_TYPES_COUNT ){
                g_printerr( "\nError parsing DATA_BLOCK parameter '%s'\n Unknown type\n", *ptr );
                g_return_val_if_reached( NULL );
            }

            /* extracting element count from type */
            pos = g_strstr_len( name_list[PARAM_TYPE_IDX], -1, "[" );
            if( pos == NULL )
                element_count = 1;
            else
                sscanf( pos + 1, "%d", &element_count );

            g_strstrip( name_list[PARAM_NAME_IDX] );

            if( strcmp( name_list[TOOL_NAME_IDX], "{}" ) == 0 ){
                if( db->posdesc == NULL )
                    db->posdesc = ppd_new();
                if( ppd_add_info_NEW_FORMAT( db->posdesc, name_list[PARAM_NAME_IDX], param_type, db->records_count, strstr( name_list[PARAM_TYPE_IDX], "<desc " ) ) == FALSE ){
                    /* add Position description to DataBlock */
                    ParamDesc *par = g_new0( ParamDesc, 1 );
                    par->type = param_type;
                    par->count = element_count;
                    g_ptr_array_add( db->params, par );
                }
                db->data_size += size;
            }
            else{
                mp = 0;
                param_desc = NULL;
                if( name_list[PARAM_MP_IDX] != NULL ){
                    mp = str2cmm( g_strstrip( name_list[PARAM_MP_IDX] ) );
                    param_desc = strstr( name_list[PARAM_MP_IDX], "<desc " );
                }
                else
                    param_desc = strstr( name_list[PARAM_TYPE_IDX], "<desc " );

                /* extract tool name from shortcut */
                name = GPOINTER_TO_INT(g_hash_table_lookup( shortcuts, GINT_TO_POINTER(g_quark_from_string( name_list[TOOL_NAME_IDX] )) ));
                if( name != 0 )
                    param_name = g_strconcat( g_quark_to_string( name ), ":", name_list[PARAM_NAME_IDX], NULL );
                else
                    param_name = g_strdup( name_list[PARAM_NAME_IDX] );

                create_param_desc_complex( db, param_name, param_type, &db->data_size, element_count, mp, param_desc );
                g_free( param_name );
            }
            g_strfreev( name_list );
        }
    }
    g_hash_table_destroy( shortcuts );

    /* add end indicator */
    g_ptr_array_add( db->params, NULL );

    return ptr;
}
