#include "verticalitem.h"

VerticalItem::VerticalItem(ICurve *curve,BoardForTrack *board)
    : AGraphicItem(curve,board)
{
    m_heightHeaderArea = 40;

}

void VerticalItem::drawHeader(QPainter *per,int &position,bool *flag){
    Q_UNUSED(flag)
    per->save();
    m_positionHeaderArea = position;
    int f_width = per->device()->width();
    per->setBrush(QBrush(QColor(255,255,255,200)));
    per->drawRect(1,position,f_width - 2,m_heightHeaderArea);
    per->drawText(QRect(1,position,f_width - 2,m_heightHeaderArea),Qt::AlignHCenter|Qt::AlignVCenter,m_curve->mnemonic());
    position += m_heightHeaderArea;
    per->restore();
}

bool VerticalItem::isClickHeaderArea(QPoint pos){
    if(!m_itemInfo->visible(AItem::BOARD_GRAPH_VIEW)){
        return false;
    }
    if(pos.y() > m_positionHeaderArea && pos.y() < m_positionHeaderArea + m_heightHeaderArea)
        return true;
    return false;
}
