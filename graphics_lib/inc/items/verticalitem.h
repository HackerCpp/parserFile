#ifndef VERTICALITEM_H
#define VERTICALITEM_H
#include "agraphicitem.h"

class VerticalItem : public AGraphicItem
{
public:
    VerticalItem(ICurve *curve,BoardForTrack *board);
    ~VerticalItem(){}

    //virtual void paint(QPainter *per,QPainter *perHead,QRect rect,bool *flag)override{}
};

#endif // VERTICALITEM_H
