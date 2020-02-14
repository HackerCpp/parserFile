QT += gui xml
CONFIG += c++11
INCLUDEPATH += $$PWD $$PWD/inc
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
    $$PWD/src/track.cpp \
    $$PWD/src/board.cpp \
    $$PWD/src/forms.cpp \
    $$PWD/src/formsblockgfm.cpp \
    $$PWD/src/desc.cpp \
    $$PWD/src/shortcut.cpp \
    $$PWD/src/curvefloat32.cpp \
    $$PWD/src/curveint16.cpp \
    $$PWD/src/curveint32.cpp \
    $$PWD/src/curveint8.cpp \
    $$PWD/src/curveuint16.cpp \
    $$PWD/src/curveuint32.cpp \
    $$PWD/src/curveuint8.cpp \
    $$PWD/src/curve.cpp \
    $$PWD/src/headerblockgfm.cpp \
    $$PWD/src/toolinfoblockgfm.cpp \
    $$PWD/src/unknownblockgfm.cpp \
    $$PWD/src/datablockgfm.cpp \
    $$PWD/src/abstractblockgfm.cpp \
    $$PWD/src/gfm.cpp \
    $$PWD/src/iteminfo.cpp

HEADERS += \
    $$PWD/inc/abstractblockgfm.h \
    $$PWD/inc/board.h \
    $$PWD/inc/curve.h \
    $$PWD/inc/curvefloat32.h \
    $$PWD/inc/curveint16.h \
    $$PWD/inc/curveint32.h \
    $$PWD/inc/curveint8.h \
    $$PWD/inc/curveuint16.h \
    $$PWD/inc/curveuint32.h \
    $$PWD/inc/curveuint8.h \
    $$PWD/inc/datablockgfm.h \
    $$PWD/inc/desc.h \
    $$PWD/inc/forms.h \
    $$PWD/inc/formsblockgfm.h \
    $$PWD/inc/gfm.h \
    $$PWD/inc/headerblockgfm.h \
    $$PWD/inc/shortcut.h \
    $$PWD/inc/toolinfoblockgfm.h \
    $$PWD/inc/track.h \
    $$PWD/inc/unknownblockgfm.h \
    $$PWD/inc/iteminfo.h

# Default rules for deployment.
unix {
    target.path = $$[QT_INSTALL_PLUGINS]/generic
}
!isEmpty(target.path): INSTALLS += target
