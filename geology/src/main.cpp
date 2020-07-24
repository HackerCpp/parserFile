#include "mainwindow.h"

#include <QApplication>
#include <QDir>
#include <QMessageBox>
#include "onewavewidget.h"
#include "pythoneditor.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTranslator qtLanguageTranslator;
    QString f_translatePath = QString(QDir().absolutePath() + "/translations/") + QString("QtLanguage_") + QString("ru_RU");
    qtLanguageTranslator.load(f_translatePath);
    qApp->installTranslator(&qtLanguageTranslator);
    MainWindow w;
    QCoreApplication::setOrganizationName("GFM");
    QCoreApplication::setApplicationName("Geology");
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

    w.setMinimumSize(600,600);
    w.show();
    w.setMinimumSize(0,0);

    return a.exec();

}
