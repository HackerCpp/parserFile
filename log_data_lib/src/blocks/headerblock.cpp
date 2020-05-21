#include "headerblock.h"
#include <QList>
#include <QDebug>

HearedBlock::HearedBlock(){
    m_type = HEADER_BLOCK;
    m_info = new QList<QSharedPointer<HeaderInfo>>;
}

HearedBlock::~HearedBlock(){
    if(m_info){
        delete m_info;
        m_info = nullptr;
    }
}

void HearedBlock::setHeaderInfo(QSharedPointer<HeaderInfo> info){
    if(!m_info){
        qDebug() << "m_info не создан";
    }
    m_info->push_back(info);
}

QList<QSharedPointer<HeaderInfo>> *HearedBlock::infoHeader(){
    return m_info;
}
