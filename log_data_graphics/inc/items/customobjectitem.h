#ifndef CUSTOMOBJECTITEM_H
#define CUSTOMOBJECTITEM_H

#include "verticalitem.h"
#include "customobjectiteminfo.h"


class CustomObjectItem : public VerticalItem{
    CustomObjectItemInfo *m_objectInfo;

public:
    CustomObjectItem(CustomObjectItemInfo *objectInfo,CustomObject *object, BoardForTrack *board);
    ~CustomObjectItem(){}

    void drawBody(QPainter *per,QRectF visibleRect,bool *flag)override;
    void drawHeader(QPainter *per,int &position,bool *flag)override;
};



#endif // CUSTOMOBJECTITEM_H
