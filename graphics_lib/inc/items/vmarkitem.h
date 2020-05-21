#ifndef VMARKITEM_H
#define VMARKITEM_H
#include "verticalitem.h"
#include "markItem.h"

class VMarkItem : public VerticalItem{
        virtual void drawBody(QPainter *per,QRectF visibleRect,bool *flag)override;



public:
    VMarkItem(AItem *itemInfo,ICurve *curve,BoardForTrack *board);
    ~VMarkItem(){}




};

#endif // VMARKITEM_H
