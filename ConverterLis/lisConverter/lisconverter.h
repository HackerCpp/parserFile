#ifndef LISCONVERTER_H
#define LISCONVERTER_H

#include "lisConverter_global.h"
#include <gtk/gtk.h>

extern "C"{
#include "lis_export.h"
#include "lis.h"
#include "getfunction.h"
}

class LISCONVERTER_EXPORT LisConverter
{
public:
    LisConverter();
};

extern "C"{

    int LISCONVERTER_EXPORT f(){
        gtk_init(NULL, NULL);
        //GtkWidget *window;
        //window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
        //gtk_window_set_title(GTK_WINDOW(window), "Введение в GTK");
        //gtk_container_set_border_width (GTK_CONTAINER(window), 50);
        //gtk_widget_show(window);
        GetFunction f_function = (GetFunction) &get_function;
        init(f_function);
        exportGFMToLis((char8 *)"D:/2020_04_28_16-22-39(МБ+ШМ+ШМ+РУ+Р04 на полу).gfm");
        //g_signal_connect ((gpointer) window, "destroy", G_CALLBACK(gtk_main_quit),NULL);
        gtk_main();
    }
}

#endif // LISCONVERTER_H
