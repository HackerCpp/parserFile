#include "acurve.h"
#include <QDebug>



ACurve::ACurve(){
    m_time = m_depth = m_userValue = nullptr;
    m_recordPoint = qQNaN();
    // if m_scale = 1 and m_offset = 0 use ACurve::rawData
    // else use ACurve::recalculatedData
    m_scale = 1;
    m_offset = 0;
    dataCountingFunction = &ACurve::rawData;
}

ACurve::~ACurve(){

}

ICurve *ACurve::time(){
   return m_time;
}

ICurve *ACurve::depth(){
    return m_depth;
}

ICurve *ACurve::userBaseValue(){
    return m_userValue;
}

bool ACurve::setTime(ICurve *time){
    m_time = time;
    return true;
}

bool ACurve::setDepth(ICurve *depth){
    m_depth = depth;
    return true;
}

bool ACurve::setUserBaseValue(ICurve *userBaseValue){
    m_userValue = userBaseValue;
    return true;
}

QString ACurve :: dataType()
{
    return m_dataType;
}

uint ACurve::size(){
    return 0;
}

qreal ACurve::maximum(){
    return (this->*dataCountingFunction)(maxData());
}

qreal ACurve::minimum(){
    return (this->*dataCountingFunction)(minData());
}

Desc *ACurve::desc(){
    return m_desc;
}

ShortCut ACurve::shortCut(){
    return m_shortCut;
}


QString ACurve::mnemonic(){
    return m_mnemonic;
}


void ACurve::setShortCut(ShortCut shortCut){
    m_shortCut.setName(shortCut.name());
    m_shortCut.setRef(shortCut.ref());
}

void ACurve::checkingTheDataFunction(){
    if(m_scale < 1.000001 && m_scale > 0.99999 && m_offset < 0.000001 && m_offset > -0.000001)
        dataCountingFunction = &ACurve::rawData;
    else
        dataCountingFunction = &ACurve::recalculatedData;
}

void ACurve::setOffset(qreal offset){
    m_offset = offset;
    checkingTheDataFunction();
}

void ACurve::setScale(qreal scale){
    m_scale = scale;
    checkingTheDataFunction();
}

void ACurve::setSizeOffset(uint sizeOffset){
    m_sizeOffsetInByte = sizeOffset;
}

void ACurve::setMnemonic(QString mnemonic){
    m_mnemonic = mnemonic;
}

void ACurve::setDataType(QString dataType){
    m_dataType = dataType;
}

void ACurve::setDesc(Desc *desc){
    m_desc = desc;
}

/*uint ACurve::offset(){
    return m_offset;
}*/





