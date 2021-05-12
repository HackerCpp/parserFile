#include "selectingmodepanel.h"
#include <QPushButton>
#include <QDebug>

SelectingModePanel::SelectingModePanel(QWidget* parent)
    :QWidget(parent)
{
    m_btns.addButton(new QPushButton(tr("mouse"),this),BTN_MOUSE);
    m_btns.addButton(new QPushButton(tr("add Label"),this),BTN_LABEL);
    //m_btns.addButton(new QPushButton(tr("shift curve"),this),BTN_SHIFT);

    foreach(auto btn,m_btns.buttons()){
        btn->setCheckable(true);
        m_hMainLayout.addWidget(btn);
    }
    m_hMainLayout.addStretch(1000);
    m_hMainLayout.setMargin(0);


    this->setLayout(&m_hMainLayout);
    connect(&m_btns,&QButtonGroup::idToggled,this,&SelectingModePanel::btnToggled);
}




void SelectingModePanel::btnToggled(int id,bool isActive){
    if(!isActive || id >= BTN_MAX)
        return;
    emit changeMode(id);
}
