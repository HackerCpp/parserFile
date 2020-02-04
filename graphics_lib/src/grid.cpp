#include "grid.h"
#include <cmath>
#include <QGraphicsSceneMouseEvent>

Grid::Grid(int width){
    //m_scale = 1;
    m_leftX = 0;
    m_rightX = width;
    m_curentPixmap = new QImage(m_rightX - m_leftX,2000,QImage::Format_ARGB32);
    m_doublePixMap = new QImage(m_rightX - m_leftX,2000,QImage::Format_ARGB32);
    m_visibilitySquare = new QRectF(0,0,0,0);
    setZValue(-50);
}

void Grid::paint(QPainter *painter, const QStyleOptionGraphicsItem*, QWidget*){
    if(m_curentPixmap)
        painter->drawImage(QRect(m_visibilitySquare->x() < 0?0 : m_visibilitySquare->x(),(m_visibilitySquare->y() - fmod(m_visibilitySquare->y(),50))-100,m_curentPixmap->width(),m_curentPixmap->height()),*m_curentPixmap);
    else
        qDebug() << "null";
}
void Grid::setSize(QRectF rect){
    m_del = true;
    wait();
    m_rightX = static_cast<int>(rect.width());
    /*elete m_curentPixmap;
    delete m_doublePixMap;
    m_curentPixmap = new  QImage(m_rightX - m_leftX,2000,QImage::Format_ARGB32);
    m_doublePixMap = new QImage(m_rightX - m_leftX,2000,QImage::Format_ARGB32);*/
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
void Grid::run(){
    m_doublePixMap->fill(QColor(0,0,0,0));
    QPainter p(m_doublePixMap);
    p.setPen(QPen(QColor(0,0,0,200),1));
    for(int i = 0;i < m_rightX - m_leftX;i += 50){
       qreal x = m_visibilitySquare->x() < 0?0: m_visibilitySquare->x();
       p.drawLine(QPoint(i - fmod(x,50),0),QPoint(i - fmod(x,50),2000));
    }
    qreal width = m_rightX - m_leftX;
    for(int i = 0;i < 2000;i += 50){
       p.drawLine(QPoint(0,i),QPoint(width,i));
    }
    swapPixMap();
}




