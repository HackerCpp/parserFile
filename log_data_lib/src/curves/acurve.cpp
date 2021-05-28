#include "acurve.h"
#include <QDebug>



ACurve::ACurve(){
    m_time = m_depth = m_userValue = nullptr;
    m_recordPoint = qQNaN();
    // if m_scale = 1 and m_offset = 0 use ACurve::rawData
    // else use ACurve::recalculatedData
    m_uid = QUuid().createUuid().toString();
    m_scale = 1;
    m_offset = 0;
    dataCountingFunction = &ACurve::rawData;
}

ICurve *ACurve::time() const{
   return m_time;
}

ICurve *ACurve::depth() const{
    return m_depth;
}

ICurve *ACurve::userBaseValue() const{
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

uint ACurve::size() const{
    return 0;
}

qreal ACurve::maximum() const{
    return (this->*dataCountingFunction)(maxData());
}

qreal ACurve::minimum() const{
    return (this->*dataCountingFunction)(minData());
}

Desc *ACurve::desc() const{
    return m_desc;
}

ShortCut ACurve::shortCut() const{
    return m_shortCut;
}


QString ACurve::mnemonic()const{
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

void ACurve::setSizeOffsetInBytes(uint sizeOffset){
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







