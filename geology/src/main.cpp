#include "mainwindow.h"

#include <QApplication>
#include <QDir>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    QFile file(":/css/darkVC.css");
    if(file.isOpen()){
        qDebug() << "file style.css open";
    }
    if(!file.exists()){
        qDebug() << "file " + file.fileName() + " style.css not found";
    }
    if(file.open(QFile::ReadOnly)){
        QString StyleSheet = QLatin1String(file.readAll());
        qApp->setStyleSheet(StyleSheet);
    }
    else {
        qDebug() << "file style.css not open;";
    }
    file.close();
    qputenv("PYTHONPATH",QString(QDir().absolutePath() + "/python3/Lib").toLatin1());
    w.show();
    /*QString f_path = QDir().absolutePath() + "/dynlib.dll";
    QLibrary  lib(f_path);
    lib.load();
    qDebug() << lib.isLoaded() << f_path;
    typedef QString (*Fct) (const QString);
    Fct fct = (Fct)(lib.resolve("str"));
    if(fct)
        qDebug() << fct("uutftfyfyt");*/

    return a.exec();
}
