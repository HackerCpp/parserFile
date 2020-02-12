#include "inc/graphic/spectr.h"
#include <QPainter>
#include <QDebug>
#include <cmath>
#include <QRgb>
#include <QTime>
#include "inc/graphic/IndexColor.h"

static QColor tableColor[36]= {QColor(255, 0, 0),QColor(139, 0, 0),QColor(255, 20, 147),QColor(255, 69, 0),QColor(255, 0, 255),
                       QColor(147, 112, 219),QColor(138, 43, 226),QColor(75, 0, 130),QColor(210, 105, 30),QColor(139, 69, 19),
                       QColor(128, 0, 0),QColor(255, 0, 255),QColor(128, 0, 128),QColor(255, 0, 0),QColor(0, 0, 255),
                       QColor(0, 0, 128),QColor(34, 139, 34),QColor(0, 100, 0),QColor(32, 178, 170),QColor(95, 158, 160),
                       QColor(30, 144, 255),QColor(123, 104, 238),QColor(0, 0, 255),QColor(0, 0, 139),QColor(25, 25, 112),
                       QColor(105, 105, 105),QColor(47, 79, 79),QColor(0, 0, 0),QColor(200,0,255),
                       QColor(255,0,255),QColor(255,0,200),QColor(255,0,150),QColor(255,0,100),QColor(255,0,50)};
Spectr::Spectr(ScaleFactor *scaleFactor,QVector<qreal>*mainValue,QVector<qreal>*dataLine,uint numOfPoints)
    :BaseCurveClass(scaleFactor),m_numOfPoints(numOfPoints),m_dataLine(dataLine),m_mainValue(mainValue){

    //m_min = LONG_LONG_MAX;m_max = LONG_LONG_MIN;
    foreach(auto value,*m_dataLine){
        m_min = m_min < value ? m_min : value;
        m_max = m_max < value ? value : m_max;
    }
    //m_min = m_min>=0?0:fabs(m_min);
    m_pen = new QPen(tableColor[qrand()%35]);
    m_pen->setWidth(2);
    m_image = new QVector<QPixmap*>;
    int  stepX = m_numOfPoints/m_scaleFactor->m_width;
    int scaleY = m_mainValue->data()[1] - m_mainValue->data()[0];
    int minValue = m_mainValue->data()[0]/(scaleY);

    double k = 360/(m_max - m_min);

    m_min =  m_min < 0?abs(m_min):-m_min;
    for(uint i = 0;i < m_dataLine->size()/m_numOfPoints;++i){
        QImage *img = new QImage(m_numOfPoints,1,QImage::Format_ARGB32);
        for(int j = 0;j < m_numOfPoints;++j){
            img->setPixel(j,0,colors[(int)((m_dataLine->data()[i * m_numOfPoints + (j)]+m_min) * k)]);
        }
        QPixmap *pixmap = new QPixmap(QPixmap::fromImage(*img));
        m_image->push_back(pixmap);
    }
    qDebug () << m_image->size();

   // file.close();
    /*img = new QImage(100,100,QImage::Format_ARGB32);
    QPainter p(img);
    QLinearGradient gradient(0,0,m_numOfPoints,1000);
    for(uint i = 0;i < 1000;++i){
        for(int j = 0;j <= m_numOfPoints-1;++j){
            gradient.setStart(j,i);
            gradient.setFinalStop(j,i+1);
            gradient.setColorAt(0,colors[i%350]);
            gradient.setColorAt(1,colors[j%350]);
            p.fillRect(0,0,100,100,gradient);
        }
    }*/
}

void Spectr::paint(QPainter *painter, const QStyleOptionGraphicsItem*, QWidget*){
    if(m_scaleFactor->m_indexBegin * m_scaleFactor->m_scaleY > m_mainValue->last())
        return;
    //painter->setPen(*m_pen);
    //QPoint prevPoint = QPoint(saturation(m_dataLine->first()),m_mainValue->first() - m_scaleFactor->m_mainValueMin);
    int indexBegin = 0;
    int step = m_mainValue->data()[1] - m_mainValue->data()[0] + 1000;
    painter->scale((qreal)m_scaleFactor->m_width/m_numOfPoints,step/(m_scaleFactor->m_scaleY));
    for(int i = 0;i < m_mainValue->size();++i){
        if(m_mainValue->data()[i] >= (m_scaleFactor->m_indexBegin - m_scaleFactor->m_mainValueMin) * m_scaleFactor->m_scaleY ){
            indexBegin = (i>0?i-1:0);
            //prevPoint = QPoint(saturation(m_dataLine->data()[indexBegin]),(m_mainValue->data()[indexBegin]- m_scaleFactor->m_mainValueMin)/(m_scaleFactor->m_scaleY));
            break;
        }
    }
    for(int i = indexBegin;i < m_mainValue->size();++i){
        painter->drawPixmap(QPointF(0,(m_mainValue->data()[i] - m_scaleFactor->m_mainValueMin)/(m_scaleFactor->m_scaleY)/(step/m_scaleFactor->m_scaleY)),*m_image->data()[i]);
    if(m_mainValue->data()[i] > (m_scaleFactor->m_indexEnd + m_scaleFactor->m_mainValueMin) * (m_scaleFactor->m_scaleY))
        return;
    }
}
/*void Spectr::paint(QPainter *painter, const QStyleOptionGraphicsItem*, QWidget*){
    if(m_scaleFactor->m_indexBegin * m_scaleFactor->m_scaleY > m_mainValue->last())
        return;
    painter->drawImage(QRectF(0,0,100,100),*img);
    QLinearGradient gradient(0,0,m_numOfPoints,1000);
    for(uint i = 0;i < 1000;++i){
        for(int j = 0;j <= m_numOfPoints-1;++j){
            gradient.setStart(j,0);
            gradient.setFinalStop(j,100);
            gradient.setColorAt(0,colors[i%350]);
            gradient.setColorAt(0.5,colors[j%350]);
            gradient.setColorAt(1,Qt::red);
        }
    }
}*/

QRectF Spectr::boundingRect() const{
    return QRectF(0,0,m_numOfPoints,m_mainValue->last()/(m_scaleFactor->m_scaleY));
}

int Spectr::saturation(qreal value){
    return fmod((value),35);
}

int Spectr::amountOfSaturation(qreal value){
    return 0;
}
