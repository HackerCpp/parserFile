#include <string.h>
#include <gio/gio.h>

#include "common.h"
#include "utils.h"

static struct _ProgDirDescription{
	char	*prefix;
	int		prefix_len;
	char	*path;
	int		is_exist;
} prog_dirs[] = {
		{"main",			4,	"",				FALSE},
#ifdef KEDR_DEBUG
		{"bin",				3,	"bin_d/",		FALSE},
		{"drivers",			7,	"drivers_d/",	FALSE},
		{"export",			6,	"export_d/",	FALSE},
#else
		{"bin",				3,	"bin/",			FALSE},
		{"drivers",			7,	"drivers/",		FALSE},
		{"export",			6,	"export/",		FALSE},
#endif
		{"share",			5,	"share/",		FALSE},
		{"images",			6,	"share/images/",FALSE},
		{"locale",			6,	"share/locale/",FALSE},
		{"work",			4,	"work/",		FALSE},
		{"data",			4,	"data/",		FALSE},
		{"calibr",			6,	"calibr/",		FALSE},
		{"forms",			5,	"forms/",		FALSE},
		{"settings_locale",	15,	"settings/LC/",	FALSE},
		{"settings",		8,	"settings/",	FALSE},
		{"tmp",				3,	"work/tmp/",	FALSE},
};

static char* curdir_utf8 = NULL;

void prog_dir_init( const char *main_path_local )
{
	GFile	*file;
	char8	*pos;
	char	*locale;
	int 	i;

	g_free( curdir_utf8 );

	g_type_init();
	pos = g_locale_to_utf8( main_path_local, -1, NULL, NULL, NULL );
	if( pos == NULL ){
		g_printerr( "\n ERROR converting main path to UTF-8 '%s'", main_path_local );
		g_warn_if_reached();
		file = g_file_new_for_commandline_arg( main_path_local );
	}
	else{
		file = g_file_new_for_commandline_arg( pos );
		g_free( pos );
	}
	curdir_utf8 = g_file_get_path( file );
	g_object_unref( file );

	if( curdir_utf8 == NULL ){
		g_warn_if_fail( curdir_utf8 != NULL );
		curdir_utf8 = g_strdup( "/" );
	}

	pos = g_strrstr( curdir_utf8, "\\" );
	if( pos == NULL )
		pos = g_strrstr( curdir_utf8, "/" );

	g_assert( pos != NULL );

	pos[1] = '\0';

	g_print( "\nCurrent '%s'\n", curdir_utf8 );

	kedrrc_open();

	locale = g_strdup( kedrrc_get_pref6s( "kedr-bin:lang" ) );
	if( locale == NULL ){
		locale = setlocale( LC_ALL, "" );
#ifdef G_OS_WIN32
		locale = g_win32_getlocale();
#else
		locale = g_strdup( locale );
#endif
	}
	else{
		/* set locale for translation */
		g_setenv( "LANG", locale, TRUE );
		/* set language priority */
//		g_setenv( "LANGUAGE", "ru:ar", TRUE );
	}

	if( locale == NULL || locale[0] == 0 || locale[1] == 0 )
		return;

	/* change 'LC' string of path in prog_dirs to current locale */
	for( i = 0; i < G_N_ELEMENTS(prog_dirs); ++i ){
		if( g_str_has_suffix( prog_dirs[i].path, "LC/" ) != FALSE ){
			prog_dirs[i].path = g_strdup( prog_dirs[i].path );
			memcpy( prog_dirs[i].path + strlen(prog_dirs[i].path) - 3, locale, 2 );
		}
	}

	g_free( locale );
}
const char* prog_dir( const char8 *path, const char8 *file, ProgDirLocale locale )
{
	static char* dir = NULL;

	const char	*prog_path;
	char		*dir_utf8;
	int i;

	g_free( dir );

	prog_path = NULL;
	for( i = 0; i < G_N_ELEMENTS(prog_dirs); ++i ){
		if( strncmp( prog_dirs[i].prefix, path, prog_dirs[i].prefix_len ) == 0 ){
			prog_path = prog_dirs[i].path;
			if( prog_dirs[i].is_exist == FALSE ){
				dir = g_strdup_printf( "%s%s", curdir_utf8, prog_path );
				if( g_file_test( dir, G_FILE_TEST_EXISTS ) != FALSE )
					prog_dirs[i].is_exist = TRUE;
				else{
					if( g_mkdir_with_parents( dir, 0 ) == -1 ){
						g_printerr( "\n** CRITICAL ERROR Cann't create directory '%s'", dir );
						g_return_val_if_reached( NULL );
					}
					else
						prog_dirs[i].is_exist = TRUE;
				}
				g_free( dir );
			}
			break;
		}
	}

	if( prog_path == NULL ){
		prog_path = path;
		dir = g_strdup_printf( "%s%s", curdir_utf8, prog_path );
		if( g_file_test( dir, G_FILE_TEST_EXISTS ) == FALSE ){
			if( g_mkdir_with_parents( dir, 0 ) == -1 ){
				g_printerr( "\n** CRITICAL ERROR Cann't create directory '%s'", dir );
				g_return_val_if_reached( NULL );
			}
		}
		g_free( dir );
	}

	dir_utf8 = g_strdup_printf( "%s%s%s", curdir_utf8, prog_path, file );

	if( locale == LOCAL ){
		dir = g_locale_from_utf8( dir_utf8, -1, NULL, NULL, NULL );
		g_free( dir_utf8 );
	}
	else{
		dir = dir_utf8;
		g_warn_if_fail( locale == UTF8 );
	}
	return dir;
}
