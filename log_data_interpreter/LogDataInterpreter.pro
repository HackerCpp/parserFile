TEMPLATE = lib
DEFINES += INTERPRETER_LIBRARY #MINI_VERSION
CONFIG += c++17

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets core

INCLUDEPATH += include \
../log_data_lib/include/externalComponents\
../log_data_lib/include/curves \
../log_data_lib/include/blocks \
libs/PythonQT3.2/src \
libs/PythonQT3.2/extensions/PythonQt_QtAll \
libs/python3/python38_x64-windows/include/python3.8\
libs/QScintilla/Qt4Qt5

!contains(DEFINES,MINI_VERSION):{
LIBS += $$PWD/libs/PythonQT3.2/build/lib/PythonQt-Qt5-Python383.lib \
        $$PWD/libs/PythonQT3.2/build/lib/PythonQt_QtAll-Qt5-Python383.lib \
        $$PWD/libs/python3/python38_x64-windows/lib/python38.lib \
        ../build/release/LogData.lib \
        $$PWD/libs/QScintilla/build/release/qscintilla2_qt5.lib

HEADERS += \
    include/interpreter_global.h \
    include/Wrapper_python.h \
    include/interpreterPython.h \
    include/pythoneditor.h

SOURCES += \
    src/Wrapper_python.cpp \
    src/interpreterPython.cpp \
    src/pythoneditor.cpp
}

contains(DEFINES,MINI_VERSION):{
   LIBS += ../build86/release/LogData.dll
}

HEADERS += \
    include/interpretercreater.h \
    include/translaterrustoing.h

SOURCES += \
    src/interpretercreater.cpp \
    src/translaterrustoing.cpp

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS
# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0



# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target
