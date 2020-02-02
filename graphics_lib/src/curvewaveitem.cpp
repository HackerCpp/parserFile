#include "curvewaveitem.h"
#include <QtMath>

CurveWaveItem::CurveWaveItem(Curve *curve)
    :CurveBaseItem(curve){
    m_pen = new QPen(QColor(qrand()%255,qrand()%255,qrand()%255),3);
    m_brush = new QBrush(QColor(qrand()%255,qrand()%255,qrand()%255));
    m_drawingMode = WAVE;
}

void CurveWaveItem::paint(QPainter *painter,QPainter *painterHeader,qreal yTop,qreal yBottom,bool *flag){
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
    painter->setPen(*m_pen);

    uint quantityElem = m_curve->quantiytElements() / m_curve->sizeOfType();
    uint i;
    double step = (double)m_limit/quantityElem;

    /*for(i = indexBegin;i < m_mainValue->size(); ++i){
        if(*flag)
            return;
        for(uint j = 0;j < quantityElem - 1; j++){
            painter->drawLine(QPointF(step*j,(m_mainValue->data(i) - yTop + 1000) - data(i*quantityElem + j)),
                              QPointF(step*(j+1),(m_mainValue->data(i) - yTop + 1000) - data(i*quantityElem + j + 1)));
        }
        if(m_mainValue->data(i) > yTop + 2000 || m_mainValue->data(i) < yTop - 1000){
            break;
        }
    }

    for(i = indexBegin;i < m_mainValue->size(); ++i){
        if(*flag)
            return;
        for(uint j = 0;j < quantityElem - 1; j++){
            if(data(i*quantityElem + j) > 0){
                painter->drawPoint(step*j,(m_mainValue->data(i) - yTop + 1000));
            }

        }
        if(m_mainValue->data(i) > yTop + 2000 || m_mainValue->data(i) < yTop - 1000){
            break;
        }
    }*/
    QColor color = QColor(painter->pen().color());
    QColor color2(0,0,0);
    qreal alphaKoeff = 1 /(m_curve->maximum() * m_scale);
    qreal alphaKoeff2 = 1 /(fabsl(m_curve->minimum() * m_scale));
    for(i = indexBegin;i < m_mainValue->size(); ++i){
        if(*flag)
            return;
        for(uint j = 0;j < quantityElem - 1; j++){
            if(data(i * quantityElem + j) >= 0){
                color.setAlphaF(data(i * quantityElem + j) * alphaKoeff);
                QPen pen(color,painter->pen().width());
                painter->setPen(pen);
                painter->drawPoint(step*j,(m_mainValue->data(i) - yTop + 1000));
            }
            else{
                color2.setAlphaF(fabsl(data(i * quantityElem + j)) * alphaKoeff2);
                QPen pen(color2,painter->pen().width());
                painter->setPen(pen);
                painter->drawPoint(step*j,(m_mainValue->data(i) - yTop + 1000));
            }
        }
        if(m_mainValue->data(i) > yTop + 2000 || m_mainValue->data(i) < yTop - 1000){
            break;
        }
    }

    //Рисуем заголовок
    drawHeader(painterHeader);
}

qreal CurveWaveItem::operator[](int index){
    return m_curve->operator[](index) * m_scale;
}
qreal CurveWaveItem::data(int index){
   return m_curve->data(index) * m_scale;
}


CurveWaveItem::~CurveWaveItem(){

}
