#include "acurve.h"
#include <QDebug>

ACurve::ACurve(){

}

ACurve::~ACurve(){

}

uint ACurve::setData(qreal data){
    return 0;
}

uint ACurve::setData(qreal data,uint index){
    return 0;
}

uint ACurve::setData(const char *dataPtr,uint numberOfVectors){
    qDebug() << "setData ACurve";
    return 0;
}

void ACurve::setShortCut(ShortCut shortCut){
    m_shortCut.setName(shortCut.getName());
    m_shortCut.setRef(shortCut.getRef());
}

void ACurve::setOffset(uint offset){
    m_offset = offset;
}

void ACurve::setSize(uint size){
    m_size = size;
}

void ACurve::setMnemonic(QString mnemonic){
    m_mnemonic = mnemonic;
}

void ACurve::setDataType(QString dataType){
    m_dataType = dataType;
}

void ACurve::setRecordPoint(QString recordPoint){
    m_recordPoint = recordPoint;
}

void ACurve::setDesc(Desc *desc){
    m_desc = desc;
}

uint ACurve::offset(){
    return m_offset;
}


