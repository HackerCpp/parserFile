#include "lis_export.h"
#include <string.h>
#include <locale.h>
#include <gio/gio.h>
#include <glib/gstdio.h>
#include <math.h>
#include "lis.h"
#include "unicode.h"
#include "top_bottom.h"
#include "lis_data.h"
#include "compress.h"
#include "edit_mnemonic.h"
#include <windows.h>

#include "gfmfile/data_types.h"
#include "program.h"

#include "params_xml.h"

#define	DEFAULT_FRAME_SIZE		16000

static GOutputStream	*lis_out = NULL;
static GInputStream 	*gfm_in = NULL;
static TIFSave		tif_save = TIF_SAVE;
static GData		*well_data = NULL;
static GData		*well_data_desc = NULL;
static GDateTime	*strt_record = NULL;
static GPtrArray	*numb_mnem = NULL;
static GPtrArray	*numb_num = NULL;

static uint32		lis_data_block_size = 16000;
static uint32		frame_size = 16000;
static uint32		max_elem_count = 0;

static void read_gfmfile( char8 *gfm_filename );
/* reading localized well info mnemonic description */
static GData* read_well_info_desc();
static void curve_info( LisBlock *block );
static void write_data( float64 first, float64 last, float64 step, int32 ModeTime, GOutputStream *out, TIFSave tif_save );

/* Date of generation for the software: Year[2] + '/' + Month[2] + '/' + Day[2] */
static const char8* lis_library_creation_date();

typedef struct _ParameterResampling{
	union{
		uint32	count;				/* count of using parameters values for resampling */
		uint32	index;				/* index of using parameters values for resampling if indexes and fractions are NULL */
	};
	uint32		*indexes;			/* indexes array of parameters for resampling */
	float64		*fractions;			/* fractions array for corresponding parameter's index */
} ParResampl;

static inline const char8* cut_shortcut( const char8 *str )
{
	char8	*out;

	if( str == NULL )
		return NULL;
	out = strstr( str, ":" );
	if( out != NULL )
		return out + 1;

	return str;
}

static inline const char8* cut_log( const char8 *str )
{
	char8	*out;

	if( str == NULL )
		return NULL;
	out = strstr( str, "." );
	if( out != NULL )
		return out + 1;

	return str;
}


EXTERN void exportGFMToLis( char8 *gfm_filename )
{
	char8		*lis_filename;
	GFile		*lis_file;
	char		*old_locale;
	GByteArray	*block;
	FileRecord	file_rec;
	char8		**mnemonics;
	ParamDesc	*desc;
	char8		*str;
	char8		*pos;
	float32		value;
	uint32	i;

	ExportMode	mode;

	lis_out = NULL;
	gfm_in = NULL;
	tif_save = TIF_SAVE;
	well_data = NULL;
	well_data_desc = NULL;
	strt_record = NULL;
	numb_mnem = NULL;
	numb_num = NULL;

	lis_data_block_size = 16000;
	frame_size = 16000;
	max_elem_count = 0;

    read_gfmfile( gfm_filename );
//    arr_mnemonics = g_array_sized_new (FALSE, FALSE, sizeof (Replay_names), 1);

    data_block_get_start_stop( &mode.start_m_5, &mode.stop_m_5, &mode.end_sec_3 );
    mode.step_m_5 = 0.1 * 1e5;
	prog_get_pref6s_int32( "mode_step_m_5", &mode.step_m_5 );
	if( mode.start_m_5 > mode.stop_m_5 )
		mode.step_m_5 = -mode.step_m_5;
	mode.step_sec_3 = 1 * 1e3;
	mode.begin_sec_3 = 0;
    mode.is_time_mode = FALSE;

	lis_filename = NULL;
    if( top_bottom_run( &mode ) ){
        prog_put_pref6s_int32( "mode_step_m_5", ABS(mode.step_m_5) );
		if( is_tif_block == TRUE )
			tif_save = TIF_SAVE;
		else
			tif_save = TIF_NOT_USE;

		lis_filename = g_strdup( gfm_filename );
		lis_filename[ strlen(lis_filename) - 3 ] = 0;
		strcat( lis_filename, "lis" );
		g_print( "\n%s\n", lis_filename );

		lis_file = g_file_new_for_path( lis_filename );
		lis_out = G_OUTPUT_STREAM(g_file_replace( lis_file, NULL, FALSE, G_FILE_CREATE_REPLACE_DESTINATION, NULL, NULL ));

		old_locale = setlocale( LC_ALL, "C" );

		bind_textdomain_codeset( PACKAGE, OUT_CODESET );

		lis_block_write_init();

		block = g_byte_array_new();

        // file header record
		memset( &file_rec, ' ', sizeof(file_rec) );
		file_rec.logic_rec_head = (LRecHead){ .type = 128, .reserved = 0 };
		file_rec.file_type = LO;
		strncpy( file_rec.file_name, "KEDR-05", 7 );
		strncpy( file_rec.vers_soft, version(), MIN( strlen(version()), sizeof(file_rec.vers_soft) ) );
		strncpy( file_rec.date_soft, lis_library_creation_date(), sizeof(file_rec.date_soft) );
        // calculate frame size
		frame_size = 0;
		max_elem_count = 0;
		for( i = 0; i < params->len; ){
			desc = g_ptr_array_index( params, i );
			if( desc == NULL || (desc->flags & SELECTED) == 0 ){
				g_ptr_array_remove_index( params, i );
				continue;
			}
            if( (desc->flags & MAGNETIC_MARK) == 0 && parr_get_last_data( desc->parr ) == NULL ){
                g_printerr( "\n** Array of parameter '%s' is empty", desc->entmnem );
                g_ptr_array_remove_index( params, i );
                g_warn_if_reached();
                continue;
            }
			frame_size += desc->count * MAX( data_types[desc->type].size, 2 );
			max_elem_count = MAX( desc->count, max_elem_count );
			++i;
		}
		lis_data_block_size = MAX( frame_size + 100, DEFAULT_FRAME_SIZE );
		str = g_strdup_printf( "%d", lis_data_block_size );
		strncpy( file_rec.max_rec_length, str, strlen( str ) );
		g_free( str );

		lis_block_add_data( block, &file_rec, sizeof(file_rec) );
		lis_block_write( block, lis_out, tif_save );

        // well information table
		lis_block_add_data( block, &(LRecHead){ .type = 34, .reserved = 0 }, sizeof(LRecHead) );
        // fill well info gfm_in table CONS
		lis_block_add_compon_block( block, 73, 'A', "TYPE", "", "CONS" );
		mnemonics = (char8*[]){                                     "MNEM", "STAT", "PUNI", "TUNI", "VALU", NULL };
		lis_block_add_compon_block_list( block, "AAAAA", mnemonics, "EQUI", "ALLO",     "",     "",  "dev" );
		lis_block_add_compon_block_list( block, "AAAAA", mnemonics, "CNCU", "ALLO",     "",     "",	  g_datalist_get_data( &well_data, "[ORDER]" ) );
		lis_block_add_compon_block_list( block, "AAAAA", mnemonics,   "CN", "ALLO",     "",     "",	  g_datalist_get_data( &well_data, "[COMP]" ) );
		lis_block_add_compon_block_list( block, "AAAAA", mnemonics,   "WN", "ALLO",     "",     "",	  g_datalist_get_data( &well_data, "[WELL]" ) );
		lis_block_add_compon_block_list( block, "AAAAA", mnemonics,   "FN", "ALLO",     "",     "",	  g_datalist_get_data( &well_data, "[FIELD]" ) );
		lis_block_add_compon_block_list( block, "AAAAA", mnemonics, "DATE", "ALLO",     "",     "",	  g_datalist_get_data( &well_data, "[DATE]" ) );
		lis_block_add_compon_block_list( block, "AAAAD", mnemonics,  "TLI", "ALLO",    "M",    "M",	  MAX( mode.start_m_5, mode.stop_m_5 ) / 1e+5f );
		lis_block_add_compon_block_list( block, "AAAAD", mnemonics,  "BLI", "ALLO",    "M",    "M",	  MIN( mode.start_m_5, mode.stop_m_5 ) / 1e+5f );

		/// TODO read real acoustic parameters descriptions
        // save acoustic description
		for( i = 0; i < params->len; ++i ){
			desc = g_ptr_array_index( params, i );
			if( desc->desc == NULL || strstr( desc->desc, "draw_type=\"ACOUSTIC\"" ) == NULL )
				continue;
			str = g_strdup_printf( "WFZ%c", cut_shortcut( desc->entmnem )[2] );
			pos = strstr( desc->desc, "data_begin=\"" );
			if( pos == NULL )
				value = 0.0;
			else
				value = prog_strtod( pos + strlen( "data_begin=\"" ), NULL );
			lis_block_add_compon_block_list( block, "AAAAD", mnemonics,  str, "ALLO",   "US",   "US",	  value );
			g_free( str );

			str = g_strdup_printf( "WFS%c", cut_shortcut( desc->entmnem )[2] );
			pos = strstr( desc->desc, "data_step=\"" );
			if( pos == NULL )
				value = 2.0;
			else
				value = prog_strtod( pos + strlen( "data_step=\"" ), NULL );
			lis_block_add_compon_block_list( block, "AAAAD", mnemonics,  str, "ALLO",   "US",   "US",	  value );
			g_free( str );
		}
		lis_block_write( block, lis_out, tif_save );

        // tools information table
		if( numb_mnem != NULL ){
			lis_block_add_data( block, &(LRecHead){ .type = 34, .reserved = 0 }, sizeof(LRecHead) );
            // fill well info gfm_in table NUMB
			lis_block_add_compon_block( block, 73, 'A', "TYPE", "", "NUMB" );
			mnemonics = (char8*[]){                                      "MNEM", "TYPS", "TYPC", "NUM", NULL };
			for( i = 0; i < numb_mnem->len; ++i ){
				str = g_ptr_array_index( numb_mnem, i );
                lis_block_add_compon_block_list( block, "AAAA", mnemonics,  str, "NSTR",   "",    g_ptr_array_index( numb_num, i ) );
			}
			lis_block_write( block, lis_out, tif_save );
		}

        // Data Format Specification Record
		lis_block_add_data( block, &(LRecHead){ .type = 64, .reserved = 0 }, sizeof(LRecHead) );
        // entry type - 4, direction up/down (1/255)
		lis_block_add_entry_block( block, 4, 'B', (mode.step_m_5 > 0)? 255 : 1 );
        // entry type - 5, depth units (255 - meters)
		lis_block_add_entry_block( block, 5, 'B', 255 );
        // entry type - 8, depth step value
		lis_block_add_entry_block( block, 8, 'D', fabs( mode.step_m_5 ) / 1e+3 );
        // entry type - 9, depth step units
		lis_block_add_entry_block( block, 9, 'A', "CM  " );
        // entry type - 12, invalid value
		lis_block_add_entry_block( block, 12, 'D', invalid_value );
        // entry type - 13, depth record mode (1 - depth occurs only once per data record preceding first frame)
		lis_block_add_entry_block( block, 13, 'B', 1 );
        // entry type - 14, depth units
		lis_block_add_entry_block( block, 14, 'A', "CM  " );
        // entry type - 15, depth representation code
		lis_block_add_entry_block( block, 15, 'B', 'I' );
        // entry type - 16, sub-type number of datum specification block
		lis_block_add_entry_block( block, 16, 'B', 0 );
        // entry type - 0, last entry block gfm_in list
		lis_block_add_entry_block( block, 0, 'B', 0 );
        // Datum Specification Block
		curve_info( block );
		lis_block_write( block, lis_out, tif_save );

        // Normal Data Record
		if( mode.is_time_mode == FALSE )
			write_data( mode.start_m_5 * 1e-5, mode.stop_m_5 * 1e-5, mode.step_m_5 * 1e-5, mode.is_time_mode, lis_out, TIF_SAVE );
		else
			write_data( mode.begin_sec_3 * 1e-3, mode.end_sec_3 * 1e-3, mode.step_sec_3 * 1e-3, mode.is_time_mode, lis_out, TIF_SAVE );

        // file trailer record
		file_rec.logic_rec_head.type = 129;
		lis_block_add_data( block, &file_rec, sizeof(file_rec) );
		lis_block_write( block, lis_out, tif_save );

        // last block
		if( tif_save == TIF_SAVE )
			tif_save = TIF_FINISH;
		lis_block_write( block, lis_out, tif_save );

		g_byte_array_free( block, TRUE );

		g_output_stream_close( lis_out, NULL, NULL );
		g_object_unref( lis_out );
		g_object_unref( lis_file );

		bind_textdomain_codeset( PACKAGE, "UTF-8" );
		setlocale( LC_ALL, old_locale );
	}
	data_blocks_free();
	g_datalist_clear( &well_data );
	g_datalist_clear( &well_data_desc );
	if( numb_mnem != NULL ){
		g_ptr_array_free( numb_mnem, TRUE );
		numb_mnem = NULL;
		g_ptr_array_unref( numb_num );
	}

	if( strt_record != NULL ){
		g_date_time_unref( strt_record );
		strt_record = NULL;
	}

	g_free( lis_filename );

	g_input_stream_close( G_INPUT_STREAM(gfm_in), NULL, NULL );

    destroy_arr_mnemonics();
    prog_show_message(PROG_MESSAGE_INFO, TRUE, _("Information!"), _("Conversion completed"), " ");
}

