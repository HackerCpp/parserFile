#include "agraphicitem.h"
#include "verticalitem.h"

AGraphicItem::AGraphicItem(ICurve *curve,BoardForTrack *board)
    : m_curve(curve), m_board(board)
{

}

AGraphicItem::~AGraphicItem(){

}
qreal AGraphicItem::topValue(){
    ICurve *f_mainValue = m_board->isDrawTime() ? m_curve->time() : m_curve->depth();
    return f_mainValue->minimum() * m_board->scale();
}

qreal AGraphicItem::bottomValue(){
    ICurve *f_mainValue = m_board->isDrawTime() ? m_curve->time() : m_curve->depth();
    return f_mainValue->maximum() * m_board->scale();
}

void AGraphicItem::paint(QPainter *per,QPainter *perHead,QRect visibleRect,
                         int &position,bool *flag){
    if(m_itemInfo->visible(AItem::BOARD_LEGEND_VIEW)){
        drawHeader(perHead,position,flag);
    }

    if(m_itemInfo->visible(AItem::BOARD_GRAPH_VIEW)){
        drawBody(per,visibleRect,flag);
    }
}


