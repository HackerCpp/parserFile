#ifndef VERTICALITEM_H
#define VERTICALITEM_H
#include "agraphicitem.h"

class VerticalItem : public AGraphicItem
{
public:
    VerticalItem(AItem *itemInfo,ICurve *curve);
    ~VerticalItem();
};

#endif // VERTICALITEM_H
