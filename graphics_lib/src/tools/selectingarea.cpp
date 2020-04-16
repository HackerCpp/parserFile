#include "selectingarea.h"
#include <QPainter>

SelectingArea::SelectingArea(QRectF rect){
    m_rect = rect;
}

SelectingArea::~SelectingArea(){

}


void SelectingArea::paint(QPainter *painter, const QStyleOptionGraphicsItem*, QWidget*){
    QColor color = QColor(0,0,qrand()%255);
    QBrush brush(QColor(255,255,255,150));
    painter->setPen(QPen(color,2,Qt::DashDotDotLine));
    painter->setBrush(brush);
    painter->drawRect(m_rect);
}

int SelectingArea::left(){
    if(m_rect.width() > 0)
        return m_rect.x();
    else
        return m_rect.x() + m_rect.width();
}

int SelectingArea::right(){
    if(m_rect.width() > 0)
        return m_rect.x() + m_rect.width();
    else
        return m_rect.x();
}

int SelectingArea::top(){
    if(m_rect.height() > 0)
        return m_rect.y();
    else
        return m_rect.y() + m_rect.height();
}

int SelectingArea::bottom(){
    if(m_rect.height() > 0)
        return m_rect.y() + m_rect.height();
    else
        return m_rect.y();
}
