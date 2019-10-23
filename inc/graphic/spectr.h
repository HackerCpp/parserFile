#ifndef SPECTR_H
#define SPECTR_H
#include <inc/graphic/basecurveclass.h>


class Spectr : public BaseCurveClass{
    uint m_numOfPoints;
    QVector<qreal>* m_dataLine;
    QVector<qreal>* m_mainValue;
    QPen *m_pen;
    double m_min,m_max,m_scaleX;
    QVector<QPixmap *>*m_image;
    QImage *img;
public:
    Spectr(ScaleFactor *scaleFactor,QVector<qreal>*mainValue,QVector<qreal>*dataLine,uint numOfPoints);
protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem*, QWidget*);
    QRectF boundingRect() const;
    int saturation(qreal value);
    int amountOfSaturation(qreal value);
};

#endif // SPECTR_H
