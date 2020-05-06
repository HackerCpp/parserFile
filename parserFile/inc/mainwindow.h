#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QVBoxLayout>
#include "inc/menu.h"
#include "inc/filehandler.h"
#include <QVector>

class MainWindow : public QWidget{

    Q_OBJECT

    FileHandler file;
    Menu *menu;
    QTabWidget *tabWid;
public:
    MainWindow(QWidget *parent = nullptr);
    bool eventFilter(QObject *o, QEvent *e);
    ~MainWindow();
public slots:
    void saveCSV();
    void saveGFM();
    void openFile();
    void closeTab(int index);
    void applyStyle();
    void openConsolePython();
};

#endif // MAINWINDOW_H
