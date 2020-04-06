#include "vmarkitem.h"

VMarkItem::VMarkItem(AItem *itemInfo,ICurve *curve,BoardForTrack *board)
    :VerticalItem(curve,board)
{
    markItem * f_markitem = dynamic_cast<markItem*>(itemInfo);
    if(f_markitem)
        m_itemInfo = f_markitem;
    else{
        qDebug() << "Не удалось преобразовать AItemInfo в MarkItemInfo" << itemInfo->name();
    }
}

/*void VMarkItem::paint(QPainter *per,QPainter *perHead,QRect rect,bool *flag){

}*/