static void read_gfmfile( char8 *gfm_filename )
{
	GFile 			*gfm_file;
	uint16			symbol;
	uint16			len16;
	uint16			*buf16;
	uint16			*str16;
	char8			*buf8;
	uint32			len32;
	gchar			**list_str;
	gchar			**pos;
	gchar			*str;
	size_t			data_block_size;

	gfm_file = g_file_new_for_path( gfm_filename );
	gfm_in = G_INPUT_STREAM(g_file_read( gfm_file, NULL, NULL ));

    // read symbol
	g_input_stream_read( gfm_in, &symbol, sizeof(symbol), NULL, NULL );

    // check GFM signature
	str16 = utf8_to_utf16( utf16_type( symbol ), GFM_FILE_SIGNATURE, -1, NULL, &len32, NULL );
	buf16 = g_malloc( len32 );
	g_input_stream_read( gfm_in, buf16, len32, NULL, NULL );
    if( memcmp( str16, buf16, len32 ) != 0 ){
		// TODO show message and correct file closing procedure
//		show_message( NULL, GTK_MESSAGE_ERROR, TRUE, _("Error"), _("Error opening"), _("Missed GFM signature in file\n\n'%s'"), gfm_filename );
		g_printerr( "\n Error opening, Missed GFM signature gfm_in file '%s'", gfm_filename );
		g_object_unref( gfm_in );
		g_free( gfm_filename );
		g_free( str16 );
		g_free( buf16 );
		return;
	}

    // searching line block name
    while( g_input_stream_read( gfm_in, &len16, sizeof(len16), NULL, NULL ) ){
		if( len16 == 0 )
			break;
		len16 /= 2;
		buf16 = g_new( uint16, len16 + 1 );
		g_input_stream_read( gfm_in, buf16, 2*len16, NULL, NULL );
		buf16[ len16 ] = 0;
		buf8 = utf16_to_char8bit( utf16_type(symbol), buf16, len16, OUT_CODESET, NULL, NULL, NULL );
		g_free( buf16 );
        // read block length
		g_input_stream_read( gfm_in, &len32, sizeof(len32), NULL, NULL );
        if( strcmp( buf8, "[DATA_BLOCK]" ) == 0 ){
			g_free( buf8 );
			data_block_size = len32;

			len32 = g_seekable_tell( G_SEEKABLE(gfm_in) );
			data_block_new_read_from_file( symbol, data_block_size, gfm_in );
            /// check data block reading
			g_warn_if_fail( g_seekable_tell( G_SEEKABLE(gfm_in) ) == len32 + data_block_size );
		}
        else if( strcmp( buf8, "[HEADER]" ) == 0 ){
			g_free( buf8 );

            // read text
			len32 /= 2;
			buf16 = g_new( uint16, len32 + 1 );
			g_input_stream_read( gfm_in, buf16, 2*len32, NULL, NULL );
			buf16[ len32 ] = 0;
			buf8 = utf16_to_char8bit( utf16_type(symbol), buf16, len32, OUT_CODESET, NULL, NULL, NULL );
			if(buf8 == NULL){
				buf8 = g_malloc(len32 + 1);
				CharToOemW((wchar_t*)buf16, buf8);
			}
			g_free( buf16 );

			g_datalist_init( &well_data );
			list_str = g_strsplit( buf8, "\n", -1 );
			g_free( buf8 );
			pos = list_str;
			while( *pos != NULL ){
                // working with string records "[mnemonic]data"
				g_strstrip( *pos );
				str = strstr( *pos, "]" );
				if( str != NULL ){
					*++str = 0;
					str = g_strstrip(str + 1);

					if( strcmp( *pos, "[DATE]") == 0 ){
						buf8 = strstr( str, " " );
						if( buf8 != NULL )
							*buf8 = 0;
					}

					g_datalist_set_data_full( &well_data, *pos, g_strdup( str ), g_free );
				}
				++pos;
			}
			g_strfreev( list_str );

			well_data_desc = read_well_info_desc();
		}
		else if( strcmp( buf8, "[LIS]" ) == 0 ){
			g_free( buf8 );

            // read GZIP data
			buf16 = g_malloc( len32 );
			g_input_stream_read( gfm_in, buf16, len32, NULL, NULL );
            // remove line-break symbols
			decompress_data( buf16 + 2, len32 - 4*2, (void**)&buf8, &len32 );
			g_free( buf16 );

			list_str = g_strsplit( buf8, "\n", -1 );
			g_free( buf8 );
			for( pos = list_str; *pos != NULL; ++pos ){
				if( g_str_has_prefix( *pos, "<table ") == FALSE )
					continue;
				str = strstr( *pos, "name=\"" );
				if( str == NULL ){
					g_printerr( "\n ** ERROR table name not fount in '%s'", *pos );
					break;
				}
				else
					str += strlen( "name=\"" );

				if( strncmp( str, "NUMB", 4 ) == 0 ){
                    // working with string records <module MNEM="XXXX" NUM="99"/>
					numb_mnem = g_ptr_array_new_with_free_func( g_free );
					numb_num = g_ptr_array_new_with_free_func( g_free );
					do{
						++pos;
						if( g_str_has_prefix( *pos, "<module ") == FALSE )
							break;
						buf8 = strstr( *pos, "MNEM=\"" ) + strlen("MNEM=\"");
						str = strstr( buf8, "\"" );
						*str = 0;
						g_ptr_array_add( numb_mnem, g_strdup( buf8 ) );

						buf8 = strstr( str + 1, "NUM=\"" ) + strlen("NUM=\"");
						str = strstr( buf8, "\"" );
						*str = 0;
						g_ptr_array_add( numb_num, g_strdup( buf8 ) );

					}while(1);
				}


				g_strstrip( *pos );
				str = strstr( *pos, "]" );
				if( str != NULL ){
					*++str = 0;
					g_datalist_set_data_full( &well_data, *pos, g_strdup(g_strstrip(str + 1)), g_free );
				}
			}
			g_strfreev( list_str );

			well_data_desc = read_well_info_desc();
		}
		else{
			g_free( buf8 );
			g_input_stream_skip( gfm_in, len32, NULL, NULL );
		}
    }
}

