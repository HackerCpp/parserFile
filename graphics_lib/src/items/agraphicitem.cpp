#include "agraphicitem.h"
#include "verticalitem.h"

AGraphicItem::AGraphicItem(ICurve *curve,BoardForTrack *board)
    : m_curve(curve), m_board(board)
{
    m_isActive = false;
    m_positionHeaderArea = 0;
    m_heightHeaderArea = 20;
    m_recordPointDepth = qIsNaN(curve->recordPoint()) ? 0 : curve->recordPoint();
}

AGraphicItem::AGraphicItem(const AGraphicItem &other){
    if(&other == this)
        return;
    m_itemInfo = nullptr;
    m_curve = ICurve::curveCreater(*other.m_curve);
    m_board = other.m_board;
    m_isActive = other.m_isActive;
    m_positionHeaderArea = other.m_positionHeaderArea;
    m_heightHeaderArea = other.m_heightHeaderArea;
    m_recordPointDepth = other.m_recordPointDepth;
}

AGraphicItem::~AGraphicItem(){
}

qreal AGraphicItem::topValue(){
    ICurve *f_mainValue = m_board->isDrawTime() ? m_curve->time() : m_curve->depth();
    qreal f_recordPoint = m_board->isDrawTime() ? 0 : (qIsNaN(m_curve->recordPoint()) ? 0 : m_curve->recordPoint()) * 1000;
    //qDebug() << f_mainValue->minimum() << f_recordPoint << (f_mainValue->minimum() + f_recordPoint) * m_board->scale() << m_curve->mnemonic();
    return (f_mainValue->minimum() + f_recordPoint) * m_board->scale();
}

qreal AGraphicItem::bottomValue(){
    ICurve *f_mainValue = m_board->isDrawTime() ? m_curve->time() : m_curve->depth();
    qreal f_recordPoint =  m_board->isDrawTime() ? 0 : (qIsNaN(m_curve->recordPoint()) ? 0 : m_curve->recordPoint()) * 1000;
    //qDebug() << f_mainValue->maximum() << f_recordPoint << (f_mainValue->maximum() + f_recordPoint) * m_board->scale() << m_curve->mnemonic();
    return (f_mainValue->maximum() + f_recordPoint) * m_board->scale();
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

