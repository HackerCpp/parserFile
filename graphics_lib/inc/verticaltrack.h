#ifndef VERTICALTRACK_H
#define VERTICALTRACK_H
#include "agraphictrack.h"
#include "rightborder.h"

class VerticalTrack : public AGraphicTrack
{
    RightBorder *m_border;

public:
    VerticalTrack(ATrack *track,QMap<QString,ICurve*> *curves);
    ~VerticalTrack()override;
private:
    void init();
protected:
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem*, QWidget*)override;

    void mousePressEvent(QGraphicsSceneMouseEvent *event)override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event)override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event)override;
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)override;
};

#endif // VERTICALTRACK_H
