#ifndef GRID_H
#define GRID_H
#include "inc/graphic/basecurveclass.h"

class Grid : public BaseCurveClass{
    Q_OBJECT

    int m_stepY, m_stepX;
    int m_ollHeight;
    int m_mainValueMin;
public:
    Grid(ScaleFactor *scaleFactor);
protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem*, QWidget*);
    QRectF boundingRect() const;
};

#endif // GRID_H
