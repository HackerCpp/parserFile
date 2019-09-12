#include "men.h"
#include <QFile>
#include <QToolButton>
#include <QStyleOptionSlider>



men::men(QWidget *parent) : QWidget(parent){

    slyderColor = new QSlider(Qt::Horizontal);
    slyderColor->setObjectName("sliderColor");
    slyderThickness = new QSlider(Qt::Horizontal);
    slydersLayout = new QHBoxLayout();
    slydersLayout->addWidget(slyderColor);
    slydersLayout->addSpacing(50);
    slydersLayout->addWidget(slyderThickness);




    up = new QWidget();
    down= new QWidget();
    down->setFixedSize(400,40);
    down->setLayout(slydersLayout);

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
    leftBtnsWidg->setFixedSize(400,40);

    rBtnW->setFixedSize(55,40);
    rBtnW->setAttribute(Qt::WA_TranslucentBackground, true );
    this->setLayout(vBoxLayout);
    btnEnter->setFixedSize(40,40);
    btnMenu->setFixedSize(15,40);

    hBoxLayout->addWidget(leftBtnsWidg);
    hBoxLayout->addStretch(100);
    hBoxLayout->addWidget(rBtnW);
    up->setAttribute( Qt::WA_TranslucentBackground, true );
    up->setLayout(hBoxLayout);
    up->setFixedSize(500,40);
    vBoxLayout->setMargin(0);
    vBoxLayout->addWidget(up);
    vBoxLayout->addWidget(down);


    setAttribute( Qt::WA_TranslucentBackground, true );
    setFixedSize(500,80);
    //this->down->hide();


}

void men::sl(){

}
