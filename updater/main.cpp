#include "mainwindow.h"

#include <QApplication>
#include "loader.h"
#include "unpacker.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //Loader *f_loader = new Loader();
    //f_loader->getData("http://sarlift.ru//geology_0.0.1.zip");
    Unpacker::unpack("E:/Project/ParserFile/parserFile/updater/build/debug/modules/geology_0.0.1.zip","../unzip");
    MainWindow w;
    w.show();
    return a.exec();
}
