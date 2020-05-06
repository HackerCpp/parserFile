CONFIG+=qt
TEMPLATE = lib
DEFINES += INTERPRETER_LIBRARY
CONFIG += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

INCLUDEPATH += include \
../log_data_lib/include/externalComponents\
../log_data_lib/include/curves \
../log_data_lib/include/blocks \
../PythonQT3.2/src \
../PythonQT3.2/extensions/PythonQt_QtAll \
../python3/python3_x64-windows/include/python3.7

LIBS += ../PythonQT3.2/build/lib/PythonQt-Qt5-Python373.lib \
        ../PythonQT3.2/build/lib/PythonQt_QtAll-Qt5-Python373.lib\
        ../python3/python3_x64-windows/lib/python37.lib \
../build/release/LogData.lib
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
    src/Wrapper_python.cpp \
    src/interpreterPython.cpp

HEADERS += \
    include/Wrapper_python.h \
    include/interpreter_global.h \
    include/interpreterPython.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target
