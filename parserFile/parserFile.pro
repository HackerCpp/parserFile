#-------------------------------------------------
#
# Project created by QtCreator 2019-07-18T08:44:09
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets opengl

TARGET = parserFile
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11
INCLUDEPATH+= ../gfm_lib/inc ../graphics_lib/inc
LIBS += ../build/debug/GFM.dll ../build/debug/graphics.dll
SOURCES += \
    src/tabs/abstracttab.cpp \
    #src/fileCreation/creategfm.cpp \
    src/graphic/wave.cpp \
    src/graphic/basecurveclass.cpp \
    #src/graphic/grid.cpp \
    src/graphic/spectr.cpp \
        src/main.cpp \
        src/mainwindow.cpp \
    src/filereader.cpp \
    src/parsers/parsertlm.cpp \
    src/parsers/parsergfm.cpp \
    src/parsers/findblocks.cpp \
    src/models/modeltlm.cpp \
    src/reedsolomoncoding.cpp \
    src/crc16.cpp \
    src/parsers/parserDataCm.cpp \
    src/parsers/parser38k.cpp \
    src/models/model38k.cpp \
    src/menu.cpp \
    src/filehandler.cpp \
    src/tabs/abstracttabsavefiles.cpp \
    src/tabs/tab38k.cpp \
    src/fileCreation/csv.cpp \
    src/tabs/tabgfm.cpp \
    src/models/modelgfm.cpp \
    src/graphic/curveline.cpp\
    src/tabs/graphicsview.cpp

HEADERS += \
    #inc/fileCreation/creategfm.h \
    inc/graphic/IndexColor.h \
    inc/graphic/wave.h \
        inc/mainwindow.h \
    inc/filereader.h \
    inc/parsers/parsertlm.h \
    inc/parsers/parsergfm.h \
    inc/parsers/findblocks.h \
    inc/models/modeltlm.h \
    inc/reedsolomoncoding.h \
    inc/crc16.h \
    inc/parsers/parserDataCm.h \
    inc/parsers/parser38k.h \
    inc/models/model38k.h \
    inc/menu.h \
    inc/filehandler.h \
    inc/tabs/abstracttab.h \
    inc/tabs/abstracttabsavefiles.h \
    inc/tabs/tab38k.h \
    inc/fileCreation/csv.h \
    inc/tabs/tabgfm.h \
    inc/models/modelgfm.h \
    inc/graphic/curveline.h \
    inc/tabs/graphicsview.h \
    inc/graphic/basecurveclass.h \
    #inc/graphic/grid.h \
    inc/graphic/spectr.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc

