#ifndef ITEMCREATER_H
#define ITEMCREATER_H
#include "aitem.h"
#include "icurve.h"


class ItemInfoCreater
{
public:
    ItemInfoCreater();
    ~ItemInfoCreater();
    static AItem *CreateItemInfo(ICurve *curve);
};

#endif // ITEMCREATER_H
