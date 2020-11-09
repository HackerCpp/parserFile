#include "mainwindow.h"

#include <QApplication>
#include <QDir>
#include <QMessageBox>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTranslator qtLanguageTranslator;
    QString f_translatePath = QString(QDir().absolutePath() + "/translations/") + QString("QtLanguage_") + QString("ru_RU");
    qtLanguageTranslator.load(f_translatePath);
    qApp->installTranslator(&qtLanguageTranslator);
    QStringList f_entryList = QDir("temporary").entryList();
    foreach(auto file,f_entryList){
        if(file != "\\." && file != "\\..")
            QFile(QDir().currentPath() + "\\temporary\\" + file).remove();
    }
    if(QDir().exists("updaterNew")){
        QProcess f_process;
        QStringList f_arguments;
        f_process.start("updaterNew/updater.exe",f_arguments);
        if(f_process.waitForStarted()){
            f_process.close();
            QDir("updater").removeRecursively();
            QDir().rename("updaterNew","updater");
        }
    }
    MainWindow w;

    QCoreApplication::setOrganizationName("GFM");
    QCoreApplication::setApplicationName("Geology");
    QSettings m_settings("settings.ini",QSettings::IniFormat);
    QString f_styleFile = m_settings.value("styleFile").toString();
    if(f_styleFile == "")
        f_styleFile = ":/css/dark.css";
    QFile file(f_styleFile);
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
