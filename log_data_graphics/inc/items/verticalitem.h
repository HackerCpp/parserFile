#ifndef VERTICALITEM_H
#define VERTICALITEM_H
#include "agraphicitem.h"

class VerticalItem : public AGraphicItem
{
public:
    VerticalItem(ICurve *curve,BoardForTrack *board);
    VerticalItem(const VerticalItem &other);

    virtual ~VerticalItem()override{}


    void drawHeader(QPainter *per,int &position,bool *flag)override;
    void drawLegend(QPainter *per,int &position,QPointF pointStarting,QPointF pointCurrent,bool *flag)override;
    bool isClickHeaderArea(QPoint pos)override;


    //virtual void paint(QPainter *per,QPainter *perHead,QRect rect,bool *flag)override{}
};

#endif // VERTICALITEM_H
