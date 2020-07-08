QT += core gui widgets opengl xml charts

CONFIG += c++11
INCLUDEPATH += $$PWD $$PWD/inc $$PWD/inc/items $$PWD/inc/tools $$PWD/inc/spectrReader $$PWD/../QScintilla/Qt4Qt5

LIBS += \
        ../build/release/LogData.lib \
        ../PythonQT3.2/build/lib/PythonQt-Qt5-Python373.lib \
        ../PythonQT3.2/build/lib/PythonQt_QtAll-Qt5-Python373.lib\
        ../python3/python3_x64-windows/lib/python37.lib \
        ../QScintilla/build/release/qscintilla2_qt5.lib \
#../build/release/LogDataInterpreter.lib \
#../build/release/LogDataLoader.lib \
#../build/release/LogDataSaver.lib \


SOURCES += \
    $$PWD/inc/spectrReader/chartvievforonewavewidget.cpp \
    $$PWD/inc/spectrReader/modelmulticolor.cpp \
    $$PWD/inc/spectrReader/modelonewave.cpp \
    $$PWD/inc/tools/pythoneditor.cpp \
    $$PWD/src/spectrReader/graphicitemforspectr.cpp \
    $$PWD/src/spectrReader/spectrscene.cpp \
    $$PWD/src/spectrReader/spectrviewer.cpp \
    $$PWD/src/spectrReader/spectrreader.cpp \
    $$PWD/src/drawsettings.cpp \
    $$PWD/src/spectrReader/filterlistview.cpp \
    $$PWD/src/spectrReader/onewavewidget.cpp \
    $$PWD/src/tools/basecurvereader.cpp \
    $$PWD/src/spectrReader/filterListModel.cpp \
    $$PWD/src/items/drawingthroughadisk.cpp \
    $$PWD/src/tools/colorscale.cpp \
    $$PWD/src/tools/basesettingswindow.cpp \
    $$PWD/src/tools/curveeditor.cpp \
    $$PWD/src/tools/modelcurveeditor.cpp \
    $$PWD/src/tools/customdelegates.cpp \
    $$PWD/src/tools/browsergraphicitems.cpp \
    $$PWD/src/tools/modelforgraphicsitems.cpp \
    $$PWD/src/tools/settingsitem.cpp \
    $$PWD/src/tools/selectingarea.cpp \
    $$PWD/src/items/vacuitem.cpp \
    $$PWD/src/items/vspectritem.cpp \
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
    $$PWD/src/tools/qxtspanslider.cpp \

HEADERS += \
    $$PWD/inc/drawsettings.h \
    $$PWD/inc/spectrReader/chartvievforonewavewidget.h \
    $$PWD/inc/spectrReader/filterListModel.h \
    $$PWD/inc/spectrReader/modelmulticolor.h \
    $$PWD/inc/spectrReader/modelonewave.h \
    $$PWD/inc/spectrReader/spectrreader.h \
    $$PWD/inc/spectrReader/filterlistview.h \
    $$PWD/inc/spectrReader/graphicitemforspectr.h \
    $$PWD/inc/spectrReader/onewavewidget.h \
    $$PWD/inc/spectrReader/spectrscene.h \
    $$PWD/inc/spectrReader/spectrviewer.h \
    $$PWD/inc/agraphicboard.h \
    $$PWD/inc/items/agraphicitem.h \
    $$PWD/inc/agraphictrack.h \
    $$PWD/inc/boardfortrack.h \
    $$PWD/inc/graphiceditor.h \
    $$PWD/inc/igraphiceditor.h \
    $$PWD/inc/items/drawingthroughadisk.h \
    $$PWD/inc/items/itimscreater.h \
    $$PWD/inc/tools/basecurvereader.h \
    $$PWD/inc/tools/basesettingswindow.h \
    $$PWD/inc/tools/browsergraphicitems.h \
    $$PWD/inc/tools/colorscale.h \
    $$PWD/inc/tools/curveeditor.h \
    $$PWD/inc/tools/customdelegates.h \
    $$PWD/inc/tools/modelcurveeditor.h \
    $$PWD/inc/tools/modelforgraphicsitems.h \
    $$PWD/inc/tools/pythoneditor.h \
    $$PWD/inc/tools/selectingarea.h \
    $$PWD/inc/items/vacuitem.h \
    $$PWD/inc/items/vspectritem.h \
    $$PWD/inc/items/vlineitem.h \
    $$PWD/inc/items/vmarkitem.h \
    $$PWD/inc/objectoftheboard.h \
    $$PWD/inc/rightborder.h \
    $$PWD/inc/tools/settingsitem.h \
    $$PWD/inc/verticalboard.h \
    $$PWD/inc/items/verticalitem.h \
    $$PWD/inc/verticaltrack.h \
    $$PWD/inc/ruler.h\
    $$PWD/inc/tools/qxtspanslider.h \
    $$PWD/inc/tools/qxtspanslider_p.h
