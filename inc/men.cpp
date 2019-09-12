#include "men.h"
#include <QFile>
#include <QToolButton>
#include <QStyleOptionSlider>
#include <QApplication>
#include <QRect>
#include <QScreen>
#include <QPropertyAnimation>
#include <QDebug>
#include <QBitmap>
#include <QTime>


void Wind::setObgectName(){
    headerBtn->setObjectName("qwit");
}

Wind::Wind(){
    trayIcon = new QSystemTrayIcon(QIcon("icon\\1.png"));
    trayIcon->show();
    QRect size = QApplication::screens().at(0)->geometry();
    this->setWindowIcon(QIcon("icon\\1.png"));
    this->setWindowTitle("title");
    this->setWindowFlags(Qt::SplashScreen | Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint);
    for(int i = 0; i < 6; i++){
        pushBtn[i] = new QPushButton;
        pushBtn[i]->setFixedSize(size.width()/24,size.height()/18);
    }
    headerLayout = new QHBoxLayout;
    headerLabelIcon = new QLabel();
    headerLabelIcon->setPixmap(QPixmap("icon\\1.png").scaled(30,30));
    headerLabelText = new QLabel("Title");
    headerBtn = new QPushButton;
    headerBtn->setFixedSize(size.width()/90,size.height()/70);
    headerBtn->setIcon(QPixmap("icon\\del.png"));
    headerLayout->addWidget(headerLabelIcon);
    headerLayout->addWidget(headerLabelText);
    headerLayout->addWidget(headerBtn);

    mainVBoxLayout = new QVBoxLayout;
    gridLayoutUp = new QGridLayout;
    hBoxLayoutAver = new QHBoxLayout;
    hBoxLayoutDown = new QHBoxLayout;
    groupBoxUp = new QGroupBox;
    groupBoxAver = new QGroupBox;
    downWidg = new QWidget;
    labelleft = new QLabel("<a href='https://docs.python'>Exit</a>");
    labelRight = new QLabel("<a href='https://docs.python'>Out</a>");
    this->setLayout(mainVBoxLayout);
    mainVBoxLayout->addLayout(headerLayout);
    mainVBoxLayout->addWidget(groupBoxUp);
    mainVBoxLayout->addWidget(groupBoxAver);
    mainVBoxLayout->addWidget(downWidg);
    groupBoxUp->setLayout(gridLayoutUp);
    groupBoxAver->setLayout(hBoxLayoutAver);
    downWidg->setLayout(hBoxLayoutDown);
    gridLayoutUp->addWidget(pushBtn[0],0,1);
    gridLayoutUp->addWidget(pushBtn[1],0,2);
    gridLayoutUp->addWidget(pushBtn[2],1,1);
    gridLayoutUp->addWidget(pushBtn[3],1,2);
    hBoxLayoutAver->addWidget(pushBtn[4]);
    hBoxLayoutAver->addWidget(pushBtn[5]);
    hBoxLayoutDown->addWidget(labelleft);
    hBoxLayoutDown->addWidget(labelRight);
    labelleft->setOpenExternalLinks(true);
    labelRight->setOpenExternalLinks(true);
    //gridLayoutUp->setMargin(0);
    //hBoxLayoutAver->setMargin(0);
    mainVBoxLayout->setMargin(4);
    this->setFixedSize(size.width()/10,size.height()/3 - size.height()/18);
    this->move(size.width()-(size.width()/7) ,size.height() - (size.height()/3));
    setObgectName();
    connect(headerBtn, SIGNAL(clicked()), this, SLOT(hideWin()));
    connect(trayIcon, SIGNAL(messageClicked()), this, SLOT(showWin()));
    connect(trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(showWin()));
}
void Wind::hideWin(){
   /* QPropertyAnimation *animation = new QPropertyAnimation(this, "geometry");
    animation->setDuration(1000);
    animation->setStartValue(QRect(this->pos().x(), this->pos().y(), this->width(), this->width()));
    animation->setEndValue(QRect(this->pos().x(), this->pos().y() + this->height(), this->width(), this->height()));
    animation->start();
    QTime time;
    time.start();
    for(;time.elapsed() < 800;)
       qApp->processEvents();*/
    this->hide();
}
void Wind::showWin(){
    if(this->isVisible())
        return;
    QPropertyAnimation *animation = new QPropertyAnimation(this, "geometry");
    animation->setDuration(500);
    animation->setStartValue(QRect(this->pos().x(), this->pos().y() + this->height(), this->width(), this->width()));
    animation->setEndValue(QRect(this->pos().x(), this->pos().y(), this->width(), this->height()));
    animation->start();
    this->show();
}

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
    showHideDown();
}

void men::showHideDown(){
    QPropertyAnimation *animation = new QPropertyAnimation(down, "geometry");
    if(showDown){
        animation->setDuration(1000);
        animation->setStartValue(QRect(0, 40, down->width(), down->width()));
        animation->setEndValue(QRect(0, 10, down->width(), down->height()));
        animation->start();
        showDown = false;
    }
    else{
        animation->setDuration(1000);
        animation->setStartValue(QRect(0, 10, down->width(), down->height()));
        animation->setEndValue(QRect(0, 40, down->width(), down->width()));
        animation->start();
        showDown = true;
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
