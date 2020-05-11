#include "itimscreater.h"
#include "vlineitem.h"
#include "vacuitem.h"
#include "vmarkitem.h"
#include "vspectritem.h"

AGraphicItem *ItimsCreater::createItem(AItem *itemInfo,ICurve *curve,BoardForTrack *board,OrientationItem orientation){
    TypeItem f_type = itemInfo->type();
    AGraphicItem *f_item = nullptr;
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
            case TypeItem::SPEC :{
                f_item = new VSpectrItem(itemInfo,curve,board);
                break;
            }
            default :{
                qDebug() << "Не описанный тип Item:" << f_type;
            }
        }

    }

    return f_item;
}
