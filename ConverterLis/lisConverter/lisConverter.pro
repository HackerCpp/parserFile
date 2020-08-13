CONFIG -= qt

TEMPLATE = lib
DEFINES += LISCONVERTER_LIBRARY

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
INCLUDEPATH+= D:\msys\mingw64\include\gtk-3.0\gtk \
E:\msys2\mingw64\include\gtk-3.0 \
E:\msys2\mingw64\include\glib-2.0 \
E:\msys2\mingw64\lib\glib-2.0\include \
E:\msys2\mingw64\include\pango-1.0 \
E:\msys2\mingw64\include\cairo \
E:\msys2\mingw64\include\gdk-pixbuf-2.0 \
E:\msys2\mingw64\include\atk-1.0 \
C:\Users\Alex\Desktop\cm_GTK_QT\kedr-m76-rev2-master\src\common \
E:\msys2\mingw64\share\gettext \
C:\Users\Alex\Desktop\cm_GTK_QT\kedr-m76-rev2-master\src\
 E:\MyQtProgram\parserGfm\ConverterLis\src\
E:\msys2\mingw64\include\
C:\Qt\Qt5.14.0\5.14.0\mingw73_64\include\libxml2
LIBS += C:\Qt\Qt5.14.0\5.14.0\mingw73_64\bin\libgtk-3-0.dll \
C:\Qt\Qt5.14.0\5.14.0\mingw73_64\bin\libgettextlib-0-19-8-1.dll \
C:\Qt\Qt5.14.0\5.14.0\mingw73_64\bin\libgettextpo-0.dll \
C:\Qt\Qt5.14.0\5.14.0\mingw73_64\bin\libgfortran-4.dll \
C:\Qt\Qt5.14.0\5.14.0\mingw73_64\bin\libgio-2.0-0.dll \
C:\Qt\Qt5.14.0\5.14.0\mingw73_64\bin\libglib-2.0-0.dll \
C:\Qt\Qt5.14.0\5.14.0\mingw73_64\bin\libgobject-2.0-0.dll \
C:\Qt\Qt5.14.0\5.14.0\mingw73_64\bin\libiconv-2.dll \
C:\Qt\Qt5.14.0\5.14.0\mingw73_64\bin\libintl-8.dll \
C:\Qt\Qt5.14.0\5.14.0\mingw73_64\bin\libpango-1.0-0.dll \
C:\Qt\Qt5.14.0\5.14.0\mingw73_64\bin\libpng16-16.dll \
C:\Qt\Qt5.14.0\5.14.0\mingw73_64\bin\libxml2-2.dll

SOURCES += \
    lisconverter.cpp\
        E:/MyQtProgram/parserGfm/ConverterLis/src/edit_mnemonic.c \
        E:/MyQtProgram/parserGfm/ConverterLis/src/gfmfile/compress.c \
        E:/MyQtProgram/parserGfm/ConverterLis/src/gfmfile/datablock_exp.c \
        E:/MyQtProgram/parserGfm/ConverterLis/src/gfmfile/param.c \
        E:/MyQtProgram/parserGfm/ConverterLis/src/gfmfile/parampos.c \
        E:/MyQtProgram/parserGfm/ConverterLis/src/gfmfile/unicode.c \
        E:/MyQtProgram/parserGfm/ConverterLis/src/lis_export.c \
        E:/MyQtProgram/parserGfm/ConverterLis/src/lis.c \
        E:/MyQtProgram/parserGfm/ConverterLis/src/lis_data.c \
        E:/MyQtProgram/parserGfm/ConverterLis/src/params_xml.c \
        E:/MyQtProgram/parserGfm/ConverterLis/src/program.c \
        E:/MyQtProgram/parserGfm/ConverterLis/src/save_export_curves.c \
        E:/MyQtProgram/parserGfm/ConverterLis/src/top_bottom.c \
        E:/MyQtProgram/parserGfm/ConverterLis/src/string-transform.c \
        E:/MyQtProgram/parserGfm/ConverterLis/src/units_scale.c \
        E:/MyQtProgram/parserGfm/ConverterLis/src/getfunction.c




HEADERS += \
    lisConverter_global.h \
    lisconverter.h \
    E:/MyQtProgram/parserGfm/ConverterLis/src/basic_types.h \
    E:/MyQtProgram/parserGfm/ConverterLis/src/common.h \
    E:/MyQtProgram/parserGfm/ConverterLis/src/compress.h \
    E:/MyQtProgram/parserGfm/ConverterLis/src/datablock.h \
    E:/MyQtProgram/parserGfm/ConverterLis/src/edit_mnemonic.h \
    E:/MyQtProgram/parserGfm/ConverterLis/src/gettext.h \
    E:/MyQtProgram/parserGfm/ConverterLis/src/gfmfile/data_types.h \
    E:/MyQtProgram/parserGfm/ConverterLis/src/gfmfile/parampos.h \
    E:/MyQtProgram/parserGfm/ConverterLis/src/lis-export_c_txt \
    E:/MyQtProgram/parserGfm/ConverterLis/src/lis-import.c__ \
    E:/MyQtProgram/parserGfm/ConverterLis/src/lis.h \
    E:/MyQtProgram/parserGfm/ConverterLis/src/lis_data.h \
    E:/MyQtProgram/parserGfm/ConverterLis/src/params_xml.h \
    E:/MyQtProgram/parserGfm/ConverterLis/src/program.h \
    E:/MyQtProgram/parserGfm/ConverterLis/src/program_c \
    E:/MyQtProgram/parserGfm/ConverterLis/src/program_h \
    E:/MyQtProgram/parserGfm/ConverterLis/src/save_export_curves.h \
    E:/MyQtProgram/parserGfm/ConverterLis/src/top_bottom.h \
    E:/MyQtProgram/parserGfm/ConverterLis/src/unicode.h \
    E:/MyQtProgram/parserGfm/ConverterLis/src/version.rc \
    E:/MyQtProgram/parserGfm/ConverterLis/src/lis_export.h \
    E:/MyQtProgram/parserGfm/ConverterLis/src/string-transform.h \
    E:/MyQtProgram/parserGfm/ConverterLis/src/units_scale.h \
    E:/MyQtProgram/parserGfm/ConverterLis/src/getfunction.h




# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc
