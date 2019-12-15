QT += gui xml
TEMPLATE = lib
#CONFIG += staticlib
CONFIG += dynamiclib
CONFIG += c++11
INCLUDEPATH+=inc/
LIBS += -L/usr/lib/zlibrary/ui -lz

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
    src/track.cpp \
    src/board.cpp \
    src/forms.cpp \
    src/formsblockgfm.cpp \
    src/desc.cpp \
    src/shortcut.cpp \
    src/curvefloat32.cpp \
    src/curveint16.cpp \
    src/curveint32.cpp \
    src/curveint8.cpp \
    src/curveuint16.cpp \
    src/curveuint32.cpp \
    src/curveuint8.cpp \
    src/curve.cpp \
    src/headerblockgfm.cpp \
    src/toolinfoblockgfm.cpp \
    src/unknownblockgfm.cpp \
    src/datablockgfm.cpp \
    src/abstractblockgfm.cpp \
    src/gfm.cpp \
    src/iteminfo.cpp

HEADERS += \
    inc/abstractblockgfm.h \
    inc/board.h \
    inc/curve.h \
    inc/curvefloat32.h \
    inc/curveint16.h \
    inc/curveint32.h \
    inc/curveint8.h \
    inc/curveuint16.h \
    inc/curveuint32.h \
    inc/curveuint8.h \
    inc/datablockgfm.h \
    inc/desc.h \
    inc/forms.h \
    inc/formsblockgfm.h \
    inc/gfm.h \
    inc/headerblockgfm.h \
    inc/shortcut.h \
    inc/toolinfoblockgfm.h \
    inc/track.h \
    inc/unknownblockgfm.h \
    inc/iteminfo.h

# Default rules for deployment.
unix {
    target.path = $$[QT_INSTALL_PLUGINS]/generic
}
!isEmpty(target.path): INSTALLS += target
