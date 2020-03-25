#include "verticaltrack.h"

VerticalTrack::VerticalTrack(ATrack *track,QMap<QString,ICurve*> *curves)
    :AGraphicTrack(track,curves)
{
    m_border = new RightBorder();
    m_curentPixmap = new QImage(m_track->getWidth() - m_border->width(),pictureHeight,QImage::Format_ARGB32);
    m_doublePixMap = new QImage(m_track->getWidth() - m_border->width(),pictureHeight,QImage::Format_ARGB32);
    QList <AItem*> itemInfo = track->getItems();
    m_items->push_back(AGraphicItem::createItem(itemInfo.last(),curves->take(itemInfo.last().name())));
}

void VerticalTrack::init(){

}

void VerticalTrack::paint(QPainter *painter, const QStyleOptionGraphicsItem*, QWidget*){
    if(m_border)
        painter->drawImage(QRect(m_track->getWidth() - m_border->width(),m_visibilitySquare->y(),m_border->width(),m_border->height()),*m_border);
     else
        qDebug() << "border для трека не создан, не может быть нарисован";
    if(m_curentPixmap)
        painter->drawImage(QRect(0,m_visibilitySquare->y() - offsetUp,m_curentPixmap->width(),m_curentPixmap->height()),*m_curentPixmap);
    else
        qDebug() << "track не может быть нарисован не создана картинка";
}

void VerticalTrack::mousePressEvent(QGraphicsSceneMouseEvent *event){

}

void VerticalTrack::mouseMoveEvent(QGraphicsSceneMouseEvent *event){

}

void VerticalTrack::mouseReleaseEvent(QGraphicsSceneMouseEvent *event){

}

void VerticalTrack::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event){

}



