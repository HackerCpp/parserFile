#ifndef VMARKITEM_H
#define VMARKITEM_H
#include "verticalitem.h"
#include "markItem.h"

class VMarkItem : public VerticalItem{
    void drawBody(QPainter *per,QRectF visibleRect,bool *flag)override;
    void drawHeader(QPainter *per,int &position,bool *flag)override;
    bool isLocatedInTheArea(QRectF area,QRectF visibleRect,QPainter *per)override;
public:
    VMarkItem(AItem *itemInfo,ICurve *curve,BoardForTrack *board);
    ~VMarkItem(){}

    QColor color()override;
    void setColor(QColor color)override;
};

#endif // VMARKITEM_H
