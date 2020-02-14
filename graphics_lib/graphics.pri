QT += core gui widgets opengl xml
CONFIG += c++11
INCLUDEPATH += $$PWD $$PWD/inc
SOURCES += \
    $$PWD/src/curvewaveitem.cpp \
    $$PWD/src/mainvalue.cpp \
    $$PWD/src/tabgroupsettings.cpp \
    $$PWD/src/tabcurvesettings.cpp \
    $$PWD/src/tabgeneralsettings.cpp \
    $$PWD/src/border.cpp \
    $$PWD/src/ruler.cpp \
    $$PWD/src/headeritem.cpp \
    $$PWD/src/grid.cpp \
    $$PWD/src/whitesubstrate.cpp \
    $$PWD/src/basegroup.cpp \
    $$PWD/src/curvelineItem.cpp \
    $$PWD/src/curvebaseitem.cpp \
    $$PWD/src/group.cpp \
    $$PWD/src/canvas.cpp \
    $$PWD/src/graphics.cpp \
    $$PWD/src/mainvaluescontainer.cpp

HEADERS += \
    $$PWD/inc/border.h \
    $$PWD/inc/basegroup.h \
    $$PWD/inc/canvas.h \
    $$PWD/inc/curvebaseitem.h \
    $$PWD/inc/curvelineItem.h \
    $$PWD/inc/curvewaveitem.h \
    $$PWD/inc/graphics.h \
    $$PWD/inc/grid.h \
    $$PWD/inc/group.h \
    $$PWD/inc/headeritem.h \
    $$PWD/inc/mainvalue.h \
    $$PWD/inc/ruler.h \
    $$PWD/inc/tabcurvesettings.h \
    $$PWD/inc/tabgeneralsettings.h \
    $$PWD/inc/tabgroupsettings.h \
    $$PWD/inc/whitesubstrate.h \
    $$PWD/inc/mainvaluescontainer.h
