#ifndef VMARKITEM_H
#define VMARKITEM_H
#include "verticalitem.h"
#include "markItem.h"

class VMarkItem : public VerticalItem{

public:
    VMarkItem(AItem *itemInfo,ICurve *curve,BoardForTrack *board);
    ~VMarkItem(){}

    //void paint(QPainter *per,QPainter *perHead,QRect rect,bool *flag)override;
};

#endif // VMARKITEM_H
