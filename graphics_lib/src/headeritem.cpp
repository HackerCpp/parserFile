#include "headeritem.h"

HeaderItem::HeaderItem(ATrack *track)
    : m_track(track)
{


}

void HeaderItem::addIteam(AGraphicItem* item){
    if(!m_items || !item)
        return;
    if(item->itemInfo()->type() == ACU || item->itemInfo()->type() == SPEC)
        m_items->push_front(item);
    else
        m_items->push_back(item);
}


void HeaderItem::paint(QPainter *painter, const QStyleOptionGraphicsItem*, QWidget*){

}

void HeaderItem::toSetTheLocationOfTheImageAfterDrawing(){

}

void HeaderItem::run(){

}

void  HeaderItem::swapImageHeader(){

}
