#include "mainwindow.h"

#include <QApplication>
#include <QDir>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    qputenv("PYTHONPATH",QString(QDir().absolutePath() + "/python3/Lib").toLatin1());
    w.show();
    return a.exec();
}
