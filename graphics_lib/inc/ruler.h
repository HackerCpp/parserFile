#ifndef RULER_H
#define RULER_H
#include "basegroup.h"

class Ruler : public BaseGroup{
    Q_OBJECT
    qreal m_scale;
    int m_movingX;
    int m_x,m_y;
    QPointF m_prevPoint;
    bool m_isMove;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem*, QWidget*) override;
    void run()override;
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event)override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event)override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event)override;
    QRectF boundingRect()const override;
public:
    Ruler(int width);
    void setScale(qreal scale);
    void updateP(QPointF leftUp,QPointF rightDown,bool forceARedraw)override;
    void setSize(QRectF rect);
signals:
    void rightMouseClick();
};

#endif // RULER_H
