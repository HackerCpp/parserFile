#ifndef AGRAPHICITEM_H
#define AGRAPHICITEM_H
#include "aitem.h"
#include "icurve.h"
#include <QPainter>
#include "boardfortrack.h"

class AGraphicItem
{

protected:
    AItem *m_itemInfo;
    ICurve *m_curve;
    BoardForTrack *m_board;

    virtual void drawBody(QPainter *per,QRect visibleRect,bool *flag){}
    virtual void drawHeader(QPainter *per,int &position,bool *flag){}

public:
    AGraphicItem(ICurve *curve,BoardForTrack *board);
    ~AGraphicItem();

    qreal topValue();
    qreal bottomValue();

    virtual void paint(QPainter *per,QPainter *perHead,QRect visibleRect,int &position,bool *flag);
};

#endif // AGRAPHICITEM_H
