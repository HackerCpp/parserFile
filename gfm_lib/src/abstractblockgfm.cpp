#include "inc/abstractblockgfm.h"
#include <QDebug>

AbstractBlockGFM::AbstractBlockGFM()
    :m_block(nullptr){
    m_codec = QTextCodec::codecForMib(1015);
}

void AbstractBlockGFM::setName(QString name){
    m_name = name;
}

QString AbstractBlockGFM::getName()const{
    return m_name;
}

void AbstractBlockGFM::parser(QByteArray *bodyBlock){
    m_block = new QByteArray(*bodyBlock);
}

QByteArray AbstractBlockGFM::getForSave(){
    QByteArray blockForWrite;
    int f_nameSize = m_name.size() * 2;
    qDebug() << m_name << "  " << m_name.size();
    blockForWrite.append(reinterpret_cast<char*>(&f_nameSize),2);       //Размер названия блока
    blockForWrite.append(m_codec->fromUnicode(m_name).mid(2));
    int f_dataBlockSize = m_block->size() + 8;
    if(f_dataBlockSize % 2){
        ++f_dataBlockSize;
        m_block->append('0');
    }
    blockForWrite.append(reinterpret_cast<char*>(&f_dataBlockSize),4);
    blockForWrite.append(m_codec->fromUnicode("\r\n").mid(2));
    blockForWrite.append(*m_block);
    blockForWrite.append(m_codec->fromUnicode("\r\n").mid(2));
    return blockForWrite;
}

AbstractBlockGFM::~AbstractBlockGFM(){
}

