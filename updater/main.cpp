#include "mainwindow.h"

#include <QApplication>
#include "loader.h"
#include "unpacker.h"
#include "updatewindow.h"
#include "infiniteloading.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QWidget *f_mainWidget;
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
    f_mainWidget->show();
    return a.exec();
}
