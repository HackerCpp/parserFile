#include "objectColumn.h"



ObjectColumn::ObjectColumn(CustomObjectItemInfo *objectInfo,
                           CustomObject *object, BoardForTrack *board,QString name)
    :CustomObjectItem(objectInfo,object,board){
    if(!object)
        createDrawObject(m_drawObject, name);

}

void ObjectColumn::createDrawObject(CustomObject *object,QString name){
    object = new CustomObject();
    object->setName("DOColumn:" + name);


}
