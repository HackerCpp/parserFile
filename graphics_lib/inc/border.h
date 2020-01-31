#ifndef BORDER_H
#define BORDER_H
#include "basegroup.h"

class Border : public BaseGroup {
    bool m_isClose;
    int m_leftLimiter,m_rememberPosition;
    QImage *m_collapseTab,*m_expandTab;
    QImage *m_curentIsClose;
    int m_width;
    qreal m_scale;
    int m_movingX;
    QPointF m_prevPoint;
    bool m_isMove;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem*, QWidget*) override;
    void run()override;
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event)override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event)override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event)override;
public:
    Border(int position,int leftLimiter);
    void updateP(QPointF leftUp,QPointF rightDown,bool forceARedraw)override;
public slots:
    void shift(int leftPosition)override;
};

#endif // BORDER_H
