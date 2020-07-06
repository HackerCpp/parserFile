#include "basesettingswindow.h"
#include <QDebug>

BaseSettingsWindow::BaseSettingsWindow(QWidget* parent)
    : QWidget(parent)
{
    m_scroll = new QScrollArea;
    m_scroll->setWidgetResizable(true);
    m_mainLayout = new QVBoxLayout;
    m_btnLayout = new QHBoxLayout;
    m_btnOk = new QPushButton("OK");
    m_btnCansel = new QPushButton("CANCEL");
    m_btnApply = new QPushButton("APPLY");
    m_btnLayout->addStretch(100);
    m_btnLayout->addWidget(m_btnOk);
    m_btnLayout->addWidget(m_btnApply);
    m_btnLayout->addWidget(m_btnCansel);

    m_mainLayout->addWidget(m_scroll);
    m_mainLayout->addLayout(m_btnLayout);
    this->setLayout(m_mainLayout);
    setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    setMinimumSize(500,500);
    connect(m_btnCansel,&QPushButton::pressed,this,&BaseSettingsWindow::cansel);
    connect(m_btnApply,&QPushButton::pressed,this,&BaseSettingsWindow::apply);
    connect(m_btnOk,&QPushButton::pressed,this,&BaseSettingsWindow::ok);
    setWindowFlags(Qt::WindowStaysOnTopHint);
    setAttribute(Qt::WA_DeleteOnClose);
}

void BaseSettingsWindow::cansel(){
    close();
}

void BaseSettingsWindow::ok(){
    apply();
    cansel();
}

void BaseSettingsWindow::apply(){
    emit changeSettings();
}



BaseSettingsWindow::~BaseSettingsWindow(){
    if(m_btnOk){delete m_btnOk;m_btnOk = nullptr;}
    if(m_btnApply){delete m_btnApply;m_btnApply = nullptr;}
    if(m_btnCansel){delete m_btnCansel;m_btnCansel = nullptr;}
    if(m_btnLayout){delete m_btnLayout;m_btnLayout = nullptr;}
    if(m_scroll){delete m_scroll;m_scroll = nullptr;}
    if(m_mainLayout){delete m_mainLayout;m_mainLayout = nullptr;}
}
