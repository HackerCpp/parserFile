#include "inc/abstractblockgfm.h"
#include <QDebug>

AbstractBlockGFM::AbstractBlockGFM(){
    m_codec = QTextCodec::codecForMib(1015);
}
void AbstractBlockGFM::setName(QString name){
    m_name = name;
}
QString AbstractBlockGFM::getName()const{
    return m_name;
}
void AbstractBlockGFM::parser(QByteArray *bodyBlock){

}
QByteArray AbstractBlockGFM::getForSave(){
    return nullptr;
}
AbstractBlockGFM::~AbstractBlockGFM(){
}