/* reading localized well info mnemonic description */
static GData* read_well_info_desc()
{
	FILE	*file;
	uint16	*buf16;
	char8	*buf8;
	gchar	**list_str;
	gchar	**pos;
	uint16	len16;
	char8	*str;
	GData	*res;

	/* reading localized well info mnemonic description */
	file = g_fopen( SETTINGSLOCDIR("well_info.txt", UTF8), "rb" );
	if( file == NULL ){
		g_printerr( "cannot open file '%s'\n", SETTINGSLOCDIR("well_info.txt", UTF8) );
		g_return_val_if_reached( NULL );
	}
	fseek( file, 0, SEEK_END );
	len16 = ftell( file ) / sizeof(uint16);
	fseek( file, 0, SEEK_SET );

	buf16 = g_new( uint16, len16 + 1 );
	fread( buf16, sizeof(uint16), len16, file );
	buf16[len16] = 0;
	fclose( file );

	buf8 = utf16_to_char8bit( UT_LE, buf16, len16, OUT_CODESET, NULL, NULL, NULL );
	g_free( buf16 );

	list_str = g_strsplit( buf8, "\n", -1 );
	g_free( buf8 );
	g_datalist_init( &res );
	pos = list_str;
	while( *pos != NULL ){
		g_strstrip( *pos );
		str = strstr( *pos, "]" );
		if( str != NULL ){
			*++str = 0;
			g_datalist_set_data_full( &res, *pos, g_strdup(g_strstrip(str + 1)), g_free );
		}
		++pos;
	}
	g_strfreev( list_str );

	return res;
}

static void curve_info( LisBlock *block )
{
	ParamDesc		*desc;
	SpecBlock		sb;
	gchar			**list;
	char8			*str, *str1;
	int idx;

	for( idx = 0; idx < params->len; ++idx ){
		desc = g_ptr_array_index( params, idx );

		if( (desc->flags & SELECTED) == 0 )
			continue;

		const char8 *xml_mnem = params_xml_table_get_lis_mnem(desc->entmnem);
		if(xml_mnem)
			str = g_strdup(xml_mnem);
		else
			str = prog_string_transform( desc->entmnem, "LIS" );
//		str1 = g_convert( str, -1, OUT_CODESET, "UTF-8", NULL, NULL, NULL );

		bool32	need_cmp = FALSE;
        if(strcmp(str, desc->entmnem) == 0)
        {
            gchar *str_edit = g_strdup(cut_shortcut(str));
            g_free(str);
            gchar lunit[100];
            lunit[0] = 0;
            edit_mnemonic(str_edit, lunit);
            str = g_strconcat(str_edit, ".",lunit, NULL);
            g_free(str_edit);
        }
        else
        	need_cmp = TRUE;

        str1 = g_convert( str, -1, OUT_CODESET, "UTF-8", NULL, NULL, NULL );
        list = g_strsplit( cut_shortcut( str1 ), ".", 2 );
		g_free( str );
		g_free( str1 );

		if(need_cmp)
			cmp_mnem_with_arr(list[0], list[1]);

		memset( &sb, 0, sizeof(sb) );
		memset( sb.str_data, ' ', sizeof(sb.str_data) );
		str_copy4( sb.mnemonic, list[0] );
		str_copy4( sb.units, list[1] );
		sb.number_samples = 1;
		if( desc->type == LOG_UINT16 || desc->type == LOG_INT16 || desc->type == LOG_UINT8 || desc->type == LOG_INT8 ){
			sb.repr_code = 'O';
			sb.size = 2 * desc->count;
		}
		else if( desc->type == LOG_UINT32 || desc->type == LOG_INT32 ){
			sb.repr_code = 'I';
			sb.size = 4 * desc->count;
		}
		else{
			sb.repr_code = 'D';
			sb.size = 4 * desc->count;
		}
		sb.size = GUINT16_SWAP_LE_BE(sb.size);
		lis_block_add_data( block, &sb, sizeof(sb) );

		g_strfreev( list );
	}
}

