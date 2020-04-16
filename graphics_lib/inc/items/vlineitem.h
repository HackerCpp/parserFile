#ifndef VLINEITEM_H
#define VLINEITEM_H
#include "verticalitem.h"
#include "LineItem.h"

class VLineItem : public VerticalItem{
    qreal m_scale,m_leftShift;

    virtual void drawBody(QPainter *per,QRectF visibleRect,bool *flag)override;
    void drawHeader(QPainter *per,int &position,bool *flag)override;

    uint amountSaturation(uint index,uint width);
    qreal operator[](int index);
    qreal pixelX(int index,int width);

    virtual bool isLocatedInTheArea(QRectF area,QRectF visibleRect,QPainter *per)override;
    virtual void run()override{}
public:
    VLineItem(AItem *itemInfo,ICurve *curve,BoardForTrack *board);
    ~VLineItem(){}


};

#endif // VLINEITEM_H
