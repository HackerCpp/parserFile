#include "inc/mainwindow.h"
#include <QFileDialog>
#include <QTabWidget>
#include <QtWidgets>
#include <QDebug>
#include "inc/tabs/tab38k.h"

MainWindow::MainWindow(QWidget *parent){
    this->setParent(parent);
    tabWid = new QTabWidget();
    menu = new Menu(this);
    QVBoxLayout *verticalLayout = new QVBoxLayout(this);
    QWidget *header = new QWidget();
    QVBoxLayout *verticalLayoutHeader = new QVBoxLayout();
    header->setMinimumHeight(50);
    header->setLayout(verticalLayoutHeader);
    QHBoxLayout *blay = new QHBoxLayout();
    QVBoxLayout *forMenu = new QVBoxLayout();
    forMenu->addWidget(menu);
    forMenu->addStretch(1000);
    blay->addLayout(forMenu);
    blay->addWidget(tabWid);

    verticalLayout->addWidget(header);
    verticalLayout->addLayout(blay);
    this->setLayout(verticalLayout);
    qApp->setStyleSheet("QWidget {background-color:#B0E0E6;position:absolute;left:20px;}"
                        "QTreeView:header {background-color:green;position:absolute;left:20px;}");
    this->tabWid->setTabsClosable(true);
    this->setMinimumSize(500,500);
    connect(this->tabWid, SIGNAL(tabCloseRequested(int)), this, SLOT(closeTab(int)));
}

MainWindow::~MainWindow(){
    delete this->menu;
    this->menu = nullptr;
    delete this->tabWid;
    this->tabWid = nullptr;

}

void MainWindow::openFile(){
    QFileDialog fileDialog;
    QString filePath = fileDialog.getOpenFileName(this, tr("Open File"),"C:/",tr("*.tlm"));
    if(filePath == "")
        return;
    QWidget *w = file.getWidget(filePath);
    if(!w){
        qDebug() << "FILE nOT";
        return;
    }
    this->tabWid->addTab(w,filePath);
}


void MainWindow::closeTab(int index){
    this->tabWid->widget(index)->deleteLater();
    this->tabWid->removeTab(index);
}


