#include "inc/graphic/curveline.h"
#include <QPainter>
#include <QPainterPath>
#include <QDebug>
#include <QtGlobal>
#include <QStyleOptionGraphicsItem>
#include <QCoreApplication>
#include <QTime>

CurveLine::CurveLine(QVector<qreal>*dataLine){
    m_dataLine = dataLine;
    m_scale = 0.0001;
    m_width = 2;
    isPaint = true;
    QColor tableColor[36]= {QColor(255, 0, 0),QColor(139, 0, 0),QColor(255, 20, 147),QColor(255, 69, 0),QColor(255, 0, 255),
                                QColor(147, 112, 219),QColor(138, 43, 226),QColor(75, 0, 130),QColor(210, 105, 30),QColor(139, 69, 19),
                           QColor(128, 0, 0),QColor(255, 0, 255),QColor(128, 0, 128),QColor(255, 0, 0),QColor(0, 0, 255),
                           QColor(0, 0, 128),QColor(34, 139, 34),QColor(0, 100, 0),QColor(32, 178, 170),QColor(95, 158, 160),
                           QColor(30, 144, 255),QColor(123, 104, 238),QColor(0, 0, 255),QColor(0, 0, 139),QColor(25, 25, 112),
                           QColor(105, 105, 105),QColor(47, 79, 79),QColor(0, 0, 0),QColor(200,0,255),
                           QColor(255,0,255),QColor(255,0,200),QColor(255,0,150),QColor(255,0,100),QColor(255,0,50)};
    m_min = 0;m_max = 0;m_width = 0;
    foreach(auto value,*m_dataLine){
        m_min = m_min < value ? m_min : value;
        m_max = m_max < value ? value : m_max;
    }
    m_min=m_min<0?m_min:0;
    m_pen = new QPen(tableColor[qrand()%35]);
    m_pen->setWidthF(2);
}
void CurveLine::paint(QPainter *painter, const QStyleOptionGraphicsItem*option, QWidget*){
    painter->setPen(*m_pen);
    if(m_dataLine->size() <= m_indexBegin)
        return;
    QPointF prevPoint = QPointF(saturation(m_dataLine->data()[m_indexBegin]),0);
    for(int i = m_indexBegin+1; i < (m_dataLine->size()< m_indexEnd?m_dataLine->size():m_indexEnd);i++){
        if(amountOfSaturation(m_dataLine->data()[i]) > amountOfSaturation(m_dataLine->data()[i-1])){
            painter->drawLine(prevPoint,QPointF(m_del,(i-1)*m_step));
            painter->drawLine(QPointF(0,i*m_step),QPointF(saturation(m_dataLine->data()[i]),i*m_step));
        }
        else if(amountOfSaturation(m_dataLine->data()[i]) < amountOfSaturation(m_dataLine->data()[i-1])){
            painter->drawLine(prevPoint,QPointF(0,(i-1)*m_step));
            painter->drawLine(QPointF(m_del,i*m_step),QPointF(saturation(m_dataLine->data()[i]),i*m_step));
        }
        else{
            painter->drawLine(QPointF(saturation(m_dataLine->data()[i]),i*m_step),prevPoint);
        }
        prevPoint = QPointF(saturation(m_dataLine->data()[i]),i*m_step);
    }
}
CurveLine::CurveLine(){
    qDebug()<<"";
}
QRectF CurveLine::boundingRect()const{
    return QRectF(0,0,m_del,m_dataLine->size()*m_step);
}
int CurveLine::amountOfSaturation(qreal value){
    return ((int)(value*m_scale - m_min)/m_del);
}
qreal CurveLine::saturation(qreal value){
    return ((value*m_scale-m_min) - ((int)((value*m_scale-m_min)/m_del)*m_del));
}
