#include "men.h"
#include <QFile>
#include <QToolButton>
#include <QStyleOptionSlider>
#include <QApplication>
#include <QRect>
#include <QScreen>
#include <QPropertyAnimation>
#include <QDebug>

void men::setObgectName(){
   slyderColor->setObjectName("sliderColor");
   up->setObjectName("UpWidget");
   down->setObjectName("DownWidget");
   leftBtnsWidg->setObjectName("LeftBtns");
   rBtnW->setObjectName("RightBtns");
}

men::men(QWidget *parent) : QWidget(parent){
    QRect size = QApplication::screens().at(0)->geometry();
    slyderColor = new QSlider(Qt::Horizontal);
    slyderThickness = new QSlider(Qt::Horizontal);
    slydersLayout = new QHBoxLayout();
    slydersLayout->addWidget(slyderColor);
    slydersLayout->addSpacing(50);
    slydersLayout->addWidget(slyderThickness);

    up = new QWidget();
    down= new QWidget();
    down->setFixedSize(size.width()/4,size.height()/26);
    down->setLayout(slydersLayout);

    this->setWindowFlags(Qt::CustomizeWindowHint | Qt::FramelessWindowHint);
    vBoxLayout = new QGridLayout;
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
    leftWidg->setFixedSize(size.width()/80,size.height()/26);
    leftLayout = new QVBoxLayout();
    leftLayout->setMargin(0);
    leftBtn = new QPushButton();
    leftBtn->setFixedSize(size.width()/80,size.width()/80);
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
        btn[i]->setFixedSize(size.width()/40,size.height()/28);
        this->toolBar->addSeparator();
    }
    this->toolBar->setFixedHeight(size.height()/26);
    leftBtnsLayuot->addWidget(toolBar);
    leftBtnsWidg->setFixedSize(size.width()/4,size.height()/26);

    rBtnW->setFixedSize(size.width()/30,size.height()/26);
    this->setLayout(vBoxLayout);
    btnEnter->setFixedSize(size.width()/40,size.height()/26);
    btnMenu->setFixedSize(size.width()/80,size.height()/26);

    hBoxLayout->addWidget(leftBtnsWidg);
    hBoxLayout->addStretch(50);
    hBoxLayout->addWidget(rBtnW);
    up->setLayout(hBoxLayout);
    up->setFixedSize(size.width()/3,size.height()/24);
    vBoxLayout->setMargin(0);
    vBoxLayout->addWidget(down,1,0);
    vBoxLayout->addWidget(up,0,0);

    setAttribute( Qt::WA_TranslucentBackground, true );
    setFixedSize(size.width()/3,size.height()/12);

    setObgectName();
    connect(this->leftBtn, SIGNAL(clicked()), this, SLOT(showHideDown()));
    connect(this->btn[0], SIGNAL(clicked()), this, SLOT(checkBtns0()));
    connect(this->btn[1], SIGNAL(clicked()), this, SLOT(checkBtns1()));
    connect(this->btn[2], SIGNAL(clicked()), this, SLOT(checkBtns2()));
    connect(this->btn[3], SIGNAL(clicked()), this, SLOT(checkBtns3()));
    connect(this->btn[4], SIGNAL(clicked()), this, SLOT(checkBtns4()));

    showDown = true;
}

void men::showHideDown(){
    QPropertyAnimation *animation = new QPropertyAnimation(down, "geometry");
    if(showDown){
        animation->setDuration(1000);
        animation->setStartValue(QRect(0, 40, down->width(), down->width()));
        animation->setEndValue(QRect(0, 10, down->width(), down->height()));
        animation->start();
        showDown = false;
        //down->hide();
    }
    else{
        animation->setDuration(1000);
        animation->setStartValue(QRect(0, 10, down->width(), down->height()));
        animation->setEndValue(QRect(0, 40, down->width(), down->width()));
        animation->start();
        showDown = true;
        //down->show();
    }
}
void men::checkBtns(int i){
    for(int ind = 0; ind < 5; ind++){
        if(ind != i)
            btn[ind]->setChecked(false);
    }
}
void men::checkBtns0(){
    checkBtns(0);
}
void men::checkBtns1(){
    checkBtns(1);
}
void men::checkBtns2(){
    checkBtns(2);
}
void men::checkBtns3(){
    checkBtns(3);
}
void men::checkBtns4(){
    checkBtns(4);
}