static void fill_data_by_depth( ParResampl **pv, size_t param_count, size_t vector_count, fixed32_5 start_m_5, fixed32_5 step_m_5 )
{
	fixed32_5		depth_m_5;
	ParamDesc		*desc;
	size_t 			param_idx;
	size_t			idx;
	float64			value, value_average;
	GArray			*indexes, *fractions;
	ParamData 		*pd;
	ParamData 		*prev_pd;
	int y, i;

	for( param_idx = 0; param_idx < params->len; ++param_idx ){
		desc = g_ptr_array_index( params, param_idx );

		if( parr_get_last_data( desc->parr ) == NULL )
			continue;

		if( desc->flags & MAGNETIC_MARK ){
			idx = 0;
			pd = parr_get_data( desc->parr, idx );
			while( pd != NULL ){
				y = (pd->position.depth_m_5 - start_m_5) / step_m_5;
				if( y >= 0 && y < vector_count )
					pv[param_idx + y * param_count] = g_memdup( &(ParResampl){ .index = idx, .indexes = NULL, .fractions = NULL }, sizeof(ParResampl));
				++idx;
				pd = parr_get_data( desc->parr, idx );
			}
		}
		else if( desc->flags & PEAK_VALUE ){
			/* calculate average value for pick detecting */
			idx = 0;
			pd = parr_get_data( desc->parr, idx );
			value_average = 0;
			for( idx = 0; pd != NULL; ){
				value_average += pd->value;
				++idx;
				pd = parr_get_data( desc->parr, idx );
			}
			if( idx != 0 )
				value_average /= idx;

			idx = 0;
			pd = parr_get_data( desc->parr, idx );
			depth_m_5 = start_m_5 - desc->mp_m_5 - step_m_5/2;
			while( pd != NULL && ((step_m_5 > 0) == (pd->position.depth_m_5 < depth_m_5)) ){
				++idx;
				pd = parr_get_data( desc->parr, idx );
			}
			y = 0;
			while( (step_m_5 > 0) == (y * step_m_5 + start_m_5 - desc->mp_m_5 + step_m_5/2 < pd->position.depth_m_5) )
				++y;
			depth_m_5 = y * step_m_5 + start_m_5  - desc->mp_m_5 - step_m_5/2;

			for( ; y < vector_count && pd != NULL; y++ ){
				pv[param_idx + y * param_count] = g_memdup( &(ParResampl){ .index = idx, .indexes = NULL, .fractions = NULL }, sizeof(ParResampl));
				value = fabs( pd->value - value_average );

				depth_m_5 = y * step_m_5 + start_m_5 - desc->mp_m_5 + step_m_5/2;
				while( pd != NULL && ((step_m_5 > 0) == (pd->position.depth_m_5 < depth_m_5)) ){
					if( value < fabs( pd->value - value_average ) ){
						value = fabs( pd->value - value_average );
						pv[param_idx + y * param_count]->index = idx;
					}
					++idx;
					pd = parr_get_data( desc->parr, idx );
				}
			}
		}
		else if( (desc->flags & AVERAGE) || (desc->flags & SUMMARIZE) ){
			idx = 0;
			pd = parr_get_data( desc->parr, idx );
			depth_m_5 = start_m_5 - desc->mp_m_5 - step_m_5/2;
			prev_pd = NULL;
			while( pd != NULL && ((step_m_5 > 0) == (pd->position.depth_m_5 < depth_m_5)) ){
				prev_pd = pd;
				++idx;
				pd = parr_get_data( desc->parr, idx );
			}

			y = 0;
			if( idx == 0 ){
				while( (step_m_5 > 0) == (y * step_m_5 + start_m_5 - desc->mp_m_5 + step_m_5/2 < pd->position.depth_m_5) )
					++y;
			}
			depth_m_5 = y * step_m_5 + start_m_5  - desc->mp_m_5 - step_m_5/2;

			indexes = g_array_new( FALSE, FALSE, sizeof(uint32) );
			fractions = g_array_new( FALSE, FALSE, sizeof(float64) );
			for( ; y < vector_count && pd != NULL; y++ ){
				if( idx == 0 || prev_pd == NULL )
					value = 1.0;
				else{
					if(prev_pd == NULL)
						value = 1.0;
					else
						value = (float64)(pd->position.depth_m_5 - depth_m_5) / (float64)(pd->position.depth_m_5 - prev_pd->position.depth_m_5);
				}
				g_array_append_val( fractions, value );
				g_array_append_val( indexes, idx );
				if(desc->flags & SUMMARIZE)
					g_print("\n 1--> %d %d %g %d", y, idx, value, depth_m_5);

				if( ((step_m_5 > 0) == (pd->position.depth_m_5 < depth_m_5)) ){
					prev_pd = pd;
					++idx;
					pd = parr_get_data( desc->parr, idx );
				}

				depth_m_5 = y * step_m_5 + start_m_5 - desc->mp_m_5 + step_m_5/2;
				while( pd != NULL && ((step_m_5 > 0) == (pd->position.depth_m_5 < depth_m_5)) ){
					value = 1.0;
					g_array_append_val( fractions, value );
					g_array_append_val( indexes, idx );
					if(desc->flags & SUMMARIZE)
						g_print("\n 2--> %d %d %g %d", y, idx, value, depth_m_5);

					prev_pd = pd;
					++idx;
					pd = parr_get_data( desc->parr, idx );
				}

				if( pd != NULL ){
					value = (prev_pd == NULL)? 1.0 : (float64)(depth_m_5 - prev_pd->position.depth_m_5 ) / (float64)(pd->position.depth_m_5 - prev_pd->position.depth_m_5);
					g_array_append_val( fractions, value );
					g_array_append_val( indexes, idx );
					if(desc->flags & SUMMARIZE)
						g_print("\n 3--> %d %d %g %d", y, idx, value, depth_m_5);

				}

				if( indexes->len != 0 ){
				    if( desc->flags & AVERAGE ){
				        value = 0;
				        for( i = 0; i < fractions->len; ++ i )
				            value += g_array_index( fractions, float64, i );
				        for( i = 0; i < fractions->len; ++ i )
				            g_array_index( fractions, float64, i ) /= value;
				    }
					pv[param_idx + y * param_count] = g_new( ParResampl, 1 );
					pv[param_idx + y * param_count]->count = indexes->len;
					pv[param_idx + y * param_count]->indexes = g_memdup( indexes->data, sizeof(uint32) * indexes->len );
					pv[param_idx + y * param_count]->fractions = g_memdup( fractions->data, sizeof(float64) * fractions->len );
				}
				g_array_set_size( indexes, 0 );
				g_array_set_size( fractions, 0 );
				++idx;
				pd = parr_get_data( desc->parr, idx );

			}
			g_array_free( indexes, TRUE );
			g_array_free( fractions, TRUE );
		}
		else{
			idx = 0;
			pd = parr_get_data( desc->parr, idx );

			if( pd == NULL || parr_get_data( desc->parr, idx + 1 ) == NULL )
				continue;

			y = 0;
			while( (step_m_5 > 0) == (y * step_m_5 + start_m_5 - desc->mp_m_5 < pd->position.depth_m_5) )
				++y;
			prev_pd = pd;
			for( ; y < vector_count && pd != NULL; y++ ){
				depth_m_5 = y * step_m_5 + start_m_5 - desc->mp_m_5;

				while( pd != NULL && ((step_m_5 > 0) == (pd->position.depth_m_5 < depth_m_5)) ){
					prev_pd = pd;
					++idx;
					pd = parr_get_data( desc->parr, idx );
				}

				if( pd == NULL ){
					pv[param_idx + y * param_count] = g_memdup( &(ParResampl){ .index = idx - 1, .indexes = NULL, .fractions = NULL }, sizeof(ParResampl));
					break;
				}

				if( desc->flags & INTERPOLATE ){
					pv[param_idx + y * param_count] = g_new( ParResampl, 1 );
					pv[param_idx + y * param_count]->count = 2;
					pv[param_idx + y * param_count]->indexes = g_memdup( (uint32[]){ idx -1, idx }, sizeof(uint32) * 2 );
					pv[param_idx + y * param_count]->fractions = g_new( float64, 2 );
					if( prev_pd->position.depth_m_5 == pd->position.depth_m_5 ){
						pv[param_idx + y * param_count]->fractions[0] = 0.5;
						pv[param_idx + y * param_count]->fractions[1] = 0.5;
					}
					else{
						pv[param_idx + y * param_count]->fractions[0] = (pd->position.depth_m_5 - depth_m_5) / (pd->position.depth_m_5 - prev_pd->position.depth_m_5);
						pv[param_idx + y * param_count]->fractions[1] = (depth_m_5 - prev_pd->position.depth_m_5) / (pd->position.depth_m_5 - prev_pd->position.depth_m_5);
					}
				}
				else{
					if( fabs( prev_pd->position.depth_m_5 - depth_m_5 ) < fabs( pd->position.depth_m_5 - depth_m_5 ) )
						pv[param_idx + y * param_count] = g_memdup( &(ParResampl){ .index = idx - 1, .indexes = NULL, .fractions = NULL }, sizeof(ParResampl));
					else
						pv[param_idx + y * param_count] = g_memdup( &(ParResampl){ .index = idx, .indexes = NULL, .fractions = NULL }, sizeof(ParResampl));
				}
			}
		}
	}
}

