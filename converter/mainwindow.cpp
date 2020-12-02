#include "mainwindow.h"
#include <QApplication>
#include <QDebug>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    //m_gtkThread = new GtkThread();
    m_horizontalSplitter = new QSplitter(Qt::Horizontal);
    m_fileDialog = new QFileDialog(this);
    m_converter = new Converter();

    m_horizontalSplitter->addWidget(m_converter);
    m_horizontalSplitter->addWidget(m_fileDialog);
    setCentralWidget(m_horizontalSplitter);
    connect(qApp, &QApplication::aboutToQuit,this, &MainWindow::quit);
    connect(m_fileDialog,&QFileDialog::currentChanged,this,&MainWindow::changeFilePath);
    connect(m_fileDialog,&QFileDialog::rejected,this,&MainWindow::fileDialogNoClose);
    connect(m_fileDialog,&QFileDialog::accepted,this,&MainWindow::fileDialogNoClose);
    connect(m_fileDialog,&QFileDialog::finished,this,&MainWindow::fileDialogNoClose);
}

MainWindow::~MainWindow(){
    //if(m_gtkThread){delete m_gtkThread; m_gtkThread = nullptr;}
}


void MainWindow::quit(){
    qDebug() << "quit";
}

void MainWindow::changeFilePath(const QString path){
    m_converter->setFilePath(path);

}

void MainWindow::fileDialogNoClose(){
    m_fileDialog->show();
}
