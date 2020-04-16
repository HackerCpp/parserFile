#include "verticalitem.h"

VerticalItem::VerticalItem(ICurve *curve,BoardForTrack *board)
    : AGraphicItem(curve,board)
{

}

void VerticalItem::drawHeader(QPainter *per,int &position,bool *flag){
    int f_width = per->device()->width();
    per->setBrush(QBrush(QColor(255,255,255,200)));
    per->drawRect(1,position,f_width - 2,40);
    per->drawText(QRect(1,position,f_width - 2,40),Qt::AlignHCenter|Qt::AlignVCenter,m_curve->mnemonic());
    position += 40;
}
