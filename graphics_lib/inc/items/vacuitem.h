#ifndef VACUITEM_H
#define VACUITEM_H
#include "verticalitem.h"
#include "AcuItem.h"
#include "cairo.h"

class VAcuItem : public VerticalItem{
    qreal m_scale,m_leftShift;

    void inline drawInterpolationVertical(QPainter *per,QRectF visibleRect,bool *flag);
    void inline drawInterpolationHorizontal(QPainter *per,QRectF visibleRect,bool *flag);

    virtual void drawBody(QPainter *per,QRectF visibleRect,bool *flag)override;

public:
    VAcuItem(AItem *itemInfo,ICurve *curve,BoardForTrack *board);
    ~VAcuItem(){}

};

#endif // VACUITEM_H
