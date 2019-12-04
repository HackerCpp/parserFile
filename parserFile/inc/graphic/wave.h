#ifndef WAVE_H
#define WAVE_H
#include "inc/graphic/basecurveclass.h"

class Wave : public BaseCurveClass{
    uint m_numOfPoints;
    QVector<qreal>* m_dataLine;
    QVector<qreal>* m_mainValue;
    QPen *m_pen;
    double m_min,m_max,m_scaleX;
    QVector<QImage *>*m_image;
public:
    Wave(ScaleFactor *scaleFactor,QVector<qreal>*mainValue,QVector<qreal>*dataLine,uint numOfPoints);
protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem*, QWidget*);
    QRectF boundingRect() const;
    qreal saturation(qreal value);
    int amountOfSaturation(qreal value);
};

#endif // WAVE_H
