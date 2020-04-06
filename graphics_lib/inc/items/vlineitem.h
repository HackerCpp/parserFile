#ifndef VLINEITEM_H
#define VLINEITEM_H
#include "verticalitem.h"
#include "LineItem.h"

class VLineItem : public VerticalItem
{
    qreal m_scale,m_leftShift;

    virtual void drawBody(QPainter *per,QRect visibleRect,bool *flag)override;
    virtual void drawHeader(QPainter *per,int &position,bool *flag)override;

    uint amountSaturation(uint index,uint width);
    qreal operator[](int index);
    qreal pixelX(int index,int width);
public:
    VLineItem(AItem *itemInfo,ICurve *curve,BoardForTrack *board);
    ~VLineItem(){}


};

#endif // VLINEITEM_H
