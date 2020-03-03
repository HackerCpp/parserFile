#include "datablock.h"



DataBlock::DataBlock(){
    m_curves = new QList<ICurve*>;
    m_type = DATA_BLOCK;
    m_shortCuts = new QList<ShortCut>;
}

DataBlock::~DataBlock(){
    if(m_curves){
        delete m_curves;
        m_curves = nullptr;
    }


}

void DataBlock::setNumberOfVectors(uint numberOfVectors){
    m_numberOfVectors = numberOfVectors;
}

void DataBlock::setPlugins(QString plugins){
    m_plugins = plugins;
}

void DataBlock::setModuleMnemonic(QString moduleMnemonics){
    m_moduleMnemonics = moduleMnemonics;
}

void DataBlock::setNameRecord(QString nameRecord){
    m_nameRecord = nameRecord;
}

void DataBlock::addShortCut(ShortCut shortCut){
    if(m_shortCuts)
        m_shortCuts->push_back(shortCut);

}

void DataBlock::setCurves(QList<ICurve*>curves){
    if(!m_curves){
        qDebug() << "евозможно добавить кривую m_curves не определён";
        return;
    }
    foreach(auto curve, curves)
        m_curves->push_back(curve);
}

void DataBlock::setcurve(ICurve* curve){
    if(!m_curves){
        qDebug() << "евозможно добавить кривую m_curves не определён";
        return;
    }
    m_curves->push_back(curve);
}


uint DataBlock::numberOfVectors(){
    return m_numberOfVectors;
}

QList<ICurve*> *DataBlock::curves(){
    return m_curves;
}

QList<ShortCut> *DataBlock::shortCuts(){
    return m_shortCuts;
}
