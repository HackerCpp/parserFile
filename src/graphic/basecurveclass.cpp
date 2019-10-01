#include "inc/graphic/basecurveclass.h"
#include <QDebug>
#include <QGraphicsScene>

BaseCurveClass::BaseCurveClass(){
    m_del = 500;
    m_step = 10;
    m_indexBegin = 0;
    m_indexEnd = 0;
}
void BaseCurveClass::scrollChange(qreal leftX,qreal topY,qreal rightX,qreal downY){
   m_indexBegin = topY/m_step - 2;
   m_indexEnd = downY/m_step + 10;
   m_del = rightX -  leftX - 100;
}
