#include "agraphicitem.h"
#include "verticalitem.h"

AGraphicItem::AGraphicItem(ICurve *curve,BoardForTrack *board)
    : m_curve(curve), m_board(board)
{
    m_isActive = false;
    m_positionHeaderArea = 0;
    m_heightHeaderArea = 20;
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


void AGraphicItem::paint(QPainter *per,QPainter *perHead,QRectF visibleRect,
                         int &position,bool *flag){
    /*if(m_itemInfo->visible(AItem::BOARD_LEGEND_VIEW)){

    }*/

    if(m_itemInfo->visible(AItem::BOARD_GRAPH_VIEW)){
        drawHeader(perHead,position,flag);
        drawBody(per,visibleRect,flag);
    }
}

