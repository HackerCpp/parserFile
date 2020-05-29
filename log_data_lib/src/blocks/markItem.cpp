#include "markItem.h"


markItem :: markItem(){
    m_type = MARK;

    m_valueScale = 1;
    m_color = "#ff" + QString::number((rand() % 200) + 50,16)
                   + QString::number((rand() % 200) + 50,16)
                   + QString::number((rand() % 200) + 50,16);
    m_widthLine = 2;
    m_isDashes = false;
}

markItem :: ~markItem(){

}

void markItem::setColor(QString color, bool isDashes){
    m_color = color;
    m_isDashes = isDashes;
}

void markItem::setWidth(unsigned int width){
    m_widthLine = width;
}

void markItem::setValueScale(qreal valueScale){
    m_valueScale = valueScale;
}

qreal markItem::valueScale(){
    return m_valueScale;
}

QString markItem::color(){
    return m_color;
}

bool markItem:: isDashes(){
    return m_isDashes;
}

unsigned int markItem::widthLine(){
    return m_widthLine;
}
