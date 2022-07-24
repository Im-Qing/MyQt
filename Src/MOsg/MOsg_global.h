#ifndef MOSG_GLOBAL_H
#define MOSG_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(MOSG_LIBRARY)
#  define MOSG_EXPORT Q_DECL_EXPORT
#else
#  define MOSG_EXPORT Q_DECL_IMPORT
#endif

#endif // MOSG_GLOBAL_H
