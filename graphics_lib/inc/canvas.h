#ifndef CANVAS_H
#define CANVAS_H
#include <QGraphicsScene>
#include <QtDebug>
#include <QKeyEvent>

class Canvas  : public QGraphicsScene
{
public:
    Canvas();

    void mouseMoveEvent(QGraphicsSceneMouseEvent *event)override;
    void keyPressEvent(QKeyEvent *keyEvent)override {
        //qDebug() << keyEvent->text();
       QGraphicsScene::keyPressEvent(keyEvent);
    }
};

#endif // CANVAS_H
