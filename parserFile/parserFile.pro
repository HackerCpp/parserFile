#-------------------------------------------------
#
# Project created by QtCreator 2019-07-18T08:44:09
#
#-------------------------------------------------

QT       += core gui xml

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
INCLUDEPATH+=\
../graphics_lib/inc \
../log_data_lib/include/logData \
../log_data_lib/include/externalComponents \
../log_data_lib/include/blocks \
../log_data_lib/include/curves \
../log_data_loader/include \
../log_data_saver/inc \
../log_data_interpreter/include \
../PythonQT3.2/src \
../PythonQT3.2/extensions/PythonQt_QtAll \
../python3\python3_x64-windows\include\python3.7


LIBS += \
../build/release/LogData.lib \
../build/release/LogDataInterpreter.lib \
../build/release/LogDataLoader.lib \
../build/release/LogDataSaver.lib \
../PythonQT3.2/build/lib/PythonQt-Qt5-Python373.lib \
../PythonQT3.2/build/lib/PythonQt_QtAll-Qt5-Python373.lib\
../python3/python3_x64-windows/lib/python37.lib \
#../build/release/graphics.lib

#include(../gfm_lib/GFM.pri)
include(../graphics_lib/graphics.pri)

SOURCES += \
    inc/logdataview.cpp \
    src/tabs/abstracttab.cpp \
    #src/fileCreation/creategfm.cpp \
    src/main.cpp \
    src/mainwindow.cpp \
    src/filereader.cpp \
    src/parsers/parsertlm.cpp \
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
    #src/models/modelgfm.cpp \
    #src/tabs/graphicsview.cpp

HEADERS += \
    #inc/fileCreation/creategfm.h \
    inc/logdataview.h \
     inc/mainwindow.h \
    inc/filereader.h \
    inc/parsers/parsertlm.h \
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
    #inc/models/modelgfm.h \
    #inc/tabs/graphicsview.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc

