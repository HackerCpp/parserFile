#include "mainvalue.h"

MainValue::MainValue(Curve *mainTime,Curve *mainDepth):
    m_mainTime(mainTime),m_mainDepth(mainDepth){
    m_isMainTime = false;
    m_mainValue = m_mainDepth;
    m_scaleForTime = m_scaleForDepth = m_curentScale = 1;
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
    return maximumTime() * m_scaleForTime;
}
qreal MainValue::minimumTimeForScale(){
    return minimumTime() * m_scaleForTime;
}
qreal MainValue::maximumDepthForScale(){
    return maximumDepth() * m_scaleForDepth;
}
qreal MainValue::minimumDepthForScale(){
    return minimumDepth() * m_scaleForDepth;
}
qreal MainValue::minimumForScale(){
    return m_isMainTime?minimumTimeForScale():minimumDepthForScale();
}
qreal MainValue::maximumForScale(){
    return m_isMainTime?maximumTimeForScale():maximumDepthForScale();
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
    return m_isMainTime?m_scaleForTime:m_scaleForDepth;
}



