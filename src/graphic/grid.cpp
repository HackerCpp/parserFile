#include "inc/graphic/grid.h"
#include <QPainter>
#include <QDebug>
#include <inc/models/modelgfm.h>

Grid::Grid(int height){
    m_ollHeight = height;
    m_step = 60;
}

void Grid::paint(QPainter *painter, const QStyleOptionGraphicsItem*, QWidget*){
    painter->setPen(QPen(Qt::black));
    for(int i = m_indexBegin; i < m_indexEnd;i ++){
        painter->drawLine(QPoint(0,i * m_step),QPoint(m_del,i * m_step));
        painter->drawText(QPoint(-50,i * m_step),"  " +QString::number( i));
    }
    for(int j = 0; j < m_del;j += m_step){
        painter->drawLine(QPoint(j,m_indexBegin * m_step),QPoint(j,m_indexEnd * m_step));
    }
    painter->drawLine(QPoint(m_del+2,m_indexBegin * m_step),QPoint(m_del+2,m_indexEnd * m_step));
}

QRectF Grid::boundingRect()const{
    return QRect(-50,0,m_del+50,m_ollHeight);
}
