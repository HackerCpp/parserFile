QT += core gui widgets opengl xml
CONFIG += c++11
INCLUDEPATH += $$PWD $$PWD/inc $$PWD/inc/items
SOURCES += \
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
    $$PWD/inc/items/vacuitem.h \
    $$PWD/inc/items/vlineitem.h \
    $$PWD/inc/items/vmarkitem.h \
    $$PWD/inc/objectoftheboard.h \
    $$PWD/inc/rightborder.h \
    $$PWD/inc/verticalboard.h \
    $$PWD/inc/items/verticalitem.h \
    $$PWD/inc/verticaltrack.h \
    $$PWD/inc/ruler.h
