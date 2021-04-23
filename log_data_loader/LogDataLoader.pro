QT -= gui

TEMPLATE = lib
DEFINES += LOADER_LIBRARY
DEFINES +=   VERSION_LIB=\\\"0.0.5\\\"

CONFIG += C++17

INCLUDEPATH += include \
../log_data_lib/include/externalComponents \
../log_data_lib/include/blocks \
../log_data_saver/inc \
../log_data_lib/include/curves

contains(QMAKE_HOST.arch, x86_64):{
    LIBS += ../build/release/LogData.lib
}
#!contains(QMAKE_HOST.arch, x86_64):{
#    LIBS += ../build86/release/LogData.dll \
#   ../build86/release/zlib1.dll
 #   DEFINES += USING_X86
#}


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
    src/loaderviaconvertergtk.cpp \
    src/lisloader.cpp \
    src/geoloader.cpp \
    src/lasloader.cpp \
    src/gfmloader.cpp

HEADERS += \
    include/geoloader.h \
    include/gfmloader.h \
    include/lasloader.h \
    include/lisloader.h \
    include/loader_global.h \
    include/loaderviaconvertergtk.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target
