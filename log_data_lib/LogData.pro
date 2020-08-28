INCLUDEPATH += $$PWD/include/blocks \
    $$PWD/include/curves \
    $$PWD/include/logData \
    $$PWD/include/externalComponents \
    $$PWD/include/customObject
# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    $$PWD/include/curves/linking.cpp \
    $$PWD/src/customObject/customobject.cpp \
    $$PWD/src/customObject/customobjectiteminfo.cpp \
    $$PWD/src/blocks/iteminfocreater.cpp \
    $$PWD/src/blocks/acuItem.cpp \
    $$PWD/src/blocks/lineItem.cpp \
    $$PWD/src/blocks/specItem.cpp \
    $$PWD/src/customObject/primitive.cpp \
    $$PWD/src/externalComponents/asaverlogdata.cpp \
    $$PWD/src/externalComponents/isaverlogdata.cpp \
    $$PWD/src/blocks/astyleitem.cpp \
    $$PWD/src/blocks/aitem.cpp \
    $$PWD/src/blocks/atrack.cpp \
    $$PWD/src/blocks/items.cpp \
    $$PWD/src/blocks/markItem.cpp \
    $$PWD/src/blocks/track.cpp \
    $$PWD/src/blocks/aboard.cpp \
    $$PWD/src/blocks/iboard.cpp \
    $$PWD/src/blocks/board.cpp \
    $$PWD/src/blocks/unknownblock.cpp \
    $$PWD/src/blocks/formsblock.cpp \
    $$PWD/src/blocks/headerblock.cpp \
    $$PWD/src/blocks/toolinfoblock.cpp \
    $$PWD/src/blocks/datablock.cpp \
    $$PWD/src/blocks/iblock.cpp \
    $$PWD/src/blocks/shortcut.cpp\
    $$PWD/src/curves/curve.cpp \
    $$PWD/src/externalComponents/ainterpreterlogdata.cpp \
    $$PWD/src/externalComponents/iinterpreterlogdata.cpp \
    $$PWD/src/blocks/ablock.cpp \
    $$PWD/src/curves/acurve.cpp \
    $$PWD/src/externalComponents/aloaderlogdata.cpp \
    $$PWD/src/logData/alogdata.cpp \
    $$PWD/src/curves/icurve.cpp \
    $$PWD/src/externalComponents/iloaderlogdata.cpp \
    $$PWD/src/logData/ilogdata.cpp \
    $$PWD/src/logData/logdata.cpp \
    $$PWD/src/curves/desc.cpp


HEADERS += \
    $$PWD/include/curves/linking.h \
    $$PWD/include/blocks/ablock.h \
    $$PWD/include/blocks/aboard.h \
    $$PWD/include/blocks/acuItem.h \
    $$PWD/include/blocks/aitem.h \
    $$PWD/include/blocks/astyleitem.h \
    $$PWD/include/blocks/atrack.h \
    $$PWD/include/blocks/formsblock.h \
    $$PWD/include/blocks/headerblock.h \
    $$PWD/include/blocks/iboard.h \
    $$PWD/include/blocks/iteminfocreater.h \
    $$PWD/include/blocks/items.h \
    $$PWD/include/blocks/lineItem.h \
    $$PWD/include/blocks/markItem.h \
    $$PWD/include/blocks/specItem.h \
    $$PWD/include/blocks/toolinfoblock.h \
    $$PWD/include/blocks/datablock.h \
    $$PWD/include/blocks/iblock.h \
    $$PWD/include/blocks/shortcut.h \
    $$PWD/include/blocks/unknownblock.h \
    $$PWD/include/blocks/board.h \
    $$PWD/include/blocks/track.h \
    $$PWD/include/curves/acurve.h \
    $$PWD/include/customObject/customobject.h \
    $$PWD/include/customObject/customobjectiteminfo.h \
    $$PWD/include/customObject/primitive.h \
    $$PWD/include/externalComponents/ainterpreterlogdata.h \
    $$PWD/include/externalComponents/aloaderlogdata.h \
    $$PWD/include/externalComponents/asaverlogdata.h \
    $$PWD/include/externalComponents/iinterpreterlogdata.h \
    $$PWD/include/externalComponents/isaverlogdata.h \
    $$PWD/include/logData/alogdata.h \
    $$PWD/include/curves/icurve.h \
    $$PWD/include/externalComponents/iloaderlogdata.h \
    $$PWD/include/logData/ilogdata.h \
    $$PWD/include/logData/logdata.h \
    $$PWD/include/curves/curve.h\
    $$PWD/include/curves/desc.h

# Default rules for deployment.

