#ifndef LOGDATASAVER_GLOBAL_H
#define LOGDATASAVER_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(SAVER_LIBRARY)
#  define SAVER_EXPORT Q_DECL_EXPORT
#else
#  define SAVER_EXPORT Q_DECL_IMPORT
#endif

#endif // LOGDATASAVER_GLOBAL_H
