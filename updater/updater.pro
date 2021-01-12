QT       += core gui network gui_private

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS
#DEFINES += USE_LIBZIP

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
contains(DEFINES, USE_LIBZIP) {
    contains(QMAKE_HOST.arch, x86_64):{
        INCLUDEPATH += zip/libzip_x64-windows/include
        LIBS += ../zip/libzip_x64-windows/lib/zip.lib
    }
    !contains(QMAKE_HOST.arch, x86_64):{
        INCLUDEPATH += zip/minGw
        LIBS += ../zip/minGw/libzip.dll
    }
    SOURCES += libzippp.cpp
    HEADERS += libzippp.h
}


SOURCES += \
    customprogressbar.cpp \
    infiniteloading.cpp \
    loader.cpp \
    main.cpp \
    mainwindow.cpp \
    module.cpp \
    modulesmodel.cpp \
    modulesusermodel.cpp \
    projectpathnamewidget.cpp \
    unpacker.cpp \
    updatewindow.cpp

HEADERS += \
    customprogressbar.h \
    infiniteloading.h \
    loader.h \
    mainwindow.h \
    module.h \
    modulesmodel.h \
    modulesusermodel.h \
    projectpathnamewidget.h \
    unpacker.h \
    updatewindow.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += res.qrc
