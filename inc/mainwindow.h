#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QVBoxLayout>
#include "inc/menu.h"

class MainWindow : public QWidget{

    Q_OBJECT

    Menu *menu;
    QTabWidget *tabWid;
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
public slots:
    void openFile();
};

#endif // MAINWINDOW_H
