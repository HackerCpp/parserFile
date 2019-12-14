#include "mainvaluescontainer.h"

MainValuesContainer::MainValuesContainer(){
    m_mainValues = new QList<MainValue*>;
}

MainValue *MainValuesContainer::addMainValue(Curve *mainTime,Curve *mainDepth){
    foreach(auto mainValue,*m_mainValues){
        if(mainValue->checkPoint(mainTime,mainDepth))
            return mainValue;
    }
    MainValue * mainValue = new MainValue(mainTime,mainDepth);
    m_mainValues->push_back(mainValue);
    return mainValue;
}
void MainValuesContainer::setMainTime(){
    if(!m_mainValues)
        return;
    foreach(auto mainValue,*m_mainValues){
        mainValue->setMainTime();
    }
}
void MainValuesContainer::setMainDepth(){
    if(!m_mainValues)
        return;
    foreach(auto mainValue,*m_mainValues){
        mainValue->setMainDepth();
    }
}
void MainValuesContainer::setScale(qreal scale){
    if(!m_mainValues)
        return;
    foreach(auto mainValue,*m_mainValues){
        mainValue->setScale(scale);
    }
}
qreal MainValuesContainer::maximum(){
    qreal maximum = std::numeric_limits<qreal>::min();
    foreach(auto mainValue,*m_mainValues){
        maximum = qMax(maximum,mainValue->maximumForScale());
    }
    return maximum;
}
qreal MainValuesContainer::minimum(){
    qreal minimum = std::numeric_limits<qreal>::max();;
    foreach(auto mainValue,*m_mainValues){
        minimum = qMin(minimum,mainValue->minimumForScale());
    }
    return minimum;
}
qreal MainValuesContainer::scale(){
    if(!m_mainValues || m_mainValues->isEmpty())
        return -1;
    m_mainValues->first()->scale();
}

MainValuesContainer::~MainValuesContainer(){

}
