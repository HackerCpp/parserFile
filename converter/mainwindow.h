#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QThread>
#include <QHBoxLayout>
#include <QSplitter>
#include <QFileDialog>
#include "converter.h"

class GtkThread;
class MainWindow : public QMainWindow
{
    Q_OBJECT
    //GtkThread *m_gtkThread;
    QSplitter *m_horizontalSplitter;
    QFileDialog *m_fileDialog;
    Converter *m_converter;
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


public slots:
    void quit();
    void changeFilePath(const QString path);
    void fileDialogNoClose();

};

#endif // MAINWINDOW_H
