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
    QString f_currrDir = QDir().currentPath();
    if(QDir().exists(f_currrDir + "/updaterNew")){
        /*QProcess f_process;
        f_process.start(f_currrDir + "/updaterNew/updater.exe",QStringList());
        if(f_process.waitForStarted()){
            qDebug() << "start";
            f_process.close();*/
            QDir(f_currrDir + "/updater").removeRecursively();
            QDir().rename(f_currrDir + "/updaterNew",f_currrDir + "/updater");
        //}
    }
    /*QDate date(2021,04,1);

    if(QDate::currentDate() >= date){
        QMessageBox::warning(nullptr,"Предкпреждение!", "Закончился пробный период!\n Обратитесь к разработчикам");
        return 0;
    }*/

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
