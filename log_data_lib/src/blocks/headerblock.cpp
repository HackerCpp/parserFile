#include "headerblock.h"
#include "headerinfo.h"
#include <QList>
#include <QDebug>

HeaderBlock::HeaderBlock(){
    m_type = HEADER_BLOCK;
    m_info = new QList<QSharedPointer<HeaderInfo>>;
}

HeaderBlock::~HeaderBlock(){
    if(m_info){
        delete m_info;
        m_info = nullptr;
    }
}

void HeaderBlock::setHeaderInfo(QSharedPointer<HeaderInfo> info){
    if(!m_info){
        qDebug() << "m_info не создан";
    }
    m_info->push_back(info);
}

QList<QSharedPointer<HeaderInfo>> *HeaderBlock::infoHeader(){
    return m_info;
}
