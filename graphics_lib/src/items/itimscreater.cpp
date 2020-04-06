#include "itimscreater.h"
#include "verticalitem.h"
#include "vlineitem.h"
#include "vacuitem.h"
#include "vmarkitem.h"

AGraphicItem *ItimsCreater::createItem(AItem *itemInfo,ICurve *curve,BoardForTrack *board,OrientationItem orientation){
    TypeItem f_type = itemInfo->Type();
    AGraphicItem * f_item = nullptr;
    if(orientation == VERTICAL){
        switch(f_type){
            case TypeItem::LINE :{
                f_item = new VLineItem(itemInfo,curve,board);
                break;
            }
            case TypeItem::ACU :{
                f_item = new VAcuItem(itemInfo,curve,board);
                break;
            }
            case TypeItem::MARK :{
                f_item = new VMarkItem(itemInfo,curve,board);
                break;
            }
        }

    }
    if(!f_item){
        qDebug() << "Не описанный тип Item:" << f_type;
    }
    return f_item;
}
