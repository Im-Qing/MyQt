#ifndef MOPENGL_GLOBAL_H
#define MOPENGL_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(MOPENGL_LIBRARY)
#  define MOPENGL_EXPORT Q_DECL_EXPORT
#else
#  define MOPENGL_EXPORT Q_DECL_IMPORT
#endif

#endif // MOPENGL_GLOBAL_H
