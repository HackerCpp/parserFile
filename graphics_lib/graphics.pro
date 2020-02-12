QT += core gui widgets opengl xml

TEMPLATE = lib
#CONFIG += staticlib
#CONFIG += dynamiclib
CONFIG += c++11
INCLUDEPATH += inc/
INCLUDEPATH+= ../gfm_lib/inc
LIBS += ../build/release/GFM.lib

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
    src/curvewaveitem.cpp \
    src/mainvalue.cpp \
    src/tabgroupsettings.cpp \
    src/tabcurvesettings.cpp \
    src/tabgeneralsettings.cpp \
    src/border.cpp \
    src/ruler.cpp \
    src/headeritem.cpp \
    src/grid.cpp \
    src/whitesubstrate.cpp \
    src/basegroup.cpp \
    src/curvelineItem.cpp \
    src/curvebaseitem.cpp \
    src/group.cpp \
    src/canvas.cpp \
    src/graphics.cpp \
    src/mainvaluescontainer.cpp

HEADERS += \
    inc/border.h \
    inc/basegroup.h \
    inc/canvas.h \
    inc/curvebaseitem.h \
    inc/curvelineItem.h \
    inc/curvewaveitem.h \
    inc/graphics.h \
    inc/grid.h \
    inc/group.h \
    inc/headeritem.h \
    inc/mainvalue.h \
    inc/ruler.h \
    inc/tabcurvesettings.h \
    inc/tabgeneralsettings.h \
    inc/tabgroupsettings.h \
    inc/whitesubstrate.h \
    inc/mainvaluescontainer.h

# Default rules for deployment.
unix {
    target.path = $$[QT_INSTALL_PLUGINS]/generic
}
!isEmpty(target.path): INSTALLS += target
