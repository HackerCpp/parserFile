QT -= gui

TEMPLATE = lib
CONFIG += staticlib
#CONFIG += dynamiclib


CONFIG += c++17
INCLUDEPATH += include/blocks \
    include/curves \
    include/logData \
    include/externalComponents \
    include/customObject
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
    include/curves/linking.cpp \
    src/customObject/customobject.cpp \
    src/customObject/customobjectiteminfo.cpp \
    src/blocks/iteminfocreater.cpp \
    src/blocks/acuItem.cpp \
    src/blocks/lineItem.cpp \
    src/blocks/specItem.cpp \
    src/customObject/primitive.cpp \
    src/externalComponents/asaverlogdata.cpp \
    src/externalComponents/isaverlogdata.cpp \
    src/blocks/astyleitem.cpp \
    src/blocks/aitem.cpp \
    src/blocks/atrack.cpp \
    src/blocks/items.cpp \
    src/blocks/markItem.cpp \
    src/blocks/track.cpp \
    src/blocks/aboard.cpp \
    src/blocks/iboard.cpp \
    src/blocks/board.cpp \
    src/blocks/unknownblock.cpp \
    src/blocks/formsblock.cpp \
    src/blocks/headerblock.cpp \
    src/blocks/toolinfoblock.cpp \
    src/blocks/datablock.cpp \
    src/blocks/iblock.cpp \
    src/blocks/shortcut.cpp\
    src/curves/curve.cpp \
    src/externalComponents/ainterpreterlogdata.cpp \
    src/externalComponents/iinterpreterlogdata.cpp \
    src/blocks/ablock.cpp \
    src/curves/acurve.cpp \
    src/externalComponents/aloaderlogdata.cpp \
    src/logData/alogdata.cpp \
    src/curves/icurve.cpp \
    src/externalComponents/iloaderlogdata.cpp \
    src/logData/ilogdata.cpp \
    src/logData/logdata.cpp \
    src/curves/desc.cpp


HEADERS += \
    include/curves/linking.h \
    include/blocks/ablock.h \
    include/blocks/aboard.h \
    include/blocks/acuItem.h \
    include/blocks/aitem.h \
    include/blocks/astyleitem.h \
    include/blocks/atrack.h \
    include/blocks/formsblock.h \
    include/blocks/headerblock.h \
    include/blocks/iboard.h \
    include/blocks/iteminfocreater.h \
    include/blocks/items.h \
    include/blocks/lineItem.h \
    include/blocks/markItem.h \
    include/blocks/specItem.h \
    include/blocks/toolinfoblock.h \
    include/blocks/datablock.h \
    include/blocks/iblock.h \
    include/blocks/shortcut.h \
    include/blocks/unknownblock.h \
    include/blocks/board.h \
    include/blocks/track.h \
    include/curves/acurve.h \
    include/customObject/customobject.h \
    include/customObject/customobjectiteminfo.h \
    include/customObject/primitive.h \
    include/externalComponents/ainterpreterlogdata.h \
    include/externalComponents/aloaderlogdata.h \
    include/externalComponents/asaverlogdata.h \
    include/externalComponents/iinterpreterlogdata.h \
    include/externalComponents/isaverlogdata.h \
    include/logData/alogdata.h \
    include/curves/icurve.h \
    include/externalComponents/iloaderlogdata.h \
    include/logData/ilogdata.h \
    include/logData/logdata.h \
    include/curves/curve.h\
    include/curves/desc.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target
