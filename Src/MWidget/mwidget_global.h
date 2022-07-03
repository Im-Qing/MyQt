#ifndef MWIDGET_GLOBAL_H
#define MWIDGET_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(MWIDGET_LIBRARY)
#  define MWIDGETSHARED_EXPORT Q_DECL_EXPORT
#else
#  define MWIDGETSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // MWIDGET_GLOBAL_H
