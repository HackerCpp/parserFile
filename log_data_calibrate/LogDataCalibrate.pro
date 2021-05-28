QT += sql core gui widgets charts

TEMPLATE = lib
DEFINES += LOGDATACALIBRATE_LIBRARY

CONFIG += c++17

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
INCLUDEPATH += \
    ../log_data_lib/include/logData \
    ../log_data_lib/include/blocks \
    ../log_data_lib/include/curves \
    ../log_data_lib/include/externalComponents \
    ../log_data_saver/inc \
    ../log_data_loader/include

LIBS += ../build/release/LogData.lib \
        ../build/release/LogDataSaver.lib \
        ../build/release/LogDataLoader.lib

include(../log_data_graphics/graphics.pri)
SOURCES += \
    calibratenoise.cpp \
    coefficientsdisplaying.cpp \
    geologysqlitedb.cpp \
    logdatacalibrate.cpp \
    referencesaver.cpp \
    spectrsset.cpp \
    selectcurvedb.cpp

HEADERS += \
    LogDataCalibrate_global.h \
    calibratenoise.h \
    coefficientsdisplaying.h \
    geologysqlitedb.h \
    logdatacalibrate.h \
    referencesaver.h \
    spectrsset.h \
    selectcurvedb.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target
