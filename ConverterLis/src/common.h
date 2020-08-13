#ifndef COMMON_H_
#define COMMON_H_

#include <glib.h>

#include "basic_types.h"

#ifdef G_OS_WIN32

#define EXPORT_API		__declspec(dllexport)
#define EXTERN			extern
#define LIB_SUFFIX		".dll"

#else

#define EXPORT_API
#define EXTERN			extern
#define LIB_SUFFIX		".so"

#endif

#define DIR_SUFFIX					"_exports"
#define OUT_CODESET					"866"

/* package name for localization */
#define PACKAGE 					"lis"

typedef enum _ProgDirLocale{ LOCAL, UTF8 } ProgDirLocale;
EXTERN char* prog_dir( const char8 *path, const char8 *file, ProgDirLocale locale );

#define	MAINDIR( PATH, LOC )		prog_dir( "main"DIR_SUFFIX, PATH, LOC )

#define BINDIR( PATH, LOC )			prog_dir( "bin"DIR_SUFFIX, PATH, LOC )
#define DRIVERSDIR( PATH, LOC )		prog_dir( "drivers"DIR_SUFFIX, PATH, LOC )
#define EXPORTDIR( PATH, LOC )		prog_dir( "export"DIR_SUFFIX, PATH, LOC )
#define TMPDIR( PATH, LOC )			prog_dir( "tmp"DIR_SUFFIX, PATH, LOC )

#define SHAREDIR( PATH, LOC ) 		prog_dir( "share"DIR_SUFFIX, PATH, LOC )
#define IMAGESDIR( PATH, LOC ) 		prog_dir( "images"DIR_SUFFIX, PATH, LOC )
#define LOCALEDIR( PATH, LOC ) 		prog_dir( "locale"DIR_SUFFIX, PATH, LOC )
#define	WORKDIR( PATH, LOC )		prog_dir( "work"DIR_SUFFIX, PATH, LOC )
#define	SETTINGSDIR( PATH, LOC )	prog_dir( "settings"DIR_SUFFIX, PATH, LOC )
#define	SETTINGSLOCDIR( PATH, LOC )	prog_dir( "settings_locale"DIR_SUFFIX, PATH, LOC )

#include <locale.h>

#define ENABLE_NLS						1
#include <gettext.h>

#define _(String)					dgettext( PACKAGE, String )
#define gettext_noop(String)		String
#define N_(String) gettext_noop		(String)

#ifdef __GNUC__
#define COMMON_INLINE __inline
#else
#ifdef __cplusplus
#define COMMON_INLINE inline
#else
#undef COMMON_INLINE
#endif
#endif

#endif /* COMMON_H_ */
