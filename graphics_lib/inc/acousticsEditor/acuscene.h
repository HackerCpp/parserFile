#ifndef ACUSCENE_H
#define ACUSCENE_H
#include <QGraphicsScene>

class AcuScene : public QGraphicsScene
{
    QGraphicsLineItem *m_lineItem;
    QGraphicsTextItem *m_textItem;
    bool m_isLeftMouseClick,m_isRightMouseClick;

public:
    AcuScene();
    ~AcuScene()override{}

    void mousePressEvent(QGraphicsSceneMouseEvent *event)override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event)override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event)override;
};
#endif // ACUSCENE_H
