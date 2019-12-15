#include "tabgeneralsettings.h"

TabGeneralSettings::TabGeneralSettings(){
    setWindowFlags(Qt::Tool|Qt::WindowSystemMenuHint);
    m_mainLayout = new QVBoxLayout;
    m_sliderScale = new QSlider(Qt::Horizontal);
    m_sliderScale->setMinimum(1);
    m_sliderScale->setMaximum(6000);
    m_sliderScale->setTickInterval(1);
    m_mainLayout->addWidget(m_sliderScale);
    this->setLayout(m_mainLayout);
    //this->show();
    connect(m_sliderScale,&QSlider::valueChanged,this,&TabGeneralSettings::changeScale);
    hide();
}
TabGeneralSettings::~TabGeneralSettings(){
    if(m_sliderScale){
        delete m_sliderScale;
        m_sliderScale = nullptr;
    }
    if(m_mainLayout){
        delete m_mainLayout;
        m_mainLayout = nullptr;
    }
}
