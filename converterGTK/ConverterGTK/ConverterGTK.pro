TEMPLATE = app
CONFIG += console c++14
CONFIG -= app_bundle
CONFIG -= qt

INCLUDEPATH += ../../gtk/win32/include/gtk-3.0/gtk \
                ../../gtk/win32/include/gtk-3.0 \
                ../../gtk/win32/include/glib-2.0 \
                ../../gtk/win32/include/pango-1.0 \
                ../../gtk/win32/include/cairo \
                ../../gtk/win32/include/gdk-pixbuf-2.0 \
                ../../gtk/win32/include/atk-1.0 \
                ../../gtk/win32/share/gettext \
                ../../gtk/win32/include \
                ../../gtk/win32/include/harfbuzz \
                ../../gtk/win32/include/libxml2
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
        converter.cpp \
        getfunction.c \
        kedrrc.c \
        loaderdll.cpp \
        main.cpp \
        prog_dir.c \
        string-transform.c \
        unicode.c \
        units_scale.c

HEADERS += \
    basic_types.h \
    common.h \
    converter.h \
    getfunction.h \
    loaderdll.h \
    string-transform.h \
    unicode.h \
    units_scale.h \
    utils.h
