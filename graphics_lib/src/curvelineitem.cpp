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

uint CurveLineItem::amountSaturation(uint index){
    if(m_limit && index < static_cast<uint>(m_curve->getSize()))
        return static_cast<uint>(((*m_curve)[index] * m_scale  + m_leftShift)/m_limit);
    return 0;
}

void CurveLineItem::paint(QPainter *painter,QPainter *painterHeader,qreal yTop,qreal yBottom,bool *flag){
    //QTime time = QTime::currentTime();
    if(!m_mainValue)
        return;
    if(painterHeader){
        int width = painterHeader->device()->width();
        painterHeader->setPen(QPen());
        painterHeader->drawRect(QRect(10,m_positionInHeader *m_headerSliceHeight,width - 20,m_headerSliceHeight));
        painterHeader->drawText(QRect(0,m_positionInHeader *m_headerSliceHeight,width,m_headerSliceHeight),Qt::AlignHCenter|Qt::AlignVCenter,m_curve->getMnemonic());
    }
    uint indexBegin = m_mainValue->indexBegin();
    if(indexBegin == m_mainValue->size())
        return;
    painter->setFont(QFont("Arial Black",8,50));
    painter->setPen(*m_pen);

    QPointF prevPoint = QPointF(operator[](indexBegin),m_mainValue->data(indexBegin) - yTop + 1000);
    //int prevMain;
    int prevIndex = 0;
    painter->drawText(QPointF(prevPoint.x()+10,prevPoint.y()),QString::number(m_mainValue->operator[](indexBegin)));
    uint i;
     //qDebug() << time.msecsTo( QTime::currentTime() );
    for(i = indexBegin + 1;i < m_mainValue->size(); ++i){
        if(*flag)
            return;
        //prevMain = static_cast<int>(m_mainValue->data(i) - yTop + 1000);
        if(amountSaturation(i) > amountSaturation(prevIndex)){
            painter->drawLine(prevPoint,QPointF(m_limit,m_mainValue->data(i) - yTop + 1000));
            painter->drawLine(QPointF(0,m_mainValue->data(i) - yTop + 1000),QPointF(operator[](i),m_mainValue->data(i) - yTop + 1000));
            painter->drawText(QPointF(50,m_mainValue->data(i) - yTop + 1000),QString::number(m_mainValue->operator[](i)));
        }
        else if(amountSaturation(i) < amountSaturation(prevIndex)){
            painter->drawLine(prevPoint,QPointF(0,m_mainValue->data(i) - yTop + 1000));
            painter->drawLine(QPointF(m_limit,m_mainValue->data(i) - yTop + 1000),QPointF(operator[](i)+ m_leftShift,m_mainValue->data(i) - yTop + 1000));
        }
        else{
            painter->drawLine(prevPoint,QPointF(operator[](i),m_mainValue->data(i) - yTop + 1000));
            //painter->drawText(QPointF(operator[](i) + 50,m_mainValue->data(i) - y + 500),QString::number(m_mainValue->operator[](i)));
        }
        prevPoint = QPointF(operator[](i),m_mainValue->data(i) - yTop + 1000);
        prevIndex = i;
        if(m_mainValue->data(i) > yTop + 2000 || m_mainValue->data(i) < yTop - 1000){
            break;
        }
    }
    //Рисуем Заголовок
    drawHeader(painterHeader);
}
