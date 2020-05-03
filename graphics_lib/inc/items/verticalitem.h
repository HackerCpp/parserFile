#ifndef VERTICALITEM_H
#define VERTICALITEM_H
#include "agraphicitem.h"

class VerticalItem : public AGraphicItem
{
public:
    VerticalItem(ICurve *curve,BoardForTrack *board);
    ~VerticalItem(){}


    void drawHeader(QPainter *per,int &position,bool *flag)override;
    bool isClickHeaderArea(QPoint pos)override;

    //virtual void paint(QPainter *per,QPainter *perHead,QRect rect,bool *flag)override{}
};

#endif // VERTICALITEM_H
