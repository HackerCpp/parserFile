#include "mainwindow.h"

#include <QApplication>
#include "loader.h"
#include "unpacker.h"
#include "updatewindow.h"
#include "infiniteloading.h"
#include <QDir>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QWidget *f_mainWidget;
    //Unpacker::unpack(QDir().currentPath() + "//updater.zip", QDir().currentPath(),false);
    if(argc == 1){
       f_mainWidget = new MainWindow();
    }
    else if(argc == 2){
        QFile f_logs("inf.log");
        f_logs.open(QIODevice::WriteOnly);
        f_logs.write(argv[1]);
        f_logs.close();
        f_mainWidget = new UpdateWindow(argv[1],"./");
    }
    else if(argc >= 3){
        QFile f_logs("inf.log");
        f_logs.open(QIODevice::WriteOnly);
        f_logs.write(argv[1]);
        f_logs.close();
        f_mainWidget = new UpdateWindow(argv[1],argv[2]);
    }
    //f_mainWidget = new UpdateWindow("http://www.gfm.ru/kedr_files/GMLog05/GMLog05_loader.xml","debug");
    f_mainWidget->show();

    return a.exec();
}
