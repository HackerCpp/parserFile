#include "headeritem.h"
#include <QPainter>

HeaderItem::HeaderItem(QImage *img){
    m_img = img;
    this->setZValue(100);
}

void HeaderItem::paint(QPainter *painter, const QStyleOptionGraphicsItem*, QWidget*){
    if(m_img)
        painter->drawImage(QRect(0,0,m_img->width(),m_img->height()),*m_img);
}

QRectF HeaderItem::boundingRect()const{
    return QRectF(0,0,100,100);
}
