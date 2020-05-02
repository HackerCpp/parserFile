QT += core gui widgets opengl xml

LIBS += -L$$PWD/../SFML/lib
CONFIG(release, debug|release): LIBS += -lsfml-audio -lsfml-graphics -lsfml-main -lsfml-network -lsfml-window -lsfml-system
CONFIG(debug, debug|release): LIBS += -lsfml-audio-d -lsfml-graphics-d -lsfml-main-d -lsfml-network-d -lsfml-window-d -lsfml-system-d
INCLUDEPATH += $$PWD/../SFML/include
DEPENDPATH += $$PWD/../SFML/include

CONFIG += c++11
INCLUDEPATH += $$PWD $$PWD/inc $$PWD/inc/items $$PWD/inc/tools
SOURCES += \
    $$PWD/inc/tools/colorscale.cpp \
    $$PWD/inc/tools/qsfmlcanvas.cpp \
    $$PWD/inc/tools/sfmlitemeditor.cpp \
    $$PWD/src/tools/basesettingswindow.cpp \
    $$PWD/src/tools/curveeditor.cpp \
    $$PWD/src/tools/modelcurveeditor.cpp \
    $$PWD/src/tools/customdelegates.cpp \
    $$PWD/src/tools/browsergraphicitems.cpp \
    $$PWD/src/tools/modelforgraphicsitems.cpp \
    $$PWD/src/tools/settingsitem.cpp \
    $$PWD/src/tools/selectingarea.cpp \
    $$PWD/src/items/vacuitem.cpp \
    $$PWD/src/items/vmarkitem.cpp \
    $$PWD/src/items/vlineitem.cpp \
    $$PWD/src/items/itimscreater.cpp \
    $$PWD/src/ruler.cpp \
    $$PWD/src/boardfortrack.cpp \
    $$PWD/src/objectoftheboard.cpp \
    $$PWD/src/items/agraphicitem.cpp \
    $$PWD/src/items/verticalitem.cpp \
    $$PWD/src/rightborder.cpp \
    $$PWD/src/verticaltrack.cpp \
    $$PWD/src/agraphictrack.cpp \
    $$PWD/src/verticalboard.cpp \
    $$PWD/src/agraphicboard.cpp \
    $$PWD/src/graphiceditor.cpp \
    $$PWD/src/igraphiceditor.cpp \

HEADERS += \
    $$PWD/inc/agraphicboard.h \
    $$PWD/inc/items/agraphicitem.h \
    $$PWD/inc/agraphictrack.h \
    $$PWD/inc/boardfortrack.h \
    $$PWD/inc/graphiceditor.h \
    $$PWD/inc/igraphiceditor.h \
    $$PWD/inc/igraphiceditor.h \
    $$PWD/inc/items/itimscreater.h \
    $$PWD/inc/tools/basesettingswindow.h \
    $$PWD/inc/tools/browsergraphicitems.h \
    $$PWD/inc/tools/colorscale.h \
    $$PWD/inc/tools/curveeditor.h \
    $$PWD/inc/tools/customdelegates.h \
    $$PWD/inc/tools/modelcurveeditor.h \
    $$PWD/inc/tools/modelforgraphicsitems.h \
    $$PWD/inc/tools/qsfmlcanvas.h \
    $$PWD/inc/tools/selectingarea.h \
    $$PWD/inc/items/vacuitem.h \
    $$PWD/inc/items/vlineitem.h \
    $$PWD/inc/items/vmarkitem.h \
    $$PWD/inc/objectoftheboard.h \
    $$PWD/inc/rightborder.h \
    $$PWD/inc/tools/settingsitem.h \
    $$PWD/inc/tools/sfmlitemeditor.h \
    $$PWD/inc/verticalboard.h \
    $$PWD/inc/items/verticalitem.h \
    $$PWD/inc/verticaltrack.h \
    $$PWD/inc/ruler.h

FORMS +=
