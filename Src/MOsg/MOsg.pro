QT += widgets core gui opengl

TEMPLATE = lib
DEFINES += MOSG_LIBRARY

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    MOsg.cpp \
    MOsgEventHandler.cpp \
    MOsgImage.cpp \
    MOsgLine.cpp \
    MOsgNode.cpp \
    MOsgScene.cpp \
    MOsgModel.cpp \
    MOsgText.cpp \
    MOsgWidget.cpp

HEADERS += \
    MOsgEventHandler.h \
    MOsgImage.h \
    MOsgLine.h \
    MOsgNode.h \
    MOsgScene.h \
    MOsgText.h \
    MOsgWidget.h \
    MOsg_global.h \
    MOsg.h \
    MOsgModel.h

INCLUDEPATH += \
    $$PWD/../../3rdPart/OpenSceneGraph-3.6.4/include

win32{
    LIBS += \
        -L$$PWD/../../3rdPart/OpenSceneGraph-3.6.4/lib \
            -losgViewerd -losgTextd -losgGAd  -losgDBd -lzlibd -losgUtild -losgd -lOpenThreadsd -losgFXd \
        -L$$PWD/../../3rdPart/OpenSceneGraph-3rdparty/lib \
            -zlibd

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
    OutputBinDir = $$PWD/../../Bin
    OutputBinDir = $$replace(OutputBinDir, /, \\)
    OutputLibDir = $$PWD/../../Lib
    OutputLibDir = $$replace(OutputLibDir, /, \\)
    //执行copy命令
    QMAKE_POST_LINK += copy /Y $$TargetDll $$OutputBinDir && copy /Y $$TargetLib $$OutputLibDir
}

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target

include($$PWD/../Common.pri)
