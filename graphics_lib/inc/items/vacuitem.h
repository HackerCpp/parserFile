#ifndef VACUITEM_H
#define VACUITEM_H
#include "verticalitem.h"
#include "AcuItem.h"

class VAcuItem : public VerticalItem{

public:
    VAcuItem(AItem *itemInfo,ICurve *curve,BoardForTrack *board);
    ~VAcuItem(){}

     //void paint(QPainter *per,QPainter *perHead,QRect rect,bool *flag)override;
};

#endif // VACUITEM_H
