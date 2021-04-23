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
    //Unpacker::unpack(QDir().currentPath() + "/tr.zip", QDir().currentPath(),false);
    if(argc == 1){
       f_mainWidget = new MainWindow();
    }
    else if(argc == 2){
        f_mainWidget = new UpdateWindow(argv[1],"./");
    }
    else if(argc == 3){
        f_mainWidget = new UpdateWindow(argv[1],argv[2]);
    }
    else{
        f_mainWidget = new UpdateWindow(argv[1],argv[2],argv[3]);
    }
    //f_mainWidget = new UpdateWindow("http://www.gfm.ru/kedr_files/GMLog05/GMLog05_loader.xml","debug");
    f_mainWidget->show();

    return a.exec();
}