/* not use now, have no specification about LIS file by time step */
static void fill_data_by_time( ParResampl **pv, size_t param_count, size_t vector_count, fixed32_3 start_sec_3, ufixed32_3 step_sec_3 )
{
	ufixed32_3		time_sec_3;
	ParamDesc		*desc;
	size_t 			param_idx;
	size_t			idx;
	float64			value, value_average;
	GArray			*indexes, *fractions;
	ParamData 		*pd;
	ParamData 		*prev_pd;
	int y, i;

	for( param_idx = 0; param_idx < params->len; ++param_idx ){
		desc = g_ptr_array_index( params, param_idx );

		if( parr_get_last_data( desc->parr ) == NULL )
			continue;

		if( desc->flags & MAGNETIC_MARK ){
			idx = 0;
			pd = parr_get_data( desc->parr, idx );
			while( pd != NULL ){
				y = (pd->position.time_sec_3 - start_sec_3) / step_sec_3;
				if( y >= 0 && y < vector_count )
					pv[param_idx + y * param_count] = g_memdup( &(ParResampl){ .index = idx, .indexes = NULL, .fractions = NULL }, sizeof(ParResampl));
				++idx;
				pd = parr_get_data( desc->parr, idx );
			}
		}
		else if( desc->flags & PEAK_VALUE ){
			/* calculate average value for pick detecting */
			idx = 0;
			pd = parr_get_data( desc->parr, idx );
			value_average = 0;
			for( idx = 0; pd != NULL; ){
				value_average += pd->value;
				++idx;
				pd = parr_get_data( desc->parr, idx );
			}
			if( idx != 0 )
				value_average /= idx;

			idx = 0;
			pd = parr_get_data( desc->parr, idx );
			time_sec_3 = start_sec_3;
			if( time_sec_3 >= step_sec_3/2 )
				time_sec_3 -= step_sec_3/2;
			while( pd != NULL && pd->position.time_sec_3 < time_sec_3 ){
				++idx;
				pd = parr_get_data( desc->parr, idx );
			}

			for( y = 0; y < vector_count && pd != NULL; y++ ){
				pv[param_idx + y * param_count] = g_memdup( &(ParResampl){ .index = idx, .indexes = NULL, .fractions = NULL }, sizeof(ParResampl));
				value = fabs( pd->value - value_average );

				time_sec_3 = y * step_sec_3 + start_sec_3 + step_sec_3/2;
				while( pd != NULL && pd->position.time_sec_3 < time_sec_3 ){
					if( value < fabs( pd->value - value_average ) ){
						value = fabs( pd->value - value_average );
						pv[param_idx + y * param_count]->index = idx;
					}
					++idx;
					pd = parr_get_data( desc->parr, idx );
				}
			}
		}
		else if( (desc->flags & AVERAGE) || (desc->flags & SUMMARIZE) ){
			idx = 0;
			pd = parr_get_data( desc->parr, idx );
			time_sec_3 = start_sec_3;
			if( time_sec_3 >= step_sec_3/2 )
				time_sec_3 -= step_sec_3/2;
			prev_pd = NULL;
			while( pd != NULL && pd->position.time_sec_3 < time_sec_3 ){
				prev_pd = pd;
				++idx;
				pd = parr_get_data( desc->parr, idx );
			}

			y = 0;
			if( idx == 0 ){
				while( y * step_sec_3 + start_sec_3 + step_sec_3/2 < pd->position.time_sec_3 )
					++y;
			}
			time_sec_3 = y * step_sec_3 + start_sec_3;
			if( time_sec_3 >= step_sec_3/2 )
				time_sec_3 -= step_sec_3/2;

			indexes = g_array_new( FALSE, FALSE, sizeof(uint32) );
			fractions = g_array_new( FALSE, FALSE, sizeof(float64) );
			for( ; y < vector_count && pd != NULL; y++ ){
				if( idx == 0 || prev_pd == NULL )
					value = 1.0;
				else
					value = (float64)(pd->position.time_sec_3 - time_sec_3) / (float64)(pd->position.time_sec_3 - prev_pd->position.time_sec_3);
				g_array_append_val( fractions, value );
				g_array_append_val( indexes, idx );

				if( pd->position.time_sec_3 < time_sec_3 ){
					prev_pd = pd;
					++idx;
					pd = parr_get_data( desc->parr, idx );
				}

				time_sec_3 = y * step_sec_3 + start_sec_3 + step_sec_3/2;
				while( pd != NULL && pd->position.time_sec_3 < time_sec_3 ){
					value = 1.0;
					g_array_append_val( fractions, value );
					g_array_append_val( indexes, idx );
					prev_pd = pd;
					++idx;
					pd = parr_get_data( desc->parr, idx );
				}

				if( pd != NULL ){
					value = (float64)(time_sec_3 - prev_pd->position.time_sec_3 ) / (float64)(pd->position.time_sec_3 - prev_pd->position.time_sec_3);
					g_array_append_val( fractions, value );
					g_array_append_val( indexes, idx );
				}

				if( indexes->len != 0 ){
				    if( desc->flags & AVERAGE ){
				        value = 0;
				        for( i = 0; i < fractions->len; ++ i )
				            value += g_array_index( fractions, float64, i );
				        for( i = 0; i < fractions->len; ++ i )
				            g_array_index( fractions, float64, i ) /= value;
				    }
					pv[param_idx + y * param_count] = g_new( ParResampl, 1 );
					pv[param_idx + y * param_count]->count = indexes->len;
					pv[param_idx + y * param_count]->indexes = g_memdup( indexes->data, sizeof(uint32) * indexes->len );
					pv[param_idx + y * param_count]->fractions = g_memdup( fractions->data, sizeof(float64) * fractions->len );
				}
				g_array_set_size( indexes, 0 );
				g_array_set_size( fractions, 0 );
			}
			g_array_free( indexes, TRUE );
			g_array_free( fractions, TRUE );
		}
		else{
			idx = 0;
			pd = parr_get_data( desc->parr, idx );

			if( pd == NULL || parr_get_data( desc->parr, idx+1 ) == NULL )
				continue;

			y = 0;
			while( y * step_sec_3 + start_sec_3 < pd->position.time_sec_3 )
				++y;
			prev_pd = pd;
			for( ; y < vector_count && pd != NULL; y++ ){
				time_sec_3 = y * step_sec_3 + start_sec_3;

				while( pd != NULL && pd->position.time_sec_3 < time_sec_3 ){
					prev_pd = pd;
					++idx;
					pd = parr_get_data( desc->parr, idx );
				}

				if( pd == NULL ){
					pv[param_idx + y * param_count] = g_memdup( &(ParResampl){ .index = idx - 1, .indexes = NULL, .fractions = NULL }, sizeof(ParResampl));
					break;
				}

				if( desc->flags & INTERPOLATE ){
					pv[param_idx + y * param_count] = g_new( ParResampl, 1 );
					pv[param_idx + y * param_count]->count = 2;
					pv[param_idx + y * param_count]->indexes = g_memdup( (uint32[]){ idx -1, idx }, sizeof(uint32) * 2 );
					pv[param_idx + y * param_count]->fractions = g_new( float64, 2 );
					if( prev_pd->position.time_sec_3 == pd->position.time_sec_3 ){
						pv[param_idx + y * param_count]->fractions[0] = 0.5;
						pv[param_idx + y * param_count]->fractions[1] = 0.5;
					}
					else{
						pv[param_idx + y * param_count]->fractions[0] = (pd->position.time_sec_3 - time_sec_3) / (pd->position.time_sec_3 - prev_pd->position.time_sec_3);
						pv[param_idx + y * param_count]->fractions[1] = (time_sec_3 - prev_pd->position.time_sec_3) / (pd->position.time_sec_3 - prev_pd->position.time_sec_3);
					}
				}
				else{
					if( fabs( prev_pd->position.time_sec_3 - time_sec_3 ) < fabs( pd->position.time_sec_3 - time_sec_3 ) )
						pv[param_idx + y * param_count] = g_memdup( &(ParResampl){ .index = idx - 1, .indexes = NULL, .fractions = NULL }, sizeof(ParResampl));
					else
						pv[param_idx + y * param_count] = g_memdup( &(ParResampl){ .index = idx, .indexes = NULL, .fractions = NULL }, sizeof(ParResampl));
				}
			}
		}
	}
}


