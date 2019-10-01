#ifndef GRID_H
#define GRID_H
#include "inc/graphic/basecurveclass.h"

class Grid : public BaseCurveClass{
    Q_OBJECT

    int m_ollHeight;
public:
    Grid(int height);
protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem*, QWidget*);
    QRectF boundingRect() const;
};

#endif // GRID_H
