#include "curvelineitem.h"
#include <QGraphicsScene>
#include <QTime>
#include <QRgb>

CurveLineItem::CurveLineItem(Curve *curve)
    :CurveBaseItem(curve){
    m_pen = new QPen(QColor(qrand()%255,qrand()%255,qrand()%255),3);
    m_brush = new QBrush(QColor(qrand()%255,qrand()%255,qrand()%255));
}

CurveLineItem::~CurveLineItem(){}

bool CurveLineItem::isCrosses(QPoint point,int y){
    QImage image(static_cast<int>(m_curve->limit()),2000,QImage::Format_ARGB32);
    image.fill(QColor(0,0,0,0));
    QPainter p(&image);
    paint(&p,y);
    return image.pixel(QPoint(point.x(),point.y() + 500));
}
void CurveLineItem::paint(QPainter *painter,qreal y){
    if(!m_curve->mainValue())
        return;
    painter->setFont(QFont("Arial Black",8,50));
    if(m_curve->mainValue()->minimumForScale() > y  + 2000 || m_curve->mainValue()->maximumForScale() < y)
        return;
    painter->setPen(*m_pen);
    uint64_t indexBegin = 0;
    QPointF prevPoint = QPointF(m_curve->operator[](0),m_curve->mainValue()->data(0) - y + 500);
    for(uint64_t i = 0; i < m_curve->mainValue()->getSize(); ++i){
       if(m_curve->mainValue()->data(i) > y){
           indexBegin = i > 2?i - 2 : 0;
           prevPoint = QPointF(m_curve->operator[](indexBegin),m_curve->mainValue()->data(indexBegin) - y + 500);
           break;
       }
    }
    painter->drawText(QPointF(prevPoint.x()+10,prevPoint.y() + 10),QString::number(m_curve->mainValue()->getData(indexBegin)));
    for(uint64_t i = indexBegin + 1;i < m_curve->mainValue()->getSize(); ++i){
        if(m_curve->amountSaturation(i) > m_curve->amountSaturation(i - 1)){
            painter->drawLine(prevPoint,QPointF(m_curve->limit(),m_curve->mainValue()->data(i) - y+ 500));
            painter->drawLine(QPointF(0,m_curve->mainValue()->data(i) - y + 500),QPointF(m_curve->operator[](i),m_curve->mainValue()->data(i) - y+ 500));
            painter->drawText(QPointF(50,m_curve->mainValue()->data(i) - y + 500),QString::number(m_curve->mainValue()->getData(i)));
        }
        else if(m_curve->amountSaturation(i) < m_curve->amountSaturation(i - 1)){
            painter->drawLine(prevPoint,QPointF(0,m_curve->mainValue()->data(i) - y+ 500));
            painter->drawLine(QPointF(m_curve->limit(),m_curve->mainValue()->data(i) - y+ 500),QPointF(m_curve->operator[](i),m_curve->mainValue()->data(i) - y+ 500));
        }
        else{
            painter->drawLine(prevPoint,QPointF(m_curve->operator[](i),m_curve->mainValue()->data(i) - y+ 500));
            //painter->drawText(QPointF(m_curve->operator[](i) + 50,m_curve->mainValue()->data(i) - y + 500),QString::number(m_curve->mainValue()->getData(i)));
        }
        prevPoint = QPoint(m_curve->operator[](i),m_curve->mainValue()->data(i) - y+ 500);
        if(m_curve->mainValue()->operator[](i) - y+ 500 > 2000)
            break;
    }
}
