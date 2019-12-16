#include "curvelineitem.h"
#include <QGraphicsScene>
#include <QTime>
#include <QRgb>

CurveLineItem::CurveLineItem(Curve *curve)
    :CurveBaseItem(curve){
    m_pen = new QPen(QColor(qrand()%255,qrand()%255,qrand()%255),3);
    m_brush = new QBrush(QColor(qrand()%255,qrand()%255,qrand()%255));
}
qreal CurveLineItem::operator[](int index){
    if(m_limit)
        return fmod((*m_curve)[index] * m_scale  + m_leftShift,m_limit);
    else
        return ((*m_curve)[index] * m_scale  + m_leftShift);
}
CurveLineItem::~CurveLineItem(){}

bool CurveLineItem::isCrosses(QPoint point,int y){
    QImage image(static_cast<int>(m_limit),2000,QImage::Format_ARGB32);
    image.fill(QColor(0,0,0,0));
    QPainter p(&image);
    QPainter paintHeader;
    paint(&p,nullptr,y,y+1500);
    return image.pixel(QPoint(point.x(),point.y() + 500));
}
uint CurveLineItem::amountSaturation(uint index){
    if(m_limit && index < static_cast<uint>(m_curve->getSize()))
        return static_cast<uint>(((*m_curve)[index] * m_scale  + m_leftShift)/m_limit);
    return 0;
}
void CurveLineItem::paint(QPainter *painter,QPainter *painterHeader,qreal yTop,qreal yBottom){
    //QTime time = QTime::currentTime();
    if(!m_mainValue)
        return;
    painter->setFont(QFont("Arial Black",8,50));
    if(m_mainValue->minimumForScale() > yTop  + 2000 || m_mainValue->maximumForScale() < yTop){

        return;
    }
    painter->setPen(*m_pen);
    int indexBegin = 0;
    QPointF prevPoint = QPointF(operator[](0),m_mainValue->data(0) - yTop + 500);
    for(uint64_t i = 0; i < m_mainValue->size(); ++i){
       if(m_mainValue->data(i) > yTop && m_mainValue->data(i) < yBottom){
           indexBegin = i > 2?i - 2 : 0;
           prevPoint = QPointF(operator[](indexBegin),m_mainValue->data(indexBegin) - yTop + 500);
           break;
       }
    }
    int prevMain = static_cast<int>(m_mainValue->data(0) - yTop + 500);
    int prevIndex = 0;
    painter->drawText(QPointF(prevPoint.x()+10,prevPoint.y()),QString::number(m_mainValue->operator[](indexBegin)));
    int i;
     //qDebug() << time.msecsTo( QTime::currentTime() );
    for(i = indexBegin + 1;i < m_mainValue->size(); ++i){
        if(static_cast<int>(m_mainValue->data(i) - yTop + 500) == prevMain){
            prevMain = static_cast<int>(m_mainValue->data(i) - yTop + 500);
            continue;
        }

        prevMain = static_cast<int>(m_mainValue->data(i) - yTop + 500);
        if(amountSaturation(i) > amountSaturation(prevIndex)){
            painter->drawLine(prevPoint,QPointF(m_limit,m_mainValue->data(i) - yTop + 500));
            painter->drawLine(QPointF(0,m_mainValue->data(i) - yTop + 500),QPointF(operator[](i),m_mainValue->data(i) - yTop + 500));
            painter->drawText(QPointF(50,m_mainValue->data(i) - yTop + 500),QString::number(m_mainValue->operator[](i)));
        }
        else if(amountSaturation(i) < amountSaturation(prevIndex)){
            painter->drawLine(prevPoint,QPointF(0,m_mainValue->data(i) - yTop + 500));
            painter->drawLine(QPointF(m_limit,m_mainValue->data(i) - yTop + 500),QPointF(operator[](i)+ m_leftShift,m_mainValue->data(i) - yTop + 500));
        }
        else{
            painter->drawLine(prevPoint,QPointF(operator[](i),m_mainValue->data(i) - yTop + 500));
            //painter->drawText(QPointF(operator[](i) + 50,m_mainValue->data(i) - y + 500),QString::number(m_mainValue->operator[](i)));
        }
        prevPoint = QPointF(operator[](i),m_mainValue->data(i) - yTop + 500);
        prevIndex = i;
        if(m_mainValue->data(i) - yTop + 500 > yBottom || m_mainValue->data(i) < yTop-500){
            break;
        }
    }
    //*************Paint Header*******************
    if(!painterHeader)
        return;
    int width = painterHeader->device()->width();
    painterHeader->setFont(QFont("Arial Black",8,10));
    painterHeader->setPen(*m_pen);
    if(!m_isActive)
       painterHeader->setBrush(QBrush(QColor(250,250,250,250)));
    else
       painterHeader->setBrush(QBrush(QColor(200,250,200,200)));
    painterHeader->drawRect(QRect(10,m_positionInHeader *m_headerSliceHeight,width - 20,m_headerSliceHeight));
    //painterHeader->setPen(*m_pen);
    painterHeader->drawText(QRect(15,m_positionInHeader *m_headerSliceHeight,width,m_headerSliceHeight),Qt::AlignLeft|Qt::AlignVCenter,QString::number((*m_curve)[indexBegin]));
    painterHeader->drawText(QRect(0,m_positionInHeader *m_headerSliceHeight,width - 15,m_headerSliceHeight),Qt::AlignRight|Qt::AlignVCenter,QString::number(i - indexBegin));
    painterHeader->drawText(QRect(0,m_positionInHeader *m_headerSliceHeight,width,m_headerSliceHeight),Qt::AlignHCenter|Qt::AlignVCenter,m_curve->getMnemonic());
    //painterHeader->drawLine(QPoint(0,m_positionInHeader *m_headerSliceHeight),QPoint(width,m_positionInHeader *m_headerSliceHeight));


}
