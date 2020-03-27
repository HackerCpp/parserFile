QT += core gui widgets opengl xml

TEMPLATE = lib
CONFIG += staticlib
#CONFIG += dynamiclib
CONFIG += c++11
INCLUDEPATH += inc/
INCLUDEPATH+= ../log_data_lib/include/curves ../log_data_lib/include/blocks
LIBS += ../build/release/LogData.lib

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
    #src/agraphicitem.cpp \
    #src/verticalitem.cpp \
    #src/rightborder.cpp \
    #src/verticaltrack.cpp \
    #src/agraphictrack.cpp \
    #src/verticalboard.cpp \
    #src/agraphicboard.cpp \
    #src/graphiceditor.cpp \
    #src/igraphiceditor.cpp \
    src/curvewaveitem.cpp \
    src/mainvalue.cpp \
    src/tabgroupsettings.cpp \
    src/tabcurvesettings.cpp \
    src/tabgeneralsettings.cpp \
    src/border.cpp \
    src/ruler.cpp \
    src/headeritem.cpp \
    src/grid.cpp \
    src/basegroup.cpp \
    src/curvelineItem.cpp \
    src/curvebaseitem.cpp \
    src/group.cpp \
    src/canvas.cpp \
    src/graphics.cpp \
    src/mainvaluescontainer.cpp

HEADERS += \
    #inc/agraphicboard.h \
    #inc/agraphicitem.h \
    #inc/agraphictrack.h \
    #inc/graphiceditor.h \
    #inc/igraphiceditor.h \
    #inc/igraphiceditor.h \
    #inc/rightborder.h \
    #inc/verticalboard.h \
    #inc/verticalitem.h \
    #inc/verticaltrack.h
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
    inc/mainvaluescontainer.h


# Default rules for deployment.
unix {
    target.path = $$[QT_INSTALL_PLUGINS]/generic
}
!isEmpty(target.path): INSTALLS += target
