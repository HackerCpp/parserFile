#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <gtk.h>
#include <QMainWindow>
#include <QThread>


class MainWindow : public QMainWindow
{
    Q_OBJECT
    QThread *m_gtkThread;
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


public slots:
    void quit();

};

#endif // MAINWINDOW_H
