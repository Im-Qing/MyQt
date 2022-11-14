#-------------------------------------------------
#
# Project created by QtCreator 2022-06-13T16:48:44
#
#-------------------------------------------------

QT       += widgets

TARGET = MCore
TEMPLATE = lib

DEFINES += MCORE_LIBRARY

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    MString.cpp

HEADERS += \
    mcore_global.h \
    MString.h

win32{
    TargetDir = /
    CONFIG(debug,debug|release){
        TargetDir = $$PWD/debug
    }
    CONFIG(release,debug|release){
        TargetDir = $$PWD/release
    }

    TargetDll = $$TargetDir/*.dll
    TargetLib = $$TargetDir/*.lib
    #将输入目录中的"/"替换为"\"
    TargetDll = $$replace(TargetDll, /, \\)
    TargetLib = $$replace(TargetLib, /, \\)
    #将输出目录中的"/"替换为"\"
    OutputBinDir = $$PWD/../../Bin/Win/
    OutputBinDir = $$replace(OutputBinDir, /, \\)
    OutputLibDir = $$PWD/../../Lib/Win/
    OutputLibDir = $$replace(OutputLibDir, /, \\)
    //执行copy命令
    QMAKE_POST_LINK += copy /Y $$TargetDll $$OutputBinDir && copy /Y $$TargetLib $$OutputLibDir
}

unix {
    target.path = /usr/lib
    INSTALLS += target
}

include($$PWD/../Common.pri)
