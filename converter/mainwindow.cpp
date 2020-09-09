#include "mainwindow.h"
#include <QApplication>
#include <QDebug>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    m_gtkThread = new QThread();
    m_gtkThread->

    connect(qApp, &QApplication::aboutToQuit,this, &MainWindow::quit);
}

MainWindow::~MainWindow(){

}


void MainWindow::quit(){
    qDebug() << "quit";
    gtk_main_quit();
}