static void read_vector_data_from_file( ParamDesc *desc, uint32 index, float64 *vals )
{
#define BUF_SIZE	65535
	static uint8	buf[65536];

	uint8	*ptr;
	int 	i;

	g_seekable_seek( G_SEEKABLE(gfm_in), parr_get_data( desc->parr, index )->offset, G_SEEK_SET, NULL, NULL );
	g_input_stream_read( gfm_in, buf, desc->count * data_types[desc->type].size, NULL, NULL );

	ptr = buf;
	for( i = 0; i < desc->count; ++i ){
		vals[i] = data_types[desc->type].conv2float64( ptr );
		ptr += data_types[desc->type].size;
	}
}

static void write_data( float64 first, float64 last, float64 step, int32 ModeTime, GOutputStream *out, TIFSave tif_save )
{
	GByteArray		*block;
	ParamDesc		*desc;
	size_t 			vector_count;
	ParResampl		**pv, *pr;
	float64			value;
	float64			*vals, *vec;
	int x, y, i, j;

	vector_count = (last - first) / step + 1;

	pv = g_new0( ParResampl*, vector_count * params->len );

	g_return_if_fail( pv != NULL);

	if( ModeTime == FALSE )
		fill_data_by_depth( pv, params->len, vector_count, first * 1e5, step * 1e5 );
	else
		fill_data_by_time( pv, params->len, vector_count, first * 1e3, step * 1e3 );

	vals = g_malloc( max_elem_count * sizeof(*vals) );
	vec = g_malloc( max_elem_count * sizeof(*vals) );

	block = g_byte_array_new();

	y = 0;
	while( y < vector_count ){
		/* Normal data Record */
		lis_block_add_data( block, &(LRecHead){ .type = 0, .reserved = 0 }, sizeof(LRecHead) );
		/* write depth */
		if( ModeTime == FALSE )
			lis_block_add_datum( block, 'I', (int32)(first * 1e2) );
		else
			lis_block_add_datum( block, 'I', (int32)(first * 1e0) );

		while( y < vector_count && block->len + frame_size <= lis_data_block_size ){
			for( x = 0; x < params->len; ++x){
				desc = g_ptr_array_index( params, x );
				pr = pv[x + y * params->len];
				if( desc->count == 1 ){
					if( desc->flags & MAGNETIC_MARK ){
						if( pr == NULL )
							value = 0;
						else
							value = parr_get_data( desc->parr, pr->index )->value;
						lis_block_add_datum( block, 'O', (int16)value );
						continue;
					}

					if( pr == NULL )
						value = invalid_value;
					else{
						if( pr->indexes == NULL )
							value = parr_get_data( desc->parr, pr->index )->value;
						else{
							value = 0;
							for( i = 0; i < pr->count; ++i )
								value += parr_get_data( desc->parr, pr->indexes[i] )->value * pr->fractions[i];
						}
					}

					if( desc->type == LOG_UINT16 || desc->type == LOG_INT16 || desc->type == LOG_UINT8 || desc->type == LOG_INT8 )
						lis_block_add_datum( block, 'O', (int16)value );
					else if( desc->type == LOG_UINT32 || desc->type == LOG_INT32 )
						lis_block_add_datum( block, 'I', (int32)value );
					else
						lis_block_add_datum( block, 'D', value );
					continue;
				}

				/* if( desc->count > 1 ) */
				if( pr == NULL ){
					if( desc->type == LOG_UINT16 || desc->type == LOG_INT16 || desc->type == LOG_UINT8 || desc->type == LOG_INT8 ){
						for( i = 0; i < desc->count; ++i )
							lis_block_add_datum( block, 'O', (int16)invalid_value );
					}
					else if( desc->type == LOG_UINT32 || desc->type == LOG_INT32 ){
						for( i = 0; i < desc->count; ++i )
							lis_block_add_datum( block, 'I', (int32)invalid_value );
					}
					else{
						for( i = 0; i < desc->count; ++i )
							lis_block_add_datum( block, 'D', invalid_value );
					}
					continue;
				}

				/* pr != NULL */
				if( pr->indexes == NULL )
					read_vector_data_from_file( desc, pr->index, vals );
				else{
					memset( vals, 0, sizeof(*vals) * desc->count );
					for( i = 0; i < pr->count; ++i ){
						read_vector_data_from_file( desc, pr->indexes[i], vec );
						for( j = 0; j < desc->count; ++j )
							vals[j] += vec[j] * pr->fractions[i];
					}
				}

				if( desc->type == LOG_UINT16 || desc->type == LOG_INT16 || desc->type == LOG_UINT8 || desc->type == LOG_INT8 ){
					for( i = 0; i < desc->count; ++i )
						lis_block_add_datum( block, 'O', (int16)vals[i] );
				}
				else if( desc->type == LOG_UINT32 || desc->type == LOG_INT32 ){
					for( i = 0; i < desc->count; ++i )
						lis_block_add_datum( block, 'I', (int32)vals[i] );
				}
				else{
					for( i = 0; i < desc->count; ++i )
						lis_block_add_datum( block, 'D', vals[i] );
				}

			}
			first += step;
			++y;
		}

		lis_block_write( block, lis_out, tif_save );

	}

	g_free( vals );
	g_free( vec );

	for( x = params->len * vector_count - 1; x >= 0; --x ){
		if( pv[x] == NULL )
			continue;
		g_free( pv[x]->indexes );
		g_free( pv[x]->fractions );
		g_free( pv[x] );
	}

	g_free( pv );
	g_byte_array_free( block, TRUE );

	g_print( "\n frame size '%d'   vector count '%d'", frame_size, vector_count );
}

/* Date of generation for the software: Year[2] + '/' + Month[2] + '/' + Day[2] */
static const char8* lis_library_creation_date()
{
	static char8	buf[100];

	GFile		*lib_file;
	GFileInfo	*info;
	uint64		cr_time;
	GDateTime	*dt;
	char8		*str;

	lib_file = g_file_new_for_path( EXPORTDIR(PACKAGE LIB_SUFFIX, UTF8) );
	info = g_file_query_info( lib_file, G_FILE_ATTRIBUTE_TIME_MODIFIED, G_FILE_QUERY_INFO_NONE, NULL, NULL );
	cr_time = g_file_info_get_attribute_uint64( info, G_FILE_ATTRIBUTE_TIME_MODIFIED );
	g_object_unref( lib_file );
	g_object_unref( info );

	dt = g_date_time_new_from_unix_local( cr_time );
	str = g_date_time_format( dt, "%y/%m/%d" );
	memcpy( buf, str, strlen(str) + 1 );
	g_free( str);
	g_date_time_unref( dt );

	return buf;
}


#include <libxml/tree.h>

