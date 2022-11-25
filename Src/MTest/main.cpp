#include "MMainWindow.h"

#include <QApplication>
#include <QTextCodec>
#include <QOpenGLContext>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //opengl版本
    QOpenGLContext ctx;
    ctx.create();
    QSurfaceFormat format = ctx.format();
    auto major = format.majorVersion();
    auto minor = format.minorVersion();
    qDebug() << "OpenGL Version Major:" << major << "OpenGL Version Minor:" << minor;

//    QTextCodec *codec = QTextCodec::codecForName("UTF-8");
//    QTextCodec::setCodecForLocale(codec);

    MMainWindow w;
    w.show();
    return a.exec();
}
