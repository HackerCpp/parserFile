#include "tabgroupsettings.h"

TabGroupSettings::TabGroupSettings(QWidget *parent) : QWidget(parent){
    m_curveSettings = new QList<TabCurveSettings*>;
    m_mainLayout = new QVBoxLayout;
    this->setLayout(m_mainLayout);
    setWindowFlags(Qt::WindowStaysOnTopHint);
}

void TabGroupSettings::hideL(){
    foreach(auto value,*m_curveSettings){
        if(value){
            m_mainLayout->removeWidget(value);
            delete value;
            value = nullptr;
        }
    }
    m_curveSettings->clear();
    this->hide();
}

void TabGroupSettings::addCurve(CurveBaseItem * curve){
    TabCurveSettings * cs = new TabCurveSettings(curve);
    m_curveSettings->push_back(cs);
    m_mainLayout->addWidget(cs);

}

TabGroupSettings::~TabGroupSettings(){
    foreach(auto value,*m_curveSettings){
        if(value){
            delete value;
            value = nullptr;
        }
    }
    delete m_curveSettings;
    m_curveSettings = nullptr;
}
