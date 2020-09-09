#include <gtk.h>
#include <QDebug>
#include <QApplication>
#include "mainwindow.h"

using namespace Qt;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    gtk_init(NULL, NULL);
    MainWindow w;
    GtkWidget *window;
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "converter");
    gtk_container_set_border_width (GTK_CONTAINER(window), 50);
    gtk_widget_show(window);
    //g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);
    w.show();

    return a.exec();
    //gtk_main();
}
