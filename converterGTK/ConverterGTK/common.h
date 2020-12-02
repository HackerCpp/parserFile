#ifndef COMMON_H_
#define COMMON_H_

#include "basic_types.h"

#define PACKAGE         "kedr-bin"

#define CURLOG_MNEM     "{{CurrentLog}}"


typedef enum _MainState{
    ST_DISCONNECT   = 0,        /* disconnect mode, logging file view only */
    ST_KEDR         = 1 << 0,   /* use KEDR DLL mode */
    ST_REMOTE       = 1 << 1,   /* use KEDR-REMOTE DLL mode */
    ST_LOGGING      = 1 << 2,   /* logging mode for KEDR and KEDR-REMOTE */
    ST_SIMULATOR    = 1 << 3,   /* simulator mode for KEDR */
} MainState;

const uint32 g_main_state;
void g_main_state_set( MainState flags );


typedef enum _ProgDirLocale{ LOCAL, UTF8 } ProgDirLocale;
const char* prog_dir( const char8 *path, const char8 *file, ProgDirLocale locale );

#define DIR_SUFFIX                  "_bin"

#define MAINDIR( PATH, LOC )        prog_dir( "main"DIR_SUFFIX, PATH, LOC )

#define BINDIR( PATH, LOC )         prog_dir( "bin"DIR_SUFFIX, PATH, LOC )
#define DRIVERSDIR( PATH, LOC )     prog_dir( "drivers"DIR_SUFFIX, PATH, LOC )
#define EXPORTDIR( PATH, LOC )      prog_dir( "export"DIR_SUFFIX, PATH, LOC )

#define SHAREDIR( PATH, LOC )       prog_dir( "share"DIR_SUFFIX, PATH, LOC )
#define LOCALEDIR( PATH, LOC )      prog_dir( "locale"DIR_SUFFIX, PATH, LOC )
#define WORKDIR( PATH, LOC )        prog_dir( "work"DIR_SUFFIX, PATH, LOC )
#define DATADIR( PATH, LOC )        prog_dir( "data"DIR_SUFFIX, PATH, LOC )
#define CALIBRDIR( PATH, LOC )      prog_dir( "calibr"DIR_SUFFIX, PATH, LOC )
#define FORMSDIR( PATH, LOC )       prog_dir( "forms"DIR_SUFFIX, PATH, LOC )
#define SETTINGSDIR( PATH, LOC )    prog_dir( "settings"DIR_SUFFIX, PATH, LOC )
#define SETTINGSLOCDIR( PATH, LOC ) prog_dir( "settings_locale"DIR_SUFFIX, PATH, LOC )

#define IMAGESDIR_DEPRECATED_( PATH, LOC )      prog_dir( "images"DIR_SUFFIX, PATH, LOC )

#define RESOURCE_UI                 "/resource/"PACKAGE"/ui/"
#define RESOURCE_PNG                "/resource/"PACKAGE"/png/"

#include <locale.h>
#include <libintl.h>
#define _(String) gettext (String)
#define gettext_noop(String) String
#define N_(String) gettext_noop(String)

#define ENABLE_NLS 1
#include <gettext.h>

#include <glib.h>

#define STATIC_ASSERT_EXPR(expr) (sizeof (char[(expr) ? 1 : -1]))
#define CHECK_COUNT( COUNT, TYPE, ... ) COUNT, __VA_ARGS__, STATIC_ASSERT_EXPR( (COUNT) == sizeof((TYPE[]){__VA_ARGS__}) / sizeof(TYPE) )

#define gtk_list_store_new_check_count( COUNT, ... )        gtk_list_store_new( CHECK_COUNT( COUNT, GType, __VA_ARGS__ ) )

/* FIX g_strtod() problem with "0,001" and decimal '.' */
//double prog_strtod( const char *nptr, char **endptr );//Закомментировал нет .c
//#define g_strtod( STR, END )    prog_strtod( STR, END )

#define builder_get_widget( BUILDER, NAME )     GTK_WIDGET(gtk_builder_get_object( (BUILDER), (NAME) ))

#ifdef G_OS_WIN32
#define LIB_SUFFIX          ".dll"
#else
#define LIB_SUFFIX          ".so"
#endif

#ifndef G_OS_WIN32
#define gtk_widget_get_window( W )          (W)->window
#define gtk_dialog_get_content_area( D )    (D)->vbox
#define gtk_adjustment_get_upper( A )       (A)->upper
#define gtk_adjustment_set_upper( A, V )    (A)->upper = (V)
#define gtk_adjustment_get_lower( A )       (A)->lower
#define gtk_adjustment_set_lower( A, V )    (A)->lower = (V)
#define gtk_widget_get_allocation( W, AL )  *(AL) = (W)->allocation
#endif

#endif /* COMMON_H_ */
