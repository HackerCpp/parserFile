#include "inc/graphic/wave.h"
#include <QPainter>


Wave::Wave(ScaleFactor *scaleFactor,QVector<qreal>*mainValue,QVector<qreal>*dataLine,uint numOfPoints)
           :BaseCurveClass(scaleFactor),m_numOfPoints(numOfPoints),m_dataLine(dataLine),m_mainValue(mainValue){
    m_dataLine = dataLine;
    m_mainValue = mainValue;
    m_scaleX = 100;

    QColor tableColor[36]= {QColor(255, 0, 0),QColor(139, 0, 0),QColor(255, 20, 147),QColor(255, 69, 0),QColor(255, 0, 255),
                           QColor(147, 112, 219),QColor(138, 43, 226),QColor(75, 0, 130),QColor(210, 105, 30),QColor(139, 69, 19),
                           QColor(128, 0, 0),QColor(255, 0, 255),QColor(128, 0, 128),QColor(255, 0, 0),QColor(0, 0, 255),
                           QColor(0, 0, 128),QColor(34, 139, 34),QColor(0, 100, 0),QColor(32, 178, 170),QColor(95, 158, 160),
                           QColor(30, 144, 255),QColor(123, 104, 238),QColor(0, 0, 255),QColor(0, 0, 139),QColor(25, 25, 112),
                           QColor(105, 105, 105),QColor(47, 79, 79),QColor(0, 0, 0),QColor(200,0,255),
                           QColor(255,0,255),QColor(255,0,200),QColor(255,0,150),QColor(255,0,100),QColor(255,0,50)};
    m_min = 0;m_max = 0;
    foreach(auto value,*m_dataLine){
        m_min = m_min < value ? m_min : value;
        m_max = m_max < value ? value : m_max;
    }
    m_min = m_min < 0?m_min:0;
    m_pen = new QPen(tableColor[qrand()%35]);
    m_pen->setWidth(2);
    this->setZValue(10);
}
void Wave::paint(QPainter *painter, const QStyleOptionGraphicsItem*option, QWidget*){
    if(m_scaleFactor->m_indexBegin * m_scaleFactor->m_scaleY > m_mainValue->last())
        return;
    painter->setPen(*m_pen);
    uint indexBegin = 0;
    for(int i = 0;i < m_mainValue->size();++i){
        if(m_mainValue->data()[i] >= (m_scaleFactor->m_indexBegin - m_scaleFactor->m_mainValueMin) * m_scaleFactor->m_scaleY ){
            indexBegin = (i>0?i-1:i);
            break;
        }
    }
    qreal scaleWidth = (qreal)m_scaleFactor->m_width/m_numOfPoints;
    for(uint i = indexBegin;i < m_mainValue->size();++i){
        for(int j = 1;j < m_numOfPoints;++j){
            painter->drawLine(QPointF((j-1)*scaleWidth,((m_mainValue->data()[i]- m_scaleFactor->m_mainValueMin)/(m_scaleFactor->m_scaleY) ) - ((m_dataLine->data()[i * m_numOfPoints + j-1] * m_scaleX/(m_scaleFactor->m_scaleY) ))),QPointF((j)*scaleWidth,((m_mainValue->data()[i] - m_scaleFactor->m_mainValueMin)/(m_scaleFactor->m_scaleY)) - (m_dataLine->data()[i*m_numOfPoints + j] * m_scaleX/(m_scaleFactor->m_scaleY))));
        }
        if(m_mainValue->data()[i] > (m_scaleFactor->m_indexEnd + m_scaleFactor->m_mainValueMin) * (m_scaleFactor->m_scaleY))
            return;
    }

}

QRectF Wave::boundingRect()const{
    return QRectF(0,0,m_scaleFactor->m_width,m_mainValue->last()/(m_scaleFactor->m_scaleY));
}
int Wave::amountOfSaturation(qreal value){
    return ((int)(value * m_scaleX - m_min)/(m_scaleFactor->m_width));
}
qreal Wave::saturation(qreal value){
    return fmod((value * m_scaleX - m_min),m_scaleFactor->m_width);
}
