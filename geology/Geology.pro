QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECARTED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
INCLUDEPATH += inc\
               ../log_data_lib/include/logData \
               ../log_data_lib/include/blocks \
               ../log_data_lib/include/curves \
               ../log_data_lib/include/externalComponents \
               ../log_data_loader/include \
                ../log_data_saver/inc \
                ../log_data_interpreter/include \
                ../PythonQT3.2/src \
                ../PythonQT3.2/extensions/PythonQt_QtAll \
                ../python3\python3_x64-windows\include\python3.7 \

LIBS += \
../build/release/LogData.lib \
../build/release/LogDataInterpreter.lib \
../build/release/LogDataLoader.lib \
../build/release/LogDataSaver.lib \
../python3/python3_x64-windows/lib/python37.lib \

include(../graphics_lib/graphics.pri)



SOURCES += \
    inc/tabinterpretations.cpp \
    src/graphicscontrolpanel.cpp \
    src/graphicwidget.cpp \
    src/newcurvetab.cpp \
    src/datamodel.cpp \
    src/datatreeview.cpp \
    src/logdataview.cpp \
    src/windowformenu.cpp \
    src/main.cpp \
    src/mainwindow.cpp \
    src/menu.cpp \
    src/filereader.cpp\

HEADERS += \
    inc/datamodel.h \
    inc/datatreeview.h \
    inc/graphicscontrolpanel.h \
    inc/graphicwidget.h \
    inc/logdataview.h \
    inc/mainwindow.h \
    inc/menu.h \
    inc/newcurvetab.h \
    inc/tabinterpretations.h \
    inc/windowformenu.h \
    inc/filereader.h \


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc
