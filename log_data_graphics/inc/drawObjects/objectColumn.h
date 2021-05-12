#ifndef DRAW_OBJECT
#define DRAW_OBJECT
#include "customobjectitem.h"

class ObjectColumn : public CustomObjectItem{

    void createDrawObject(CustomObject *object,QString name);

public:
    ObjectColumn(CustomObjectItemInfo *objectInfo,CustomObject *object, BoardForTrack *board,QString name);
    ~ObjectColumn(){}

};


#endif