/* make export */
EXPORT_API void export_xml_description( char8 *xml_description )
{
	char8		*lis_filename;
	GFile		*lis_file;
	char		*old_locale;
	GByteArray	*block;
	FileRecord	file_rec;
	char8		**mnemonics;
	ParamDesc	*desc;
	char8		*str;
	char8		*pos;
	float32		value;
	uint32		i;
	char8 		*gfm_filename;

	ExportMode	mode;
	xmlDocPtr		doc = NULL;
	xmlNodePtr		node = NULL;
	xmlChar			*xml_data;

	lis_out = NULL;
	gfm_in = NULL;
	tif_save = TIF_SAVE;
	well_data = NULL;
	well_data_desc = NULL;
	strt_record = NULL;
	numb_mnem = NULL;
	numb_num = NULL;

	lis_data_block_size = 16000;
	frame_size = 16000;
	max_elem_count = 0;

	if(xml_description == NULL)
		return;

	doc = xmlParseMemory(xml_description, strlen(xml_description));
	if(doc == NULL){
		g_printerr("\n !!! Error parse xml memory !!!");
		return;
	}

	node = xmlDocGetRootElement( doc );
	if(xmlStrcmp( node->name, (const xmlChar*)"GFM" ) != 0){
		g_printerr("\n !!! Error! Not found GFM root element !!!");
		xmlFreeDoc(doc);
		xmlCleanupParser();
		return;
	}

	xml_data = xmlGetProp( node, (const xmlChar*)"START_M" );
	if(xml_data){
		mode.start_m_5 = prog_strtod((const char8 *)xml_data, NULL) * 1e5;
		xmlFree( xml_data );
	}
	else{
		g_printerr("\n !!! Error! Not found START_M !!!");
		xmlFreeDoc(doc);
		xmlCleanupParser();
		return;
	}

	xml_data = xmlGetProp( node, (const xmlChar*)"STOP_M" );
	if(xml_data){
		mode.stop_m_5 = prog_strtod((const char8 *)xml_data, NULL) * 1e5;
		xmlFree( xml_data );
	}
	else{
		g_printerr("\n !!! Error! Not found STOP_M !!!");
		xmlFreeDoc(doc);
		xmlCleanupParser();
		return;
	}

	xml_data = xmlGetProp( node, (const xmlChar*)"STEP_M" );
	if(xml_data){
		mode.step_m_5 = prog_strtod((const char8 *)xml_data, NULL) * 1e5;
		xmlFree( xml_data );
	}
	else{
		mode.step_m_5 = 0.1 * 1e5;
	}

	xml_data = xmlGetProp( node, (const xmlChar*)"BEGIN_SEC" );
	if(xml_data){
		mode.begin_sec_3 = prog_strtod((const char8 *)xml_data, NULL) * 1e3;
		xmlFree( xml_data );
	}
	else{
		mode.begin_sec_3 = 0;
	}

	xml_data = xmlGetProp( node, (const xmlChar*)"END_SEC" );
	if(xml_data){
		mode.end_sec_3 = prog_strtod((const char8 *)xml_data, NULL) * 1e3;
		xmlFree( xml_data );
	}
	else{
		g_printerr("\n !!! Error! Not found END_SEC !!!");
		xmlFreeDoc(doc);
		xmlCleanupParser();
		return;
	}

	xml_data = xmlGetProp( node, (const xmlChar*)"STEP_SEC" );
	if(xml_data){
		mode.step_sec_3 = prog_strtod((const char8 *)xml_data, NULL) * 1e3;
		xmlFree( xml_data );
	}
	else{
		mode.step_sec_3 = 1 * 1e3;
	}

	xml_data = xmlGetProp( node, (const xmlChar*)"INVALID_VALUE" );
	if(xml_data){
		invalid_value = prog_strtod((const char8 *)xml_data, NULL);
		xmlFree( xml_data );
	}
	else{
		invalid_value = -999.5;
	}

	xml_data = xmlGetProp( node, (const xmlChar*)"FILE" );
	if(xml_data){
		gfm_filename = g_strdup((char*)xml_data);
		xmlFree( xml_data );
	}
	else{
		g_printerr("\n !!! Error! Not found gfm filename !!!");
		xmlFreeDoc(doc);
		xmlCleanupParser();
		return;
	}

//	xml_data = xmlGetProp( node, (const xmlChar*)"TIME_MODE" );
//	if(xml_data){
//		mode.is_time_mode = prog_strtod(xml_data, NULL);
//		xmlFree( xml_data );
//	}
//	else{
//		mode.is_time_mode = FALSE;
//	}
	mode.is_time_mode = FALSE;
	if( mode.start_m_5 > mode.stop_m_5  && mode.step_m_5 > 0)
		mode.step_m_5 = -mode.step_m_5;
	else if(mode.start_m_5 < mode.stop_m_5  && mode.step_m_5 < 0)
		mode.step_m_5 = -mode.step_m_5;

	tif_save = TIF_SAVE;

	node = node->children;
	for( ; node != NULL; node = node->next ){
		if( xmlStrcmp( node->name, (const xmlChar*)"MNEMS" ) != 0 )
			continue;
		else
			break;
	}

	if( node == NULL ){
		g_printerr("\n !!! Error! Not found MNEMS data block !!!");
		g_free(gfm_filename);
		xmlFreeDoc(doc);
		xmlCleanupParser();
		return;
	}

	params_xml_hash_table_new();
	node = node->children;
	for( ; node != NULL; node = node->next ){
		if( xmlStrcmp( node->name, (const xmlChar*)"MNEM" ) != 0 )
			continue;

		xmlChar *gfm_mnem;
		xmlChar *lis_mnem;
		uint8	is_selected;

		is_selected = TRUE;
		xml_data = xmlGetProp( node, (const xmlChar*)"LIS_CHECKED" );
		if(xml_data){
			is_selected = prog_strtod((const char8 *)xml_data, NULL);
			g_free(xml_data);
		}

		if(!is_selected)
			continue;

		gfm_mnem = xmlGetProp( node, (const xmlChar*)"GFM_MNEM" );
		if(gfm_mnem == NULL)
			continue;

		lis_mnem = xmlGetProp( node, (const xmlChar*)"LIS_MNEM" );
		if(lis_mnem == NULL){
			params_xml_table_set_new_element((const char8 *)gfm_mnem, (const char8 *)gfm_mnem);
		}
		else{
			params_xml_table_set_new_element((const char8 *)gfm_mnem, (const char8 *)lis_mnem);
			g_free(lis_mnem);
		}
		g_free(gfm_mnem);
	}

	xmlFreeDoc( doc );
	xmlCleanupParser();

	read_gfmfile( gfm_filename );

	g_print("\n LIS read gfm file");

	/* calculate frame size */
	frame_size = 0;
	max_elem_count = 0;
	for( i = 0; i < params->len; ){
		desc = g_ptr_array_index( params, i );
		if(desc == NULL){
			g_ptr_array_remove_index( params, i );
			continue;
		}
		if(params_xml_table_get_lis_mnem(cut_log(desc->entmnem)) == NULL){
			g_ptr_array_remove_index( params, i );
			continue;
		}

        if( (desc->flags & MAGNETIC_MARK) == 0 && parr_get_last_data( desc->parr ) == NULL ){
            g_printerr( "\n** Array of parameter '%s' is empty", desc->entmnem );
            g_ptr_array_remove_index( params, i );
            g_warn_if_reached();
            continue;
        }
		frame_size += desc->count * MAX( data_types[desc->type].size, 2 );
		max_elem_count = MAX( desc->count, max_elem_count );
		++i;
	}

	if(params->len == 0){
		g_print("\n lis params->len = 0");

		g_free(gfm_filename);
		data_blocks_free();
		g_datalist_clear( &well_data );
		g_datalist_clear( &well_data_desc );
		if( numb_mnem != NULL ){
			g_ptr_array_free( numb_mnem, TRUE );
			numb_mnem = NULL;
			g_ptr_array_unref( numb_num );
		}

		if( strt_record != NULL ){
			g_date_time_unref( strt_record );
			strt_record = NULL;
		}

	    destroy_arr_mnemonics();
	    params_xml_table_free_data();

		return;
	}

	lis_filename = NULL;


	lis_filename = g_strdup( gfm_filename );
	g_free(gfm_filename);

	lis_filename[ strlen(lis_filename) - 3 ] = 0;
	strcat( lis_filename, "lis" );
	g_print( "\n%s\n", lis_filename );

	lis_file = g_file_new_for_path( lis_filename );
	lis_out = G_OUTPUT_STREAM(g_file_replace( lis_file, NULL, FALSE, G_FILE_CREATE_REPLACE_DESTINATION, NULL, NULL ));

	old_locale = setlocale( LC_ALL, "C" );

	bind_textdomain_codeset( PACKAGE, OUT_CODESET );

	lis_block_write_init();

	block = g_byte_array_new();

	/* file header record */
	memset( &file_rec, ' ', sizeof(file_rec) );
	file_rec.logic_rec_head = (LRecHead){ .type = 128, .reserved = 0 };
	file_rec.file_type = LO;
	strncpy( file_rec.file_name, "KEDR-05", 7 );
	strncpy( file_rec.vers_soft, version(), MIN( strlen(version()), sizeof(file_rec.vers_soft) ) );
	strncpy( file_rec.date_soft, lis_library_creation_date(), sizeof(file_rec.date_soft) );

	lis_data_block_size = MAX( frame_size + 100, DEFAULT_FRAME_SIZE );
	str = g_strdup_printf( "%d", lis_data_block_size );
	strncpy( file_rec.max_rec_length, str, strlen( str ) );
	g_free( str );

	lis_block_add_data( block, &file_rec, sizeof(file_rec) );
	lis_block_write( block, lis_out, tif_save );

	/* well information table */
	lis_block_add_data( block, &(LRecHead){ .type = 34, .reserved = 0 }, sizeof(LRecHead) );
	/* fill well info gfm_in table CONS */
	lis_block_add_compon_block( block, 73, 'A', "TYPE", "", "CONS" );
	mnemonics = (char8*[]){                                     "MNEM", "STAT", "PUNI", "TUNI", "VALU", NULL };
	lis_block_add_compon_block_list( block, "AAAAA", mnemonics, "EQUI", "ALLO",     "",     "",  "dev" );
	lis_block_add_compon_block_list( block, "AAAAA", mnemonics, "CNCU", "ALLO",     "",     "",	  g_datalist_get_data( &well_data, "[ORDER]" ) );
	lis_block_add_compon_block_list( block, "AAAAA", mnemonics,   "CN", "ALLO",     "",     "",	  g_datalist_get_data( &well_data, "[COMP]" ) );
	lis_block_add_compon_block_list( block, "AAAAA", mnemonics,   "WN", "ALLO",     "",     "",	  g_datalist_get_data( &well_data, "[WELL]" ) );
	lis_block_add_compon_block_list( block, "AAAAA", mnemonics,   "FN", "ALLO",     "",     "",	  g_datalist_get_data( &well_data, "[FIELD]" ) );
	lis_block_add_compon_block_list( block, "AAAAA", mnemonics, "DATE", "ALLO",     "",     "",	  g_datalist_get_data( &well_data, "[DATE]" ) );
	lis_block_add_compon_block_list( block, "AAAAD", mnemonics,  "TLI", "ALLO",    "M",    "M",	  MAX( mode.start_m_5, mode.stop_m_5 ) / 1e+5f );
	lis_block_add_compon_block_list( block, "AAAAD", mnemonics,  "BLI", "ALLO",    "M",    "M",	  MIN( mode.start_m_5, mode.stop_m_5 ) / 1e+5f );

	/// TODO read real acoustic parameters descriptions
	/* save acoustic description */
	for( i = 0; i < params->len; ++i ){
		desc = g_ptr_array_index( params, i );
		if( desc->desc == NULL || strstr( desc->desc, "draw_type=\"ACOUSTIC\"" ) == NULL )
			continue;
		str = g_strdup_printf( "WFZ%c", cut_shortcut( desc->entmnem )[2] );
		pos = strstr( desc->desc, "data_begin=\"" );
		if( pos == NULL )
			value = 0.0;
		else
			value = prog_strtod( pos + strlen( "data_begin=\"" ), NULL );
		lis_block_add_compon_block_list( block, "AAAAD", mnemonics,  str, "ALLO",   "US",   "US",	  value );
		g_free( str );

		str = g_strdup_printf( "WFS%c", cut_shortcut( desc->entmnem )[2] );
		pos = strstr( desc->desc, "data_step=\"" );
		if( pos == NULL )
			value = 2.0;
		else
			value = prog_strtod( pos + strlen( "data_step=\"" ), NULL );
		lis_block_add_compon_block_list( block, "AAAAD", mnemonics,  str, "ALLO",   "US",   "US",	  value );
		g_free( str );
	}
	lis_block_write( block, lis_out, tif_save );

	/* tools information table */
	if( numb_mnem != NULL ){
		lis_block_add_data( block, &(LRecHead){ .type = 34, .reserved = 0 }, sizeof(LRecHead) );
		/* fill well info gfm_in table NUMB */
		lis_block_add_compon_block( block, 73, 'A', "TYPE", "", "NUMB" );
		mnemonics = (char8*[]){                                      "MNEM", "TYPS", "TYPC", "NUM", NULL };
		for( i = 0; i < numb_mnem->len; ++i ){
			str = g_ptr_array_index( numb_mnem, i );
			lis_block_add_compon_block_list( block, "AAAA", mnemonics,  str, "NSTR"/*"NSTL"*/,   "",    g_ptr_array_index( numb_num, i ) );
		}
		lis_block_write( block, lis_out, tif_save );
	}

	/* Data Format Specification Record */
	lis_block_add_data( block, &(LRecHead){ .type = 64, .reserved = 0 }, sizeof(LRecHead) );
	/* entry type - 4, direction up/down (1/255) */
	lis_block_add_entry_block( block, 4, 'B', (mode.step_m_5 > 0)? 255 : 1 );
	/* entry type - 5, depth units (255 - meters) */
	lis_block_add_entry_block( block, 5, 'B', 255 );
	/* entry type - 8, depth step value */
	lis_block_add_entry_block( block, 8, 'D', fabs( mode.step_m_5 ) / 1e+3 );
	/* entry type - 9, depth step units */
	lis_block_add_entry_block( block, 9, 'A', "CM  " );
	/* entry type - 12, invalid value */
	lis_block_add_entry_block( block, 12, 'D', invalid_value );
	/* entry type - 13, depth record mode (1 - depth occurs only once per data record preceding first frame) */
	lis_block_add_entry_block( block, 13, 'B', 1 );
	/* entry type - 14, depth units */
	lis_block_add_entry_block( block, 14, 'A', "CM  " );
	/* entry type - 15, depth representation code */
	lis_block_add_entry_block( block, 15, 'B', 'I' );
	/* entry type - 16, sub-type number of datum specification block */
	lis_block_add_entry_block( block, 16, 'B', 0 );
	/* entry type - 0, last entry block gfm_in list */
	lis_block_add_entry_block( block, 0, 'B', 0 );
	/* Datum Specification Block */
	curve_info( block );
	lis_block_write( block, lis_out, tif_save );

	g_print("\n start %d  stop %d step %d", mode.start_m_5, mode.stop_m_5, mode.step_m_5);
		/* Normal Data Record */
	if( mode.is_time_mode == FALSE )
		write_data( mode.start_m_5 * 1e-5, mode.stop_m_5 * 1e-5, mode.step_m_5 * 1e-5, mode.is_time_mode, lis_out, TIF_SAVE );
	else
		write_data( mode.begin_sec_3 * 1e-3, mode.end_sec_3 * 1e-3, mode.step_sec_3 * 1e-3, mode.is_time_mode, lis_out, TIF_SAVE );

		/* file trailer record */
	file_rec.logic_rec_head.type = 129;
	lis_block_add_data( block, &file_rec, sizeof(file_rec) );
	lis_block_write( block, lis_out, tif_save );

		/* last block */
	if( tif_save == TIF_SAVE )
		tif_save = TIF_FINISH;
	lis_block_write( block, lis_out, tif_save );

	g_byte_array_free( block, TRUE );

	g_output_stream_close( lis_out, NULL, NULL );
	g_object_unref( lis_out );
	g_object_unref( lis_file );

	bind_textdomain_codeset( PACKAGE, "UTF-8" );
	setlocale( LC_ALL, old_locale );

	data_blocks_free();
	g_datalist_clear( &well_data );
	g_datalist_clear( &well_data_desc );
	if( numb_mnem != NULL ){
		g_ptr_array_free( numb_mnem, TRUE );
		numb_mnem = NULL;
		g_ptr_array_unref( numb_num );
	}

	if( strt_record != NULL ){
		g_date_time_unref( strt_record );
		strt_record = NULL;
	}

	g_free( lis_filename );

	g_input_stream_close( G_INPUT_STREAM(gfm_in), NULL, NULL );

    destroy_arr_mnemonics();
    params_xml_table_free_data();

}
