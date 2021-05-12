#include "canvas.h"
#include <QDebug>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsItem>


Canvas::Canvas()
{

}

void Canvas::mouseMoveEvent(QGraphicsSceneMouseEvent *event){
    QGraphicsScene::mouseMoveEvent(event);
}
