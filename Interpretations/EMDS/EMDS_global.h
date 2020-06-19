#ifndef EMDS_GLOBAL_H
#define EMDS_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(EMDS_LIBRARY)
#  define EMDS_EXPORT Q_DECL_EXPORT
#else
#  define EMDS_EXPORT Q_DECL_IMPORT
#endif

#endif // EMDS_GLOBAL_H
