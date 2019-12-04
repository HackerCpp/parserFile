#ifndef GRID_H
#define GRID_H
#include "basegroup.h"

class Grid : public BaseGroup{
    //qreal m_scale;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem*, QWidget*) override;
    void run()override;
public:
    Grid(int width);
    void setSize(QRectF rect);
};

#endif // GRID_H
