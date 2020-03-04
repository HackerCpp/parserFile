QT -= gui

TEMPLATE = lib
CONFIG += staticlib
#CONFIG += dynamiclib


CONFIG += c++17
INCLUDEPATH += include/blocks \
    include/curves \
    include/logData \
    include/externalComponents

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
    src/externalComponents/ainterpreterlogdata.cpp \
    src/externalComponents/iinterpreterlogdata.cpp \
    src/blocks/ablock.cpp \
    src/curves/acurve.cpp \
    src/externalComponents/aloaderlogdata.cpp \
    src/logData/alogdata.cpp \
    src/blocks/datablock.cpp \
    src/blocks/iblock.cpp \
    src/curves/icurve.cpp \
    src/externalComponents/iloaderlogdata.cpp \
    src/logData/ilogdata.cpp \
    src/logData/logdata.cpp

HEADERS += \
    include/blocks/ablock.h \
    include/curves/acurve.h \
    include/externalComponents/ainterpreterlogdata.h \
    include/externalComponents/aloaderlogdata.h \
    include/externalComponents/iinterpreterlogdata.h \
    include/logData/alogdata.h \
    include/blocks/datablock.h \
    include/blocks/iblock.h \
    include/curves/icurve.h \
    include/externalComponents/iloaderlogdata.h \
    include/logData/ilogdata.h \
    include/logData/logdata.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target
