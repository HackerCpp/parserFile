#include "mainvalue.h"

MainValue::MainValue(Curve *mainTime,Curve *mainDepth):
    m_mainTime(mainTime),m_mainDepth(mainDepth){
    m_isMainTime = false;
    m_mainValue = m_mainDepth;
    m_scaleForTime = m_scaleForDepth = m_curentScale = 1;
    m_curentIndexBegin = size();
}

void MainValue::findIndexBegin(int yTop){
    if(minimumForScale() > yTop  + 2000 || maximumForScale() < yTop - 1000){
        m_curentIndexBegin = size();
        return;
    }
    for(uint i = 0; i < size(); ++i){
       if(data(i) > yTop - 1000 && data(i) < yTop + 2000){
           m_curentIndexBegin = i;// > 2?i - 2 : 0;
           return;
       }
    }
}

bool MainValue::checkPoint(Curve *time,Curve *depth){
    return (time == m_mainTime && depth == m_mainDepth);
}
qreal MainValue::maximumTime(){
    return m_mainTime->maximum();
}
qreal MainValue::minimumTime(){
    return m_mainTime->minimum();
}
qreal MainValue::maximumDepth(){
    return m_mainDepth->maximum();
}
qreal MainValue::minimumDepth(){
    return m_mainDepth->minimum();
}
qreal MainValue::maximumTimeForScale(){
    return maximumTime() * m_curentScale;
}
qreal MainValue::minimumTimeForScale(){
    return minimumTime() * m_curentScale;
}
qreal MainValue::maximumDepthForScale(){
    return maximumDepth() * m_curentScale;
}
qreal MainValue::minimumDepthForScale(){
    return minimumDepth() * m_curentScale;
}
qreal MainValue::minimumForScale(){
    return m_mainValue->minimum()*m_curentScale;
}
qreal MainValue::maximumForScale(){
    return m_mainValue->maximum()*m_curentScale;
}
void MainValue::setMainTime(){
    m_isMainTime = true;
    m_mainValue = m_mainTime;
    m_scaleForDepth = m_curentScale;
    m_curentScale = m_scaleForTime;
}
void MainValue::setMainDepth(){
    m_isMainTime = false;
    m_mainValue = m_mainDepth;
    m_scaleForTime = m_curentScale;
    m_curentScale = m_scaleForDepth;
}
bool MainValue::isMainTime(){
    return m_isMainTime;
}
uint MainValue::size(){
    return m_mainValue->getSize();
}
void MainValue::setScale(qreal scale){
    m_curentScale = scale;
}
qreal MainValue::data(int index){
    return m_mainValue->data(index) * m_curentScale;
}

qreal MainValue::operator[](int index){
    return m_mainValue->data(index);
}

qreal MainValue::scale(){
    return m_curentScale;
}



