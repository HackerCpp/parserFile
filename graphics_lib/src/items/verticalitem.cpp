#include "verticalitem.h"

VerticalItem::VerticalItem(ICurve *curve,BoardForTrack *board)
    : AGraphicItem(curve,board)
{
    m_heightHeaderArea = 40;

}

VerticalItem::VerticalItem(CustomObject *object,BoardForTrack *board)
    : AGraphicItem(object,board)
{
    m_heightHeaderArea = 40;

}

VerticalItem::VerticalItem(const VerticalItem &other)
    :AGraphicItem(other){
    m_heightHeaderArea = other.m_heightHeaderArea;
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
void VerticalItem::drawLegend(QPainter *per,int &position,QPointF pointStarting,QPointF pointCurrent,bool *flag){
    Q_UNUSED(flag)
    if(!per || !per->isActive())
        return;
    if(!m_curve || !m_curve->size())
        return;
    per->save();
    int f_width = per->device()->width();
    per->setPen(QPen(color(),2));
    per->setFont(m_fontLegend);
    per->setBrush(QBrush(QColor(255,255,255,255)));
    per->drawRect(1,position,f_width - 2,m_heightLegend);
    QString f_textMnemonic = m_curve->mnemonic();
    int f_indexStartingMainValue = mainIndexFromScene(pointStarting);
    int f_indexCurrentMainValue = mainIndexFromScene(pointCurrent);
    if(f_indexStartingMainValue == -1 || f_indexCurrentMainValue == -1){
        per->restore();
        return;
    }
    QString f_textValue = QString::number(m_curve->data(f_indexStartingMainValue) * m_curve->sizeOffset()) + " " +
                          QString::number(m_curve->data(f_indexCurrentMainValue) * m_curve->sizeOffset());
    per->drawText(QRect(10,position,f_width - 2,m_heightLegend),Qt::AlignLeft|Qt::AlignVCenter,f_textMnemonic);
    per->drawText(QRect(0,position,f_width - 2,m_heightLegend),Qt::AlignRight|Qt::AlignVCenter,f_textValue);
    position += m_heightLegend;
    per->restore();
}

bool VerticalItem::isClickHeaderArea(QPoint pos){

    /*if(!m_itemInfo->visible(AItem::BOARD_GRAPH_VIEW)){
        return false;
    }*/
    if(!is_visible())
        return false;

    if(pos.y() > m_positionHeaderArea && pos.y() < m_positionHeaderArea + m_heightHeaderArea)
        return true;
    return false;
}
