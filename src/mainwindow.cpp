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
    applyStyle();
    this->tabWid->setTabsClosable(true);
    connect(this->tabWid, SIGNAL(tabCloseRequested(int)), this, SLOT(closeTab(int)));
    connect(this->menu, SIGNAL(applyStyle()), this, SLOT(applyStyle()));
    QPropertyAnimation *animation = new QPropertyAnimation(this, "geometry");
     animation->setDuration(1000);
     animation->setStartValue(QRect(0, 0, 0, 0));
     animation->setEndValue(QRect(100, 100, 800, 800));
     animation->start();
    menu->installEventFilter(this);
}
bool MainWindow::eventFilter(QObject *o, QEvent *e){
    if(o == this->menu){
        if(e->type() == QEvent::Enter){
            this->menu->showRight();
            return true;
        }
        if(e->type() == QEvent::Leave){
            this->menu->hideLeft();
            return true;
        }

    }

    return false;
}
void MainWindow::applyStyle(){
    QFile File("debug\\css\\style.css");
    File.open(QFile::ReadOnly);
    QString StyleSheet = QLatin1String(File.readAll());
    qApp->setStyleSheet(StyleSheet);
}
MainWindow::~MainWindow(){
    delete this->menu;
    this->menu = nullptr;
    delete this->tabWid;
    this->tabWid = nullptr;

}
void MainWindow::saveFile(){
   Tab38k * tab = dynamic_cast<Tab38k *>(this->tabWid->currentWidget());
   if(tab)
       tab->saveFile();
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
    this->tabWid->setCurrentWidget(w);
    QPropertyAnimation *animation = new QPropertyAnimation(w, "geometry");
     animation->setDuration(1000);
     animation->setStartValue(QRect(0, 0, 0, 0));
     animation->setEndValue(QRect(0, 0, tabWid->width()+30, tabWid->height()-30));
     animation->start();
}


void MainWindow::closeTab(int index){
    QPropertyAnimation *animation = new QPropertyAnimation(this->tabWid->widget(index), "geometry");
     animation->setDuration(1000);
     animation->setStartValue(QRect(0, 0, this->tabWid->widget(index)->width(), this->tabWid->widget(index)->height()));
     animation->setEndValue(QRect(0, 0, 0, 0));
     animation->start();
     QTime time;
     time.start();
     for(;time.elapsed() < 800;)
        qApp->processEvents();
    this->tabWid->widget(index)->deleteLater();
    this->tabWid->removeTab(index);
}


