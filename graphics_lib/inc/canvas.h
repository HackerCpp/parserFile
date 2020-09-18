#ifndef CANVAS_H
#define CANVAS_H
#include <QGraphicsScene>

class Canvas  : public QGraphicsScene
{
public:
    Canvas();

    void mouseMoveEvent(QGraphicsSceneMouseEvent *event)override;
};

#endif // CANVAS_H
