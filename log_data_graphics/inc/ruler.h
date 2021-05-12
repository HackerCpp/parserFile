#ifndef RULER_H
#define RULER_H
#include "objectoftheboard.h"
#include "boardfortrack.h"

class Ruler : public ObjectOfTheBoard
{
    int m_width;
    int m_positionX;
    BoardForTrack *m_board;
    QPointF m_prevPoint;


    void mousePressEvent(QGraphicsSceneMouseEvent *event)override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event)override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event)override;
public:
    Ruler(BoardForTrack *board);
    virtual ~Ruler()override{}
 protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem*, QWidget*)override;
    void run() override;
    QRectF boundingRect()const override;
    void resizePictures()override;
    void toSetTheLocationOfTheImageAfterDrawing() override;
};

#endif // RULER_H
