#include "agraphicitem.h"
#include "verticalitem.h"

AGraphicItem *AGraphicItem::createItem(AItem *itemInfo,ICurve *curve){
    return new VerticalItem(itemInfo,curve);
}


AGraphicItem::AGraphicItem(AItem *itemInfo,ICurve *curve)
{

}

AGraphicItem::~AGraphicItem(){

}


