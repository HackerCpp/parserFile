#include <program_h>

/* Localized tool's name for "Select tool's driver" dialog */
#define EXPORT_NAME_LOCALIZED dpgettext( PACKAGE, "Export name", "file LIS" )

#define IMPORT_FILE_EXT	"*.lis"

/* initialization of library, return NULL on success, else error string */
EXPORT_API const char8* init( GetFunction func )
{
	init_prog_dir_func( func );

	bindtextdomain( PACKAGE, LOCALEDIR("", LOCAL) );
	bind_textdomain_codeset( PACKAGE, "UTF-8" );

	init_prog_func( func );

	return NULL;
}

/* destroy library - free static data */
EXPORT_API void destroy()
{
}

#define ONLY_HEADER
#include "version.rc"

/* library version */
EXPORT_API const char8* version()
{
	return LIBRARY_FILEVER;
}

/* LIS-file exporter name */
EXPORT_API const char8* exporter_name()
{
	return EXPORT_NAME_LOCALIZED;
}

/* extension of file can be imported */
EXPORT_API const char8* import_extension()
{
	return IMPORT_FILE_EXT;
}
