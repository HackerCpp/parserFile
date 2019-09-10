#include "men.h"
#include <QFile>
#include <QToolButton>



men::men(QWidget *parent) : QWidget(parent){
    QFile File("debug\\m.css");
    File.open(QFile::ReadOnly);
    QString StyleSheet = QLatin1String(File.readAll());
    this->setStyleSheet(StyleSheet);

    up = new QWidget();
    down= new QWidget();
    this->setWindowFlags(Qt::CustomizeWindowHint | Qt::FramelessWindowHint);
    vBoxLayout = new QVBoxLayout;
    hBoxLayout = new QHBoxLayout;
    hBoxLayout->setContentsMargins(0,0,0,0);

    leftBtnsWidg = new QWidget();
    leftBtnsLayuot = new QHBoxLayout();
    leftBtnsLayuot->setMargin(0);
    leftBtnsWidg->setLayout(leftBtnsLayuot);

    rBtnW = new QWidget();
    rBtnL = new QHBoxLayout();
    rBtnL->setMargin(0);
    btnMenu = new QPushButton();
    btnEnter = new QPushButton();

    rBtnW->setLayout(rBtnL);
    rBtnL->addWidget(btnEnter);
    rBtnL->addWidget(btnMenu);

    leftWidg = new QWidget();
    leftWidg->setFixedSize(15,40);
    leftLayout = new QVBoxLayout();
    leftLayout->setMargin(0);
    leftBtn = new QPushButton();
    leftBtn->setFixedSize(15,15);
    leftWidg->setLayout(leftLayout);
    leftLayout->addWidget(new QWidget());
    leftLayout->addWidget(leftBtn);

    this->toolBar = new QToolBar();
    toolBar->addWidget(leftWidg);
    this->toolBar->addSeparator();
    for(int i = 0; i < 5; i++){
        this->btn[i] = new QPushButton;
        this->toolBar->addWidget(btn[i]);
        btn[i]->setCheckable(true);
        btn[i]->setFixedSize(38,38);
        this->toolBar->addSeparator();
    }
    this->toolBar->setFixedHeight(40);
    leftBtnsLayuot->addWidget(toolBar);
    leftBtnsWidg->setFixedHeight(40);

    rBtnW->setFixedSize(55,40);
    rBtnW->setAttribute(Qt::WA_TranslucentBackground, true );
    this->setLayout(vBoxLayout);
    btnEnter->setFixedSize(40,40);
    btnMenu->setFixedSize(15,40);

    hBoxLayout->addWidget(leftBtnsWidg);
    hBoxLayout->addWidget(rBtnW);
    up->setAttribute( Qt::WA_TranslucentBackground, true );
    up->setLayout(hBoxLayout);
    up->setFixedSize(500,40);
    vBoxLayout->setMargin(0);
    vBoxLayout->addWidget(up);
    vBoxLayout->addWidget(down);


    setAttribute( Qt::WA_TranslucentBackground, true );
    setFixedSize(500,100);



}

void men::sl(){

}
