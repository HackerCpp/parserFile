#include "customobjectitem.h"



CustomObjectItem::CustomObjectItem(CustomObjectItemInfo *objectInfo,CustomObject *object, BoardForTrack *board):
    VerticalItem(object,board)
{
    Q_UNUSED(objectInfo)

}


void CustomObjectItem::drawBody(QPainter *per,QRectF visibleRect,bool *flag){
    Q_UNUSED(per)Q_UNUSED(visibleRect)Q_UNUSED(flag)

}

void CustomObjectItem::drawHeader(QPainter *per,int &position,bool *flag){
    Q_UNUSED(per)Q_UNUSED(position)Q_UNUSED(flag)
}
