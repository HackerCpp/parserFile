#include "mainwindow.h"

#include <QApplication>
#include <QDir>
#include <QMessageBox>
#include "onewavewidget.h"
#include "pythoneditor.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    try{

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
    qputenv("PYTHONPATH",QString(QDir().absolutePath() + "/python3/Lib").toLatin1());
    w.setMinimumSize(600,600);
    w.show();
    w.setMinimumSize(0,0);
    //PythonEditor *f_editor = new PythonEditor(nullptr,&w);
    //f_editor->show();
    return a.exec();

        // Здесь мы пишем стейтменты, которые будут генерировать следующее исключение
        //throw -1; // типичный стейтмент throw
    }
    catch (int a)
    {
        // Любые исключения типа int, сгенерированные в блоке try выше, обрабатываются здесь
        std::cerr << "We caught an int exception with value: " << a << '\n';
    }
    catch (double) // мы не указываем имя переменной, так как в этом нет надобности (мы её нигде в блоке не используем)
    {
        // Любые исключения типа double, сгенерированные в блоке try выше, обрабатываются здесь
        std::cerr << "We caught an exception of type double" << '\n';
    }
    catch (const std::string &str) // ловим исключения по константной ссылке
    {
        // Любые исключения типа std::string, сгенерированные внутри блока try выше, обрабатываются здесь
        std::cerr << "We caught an exception of type std::string" << '\n';
    }

}
