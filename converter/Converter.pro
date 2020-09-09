QT       += core gui widgets

CONFIG += c++17

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
INCLUDEPATH += ../gtk/win32/include/gtk-3.0/gtk \
                ../gtk/win32/include/gtk-3.0 \
                ../gtk/win32/include/glib-2.0 \
                ../gtk/win32/include/pango-1.0 \
                ../gtk/win32/include/cairo \
                ../gtk/win32/include/gdk-pixbuf-2.0 \
                ../gtk/win32/include/atk-1.0 \
                ../gtk/win32/share/gettext \
                ../gtk/win32/include \
                ../gtk/win32/include/harfbuzz \
                ../gtk/win32/include/libxml2
LIBS += ../../gtk/win32/bin\libgtk-3-0.dll \
                ../../gtk/win32/bin/libgettextlib-0-19-8-1.dll \
                ../../gtk/win32/bin/libgettextpo-0.dll \
                ../../gtk/win32/bin/libgio-2.0-0.dll \
                ../../gtk/win32/bin/libglib-2.0-0.dll \
                ../../gtk/win32/bin/libgobject-2.0-0.dll \
                ../../gtk/win32/bin/libiconv-2.dll \
                ../../gtk/win32/bin/libintl-8.dll \
                ../../gtk/win32/bin/libpango-1.0-0.dll \
                ../../gtk/win32/bin/libpng16-16.dll \
                ../../gtk/win32/bin/libxml2-2.dll

SOURCES += \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    mainwindow.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
