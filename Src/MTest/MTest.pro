QT       += core gui positioning location

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
    easylogging++.cc \
    main.cpp \
    MMainWindow.cpp \
    SystemCapabilityCalculation.cpp \
    MModelTest.cpp

HEADERS += \
    MMainWindow.h \
    SystemCapabilityCalculation.h \
    MModelTest.h \
    easylogging++.h

FORMS += \
    MMainWindow.ui

INCLUDEPATH += \
    $$PWD/../../3rdPart \
    $$PWD/../../Src

RESOURCES += \
    Res.qrc

DEPENDPATH += \
    $$PWD/../MOpenGL \
    $$PWD/../MWidget \
    $$PWD/../MCore

win32{
    LIBS += \
        -L$$PWD/../../Lib -lMOpenGLd -lMCored -lMWidgetd

    DESTDIR = $$PWD/../../Bin
}
mac{
    CONFIG(debug,debug|release){
        LIBS += \
            -L$$PWD/../../Temp/Src/MOpenGL -lMOpenGLd \
            -L$$PWD/../../Temp/Src/MWidget -lMWidgetd \
            -L$$PWD/../../Temp/Src/MCore -lMCored
    }
    CONFIG(release,debug|release){
        LIBS += \
            -L$$PWD/../../Temp/Src/MOpenGL -lMOpenGL \
            -L$$PWD/../../Temp/Src/MWidget -lMWidget \
            -L$$PWD/../../Temp/Src/MCore -lMCore
    }

    DESTDIR = $$PWD/../../Bin/Mac
}

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
