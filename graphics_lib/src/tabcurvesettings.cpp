#include "tabcurvesettings.h"
#include <QColor>

TabCurveSettings::TabCurveSettings(CurveBaseItem* item)
    :m_item(item){

    m_sliderColor = new QSlider(Qt::Horizontal);
    m_sliderColor->setMinimum(0);
    m_sliderColor->setMaximum(360);
    m_sliderColor->setTickInterval(1);



    m_sliderWidthLine = new QSlider(Qt::Horizontal);
    m_sliderWidthLine->setMinimum(1);
    m_sliderWidthLine->setMaximum(8);
    m_sliderWidthLine->setTickInterval(1);


    m_cliderScale = new QSlider(Qt::Horizontal);
    m_cliderScale->setMinimum(1);
    m_cliderScale->setMaximum(1000000);
    m_cliderScale->setTickInterval(1);
    m_cliderScale->setValue(item->scale()*100000);

    m_sliderOffset = new QSlider(Qt::Horizontal);
    m_sliderOffset->setMinimum(0);
    m_sliderOffset->setMaximum(item->limit());
    m_sliderOffset->setTickInterval(1);
    m_sliderOffset->setValue(item->leftShift());

    m_rBtnIsShow = new QRadioButton("Показать");
    m_rBtnIsShow->setChecked(item->isShow());

    m_mainLayout = new QVBoxLayout;
    this->setLayout(m_mainLayout);
    m_mainLayout->addWidget(m_sliderColor);
    m_mainLayout->addWidget(m_sliderWidthLine);
    m_mainLayout->addWidget(m_cliderScale);
    m_mainLayout->addWidget(m_sliderOffset);
    m_mainLayout->addWidget(m_rBtnIsShow);



    connect(m_sliderColor,&QSlider::valueChanged,this,&TabCurveSettings::changeColor);
    connect(m_cliderScale,&QSlider::valueChanged,this,&TabCurveSettings::changeScale);
    connect(m_sliderWidthLine,&QSlider::valueChanged,this,&TabCurveSettings::changeWidth);
    connect(m_sliderOffset,&QSlider::valueChanged,this,&TabCurveSettings::changeLeftShift);
    connect(m_rBtnIsShow,&QRadioButton::toggled,this,&TabCurveSettings::changeShow);

    show();
}
void TabCurveSettings::changeShow(bool show){
    m_item->setShow(show);
    emit m_item->updateL(QPointF(),QPointF(),true);
}
void TabCurveSettings::changeLeftShift(int shift){
    m_item->setLeftShift(shift);
    emit m_item->updateL(QPointF(),QPointF(),true);
}
void TabCurveSettings::changeColor(int hsl){
    QColor color;
    color.setHsl(hsl,128,128,255);
    m_item->getPen()->setColor(color);
    emit m_item->updateL(QPointF(),QPointF(),true);
}
void TabCurveSettings::changeScale(int scale){
    m_item->setScale(static_cast<qreal>(scale)/100000);
    emit m_item->updateL(QPointF(),QPointF(),true);
}
void TabCurveSettings::changeWidth(int width){
    m_item->setWidthLine(width);
}
TabCurveSettings::~TabCurveSettings(){
    if(m_sliderColor){
        delete m_sliderColor;
        m_sliderColor = nullptr;
    }
    if(m_sliderWidthLine){
        delete m_sliderWidthLine;
        m_sliderWidthLine = nullptr;
    }
    if(m_cliderScale){
        delete m_cliderScale;
        m_cliderScale = nullptr;
    }
    if(m_sliderOffset){
        delete m_sliderOffset;
        m_sliderOffset = nullptr;
    }
}
