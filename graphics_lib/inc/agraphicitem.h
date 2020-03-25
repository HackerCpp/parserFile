#ifndef AGRAPHICITEM_H
#define AGRAPHICITEM_H
#include "aitem.h"
#include "icurve.h"

class AGraphicItem
{

protected:

public:
    static AGraphicItem *createItem(AItem *itemInfo,ICurve *curve);
    AGraphicItem(AItem *itemInfo,ICurve *curve);
    ~AGraphicItem();
};

#endif // AGRAPHICITEM_H
