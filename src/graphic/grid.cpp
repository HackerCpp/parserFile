#include "inc/graphic/grid.h"
#include <QPainter>
#include <QDebug>
#include <inc/models/modelgfm.h>

Grid::Grid(ScaleFactor *scaleFactor):BaseCurveClass(scaleFactor){
    m_ollHeight = scaleFactor->m_mainValueMax - scaleFactor->m_mainValueMin;
    m_mainValueMin = scaleFactor->m_mainValueMin;
    m_stepY = 50;
    m_stepX = 50;
}

void Grid::paint(QPainter *painter, const QStyleOptionGraphicsItem*, QWidget*){
    painter->setPen(QPen(QColor(0,0,0,100)));
    for(int i = (m_scaleFactor->m_indexBegin/m_stepY); i < (m_scaleFactor->m_indexEnd/m_stepY + m_stepY);++i){
        painter->drawLine(QPoint(0,(i * m_stepY)),QPoint(m_scaleFactor->m_width,(i * m_stepY)));
        painter->drawText(QPoint(-50,(i * m_stepY)),"  " +QString::number((i * m_stepY + m_mainValueMin)*m_stepY));
    }
    for(int j = 0; j < m_scaleFactor->m_width;j += m_stepX){
        painter->drawLine(QPoint(j,m_scaleFactor->m_indexBegin),QPoint(j,m_scaleFactor->m_indexEnd));
    }
    painter->drawLine(QPoint(m_scaleFactor->m_width+2,m_scaleFactor->m_indexBegin),QPoint(m_scaleFactor->m_width+2,m_scaleFactor->m_indexEnd));
}

QRectF Grid::boundingRect()const{
    return QRect(-50,0,m_scaleFactor->m_width,m_ollHeight/(m_scaleFactor->m_scaleY));
}
