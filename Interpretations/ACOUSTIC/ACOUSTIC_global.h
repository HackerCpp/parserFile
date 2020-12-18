#ifndef ACOUSTIC_GLOBAL_H
#define ACOUSTIC_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(ACOUSTIC_LIBRARY)
#  define ACOUSTIC_EXPORT Q_DECL_EXPORT
#else
#  define ACOUSTIC_EXPORT Q_DECL_IMPORT
#endif

#endif // ACOUSTIC_GLOBAL_H
