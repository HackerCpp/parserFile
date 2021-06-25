QT += sql core gui widgets charts printsupport webenginewidgets
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
    src/calibratenoise.cpp \
    src/coefficientsdisplaying.cpp \
    src/coeffs.cpp \
    src/geologysqlitedb.cpp \
    src/logdatacalibrate.cpp \
    src/operator.cpp \
    src/picturechart.cpp \
    src/protocolcreater.cpp \
    src/protocolinfo.cpp \
    src/protocolnoise.cpp \
    src/referencesaver.cpp \
    src/saverloadercalibdb.cpp \
    src/selectingidfromdb.cpp \
    src/spectrsset.cpp \
    src/referenceLoader.cpp

HEADERS += \
    src/LogDataCalibrate_global.h \
    src/calibratenoise.h \
    src/coefficientsdisplaying.h \
    src/coeffs.h \
    src/geologysqlitedb.h \
    src/logdatacalibrate.h \
    src/operator.h \
    src/picturechart.h \
    src/protocolcreater.h \
    src/protocolinfo.h \
    src/protocolnoise.h \
    src/referencesaver.h \
    src/saverloadercalibdb.h \
    src/selectingidfromdb.h \
    src/spectrsset.h \
    src/referenceLoader.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target
