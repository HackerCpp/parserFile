#include "vacuitem.h"

VAcuItem::VAcuItem(AItem *itemInfo,ICurve *curve,BoardForTrack *board)
    :VerticalItem(curve,board)
{
    AcuItem * f_acuitem = dynamic_cast<AcuItem*>(itemInfo);
    if(f_acuitem)
        m_itemInfo = f_acuitem;
    else{
        qDebug() << "Не удалось преобразовать AItemInfo в AcuItemInfo" << itemInfo->name();
    }
}

/*void VAcuItem::paint(QPainter *per,QPainter *perHead,QRect rect,bool *flag){

}*/
