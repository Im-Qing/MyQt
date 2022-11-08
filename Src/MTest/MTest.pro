QT       += core gui positioning location opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

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
    main.cpp \
    MMainWindow.cpp \

HEADERS += \
    MMainWindow.h \

FORMS += \
    MMainWindow.ui

INCLUDEPATH += \
    $$PWD/../../3rdPart \
    $$PWD/../../Src \
    $$PWD/../../3rdPart/OpenSceneGraph-3.6.4/include

RESOURCES += \
    Res.qrc

DEPENDPATH += \
    $$PWD/../MWidget \
    $$PWD/../MCore

win32{
    LIBS += \
        -L$$PWD/../../Lib/Win \
            -lMCored -lMWidgetd  -lMOsgd \
        -L$$PWD/../../3rdPart/OpenSceneGraph-3.6.4/lib \
            -losgViewerd -losgTextd -losgGAd  -losgDBd -lzlibd -losgUtild -losgd -lOpenThreadsd

    DESTDIR = $$PWD/../../Bin/Win
}
mac{
    CONFIG(debug,debug|release){
        LIBS += \
            -L$$PWD/../../Temp/Src/MWidget -lMWidgetd \
            -L$$PWD/../../Temp/Src/MCore -lMCored \
            -L$$PWD/../../Temp/Src/MOsg -lMOsgd
    }
    CONFIG(release,debug|release){
        LIBS += \
            -L$$PWD/../../Temp/Src/MWidget -lMWidget \
            -L$$PWD/../../Temp/Src/MCore -lMCore \
            -L$$PWD/../../Temp/Src/MOsg -lMOsg
    }

    DESTDIR = $$PWD/../../Bin/Mac
}

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
