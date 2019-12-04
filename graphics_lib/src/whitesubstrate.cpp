#include "whitesubstrate.h"


WhiteSubstrate::WhiteSubstrate(int width){
    m_leftX = 0;
    m_rightX = width;
    m_curentPixmap = new  QImage(m_rightX - m_leftX,2000,QImage::Format_RGB32);
    m_doublePixMap = new QImage(m_rightX - m_leftX,2000,QImage::Format_RGB32);
    m_visibilitySquare = new QRectF(0,0,0,0);
    setZValue(-100);
}
void WhiteSubstrate::setSize(QRectF rect){
    wait();
    m_rightX = static_cast<int>(rect.width());

    QImage *img = new  QImage(m_rightX - m_leftX,2000,QImage::Format_ARGB32);
    QImage *deleteImage = m_curentPixmap;
    m_curentPixmap = img;
    delete deleteImage;

    img = new QImage(m_rightX - m_leftX,2000,QImage::Format_ARGB32);
    deleteImage = m_doublePixMap;
    m_doublePixMap = img;
    delete deleteImage;
    start();
}
void WhiteSubstrate::paint(QPainter *painter, const QStyleOptionGraphicsItem*, QWidget*){
    if(m_curentPixmap)
        painter->drawImage(QRect(m_leftX,m_visibilitySquare->y() - 500,m_curentPixmap->width(),m_curentPixmap->height()),*m_curentPixmap);
    else
        qDebug() << "null";
}

void WhiteSubstrate::run(){
    m_doublePixMap->fill(QColor(250,250,250));
    swapPixMap();
}
