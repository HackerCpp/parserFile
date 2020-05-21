#include "vmarkitem.h"
#include "SFML/System.hpp"


VMarkItem::VMarkItem(AItem *itemInfo,ICurve *curve,BoardForTrack *board)
    :VerticalItem(curve,board)
{
    markItem * f_markitem = dynamic_cast<markItem*>(itemInfo);
    if(f_markitem)
        m_itemInfo = f_markitem;
    else{
        qDebug() << "Не удалось преобразовать AItemInfo в MarkItemInfo" << itemInfo->name();
    }
}

void VMarkItem::drawBody(QPainter *per,QRectF visibleRect,bool *flag){

        if(!m_itemInfo || !per || !m_board){
            qDebug() << "MarkItemInfo = nullptr или painter = nullptr m_board = null Не удаётся нарисовать кривую";
            return;
        }
        if(!m_curve){
            qDebug() << "Нулевой указатель mCurve";
            return;
        }

        markItem *f_markItemInfo = dynamic_cast<markItem*>(m_itemInfo);
        if(!f_markItemInfo){
            qDebug() << "m_itemInfo не переводится в m_markItem не получается нарисовать";
            return;
        }
    qreal f_width = per->device()->width();
    int f_height = per->device()->height();
    QColor f_color = QColor(f_markItemInfo->color());

    QPen f_pen(f_color);
    int f_widthLine = f_markItemInfo->widthLine() + 4;
    f_pen.setWidth(f_widthLine);
    int indexBegin  = 0;
     qreal f_scaleForMainValue = m_board->scale();
     int f_yTop = visibleRect.y();
     int f_topOffset = m_board->offsetUp();
     int f_downOffset = f_height - f_topOffset;
    per->setFont(QFont("Times", 10, QFont::Bold));
    per->setPen(f_pen);

    ICurve *f_mainValue = m_board->isDrawTime() ? m_curve->time() :  m_curve->depth();
    for(uint i = 0; i < m_curve->size(); ++i){
       if((m_curve->data(i) * f_scaleForMainValue) > f_yTop - f_topOffset && (m_curve->data(i) * f_scaleForMainValue) < f_yTop + f_downOffset){
           indexBegin = i;// > 2?i - 2 : 0;
           break;
       }
    }
    uint i=0;
    qreal multiplierWidth = f_width/3;
    for(i = indexBegin+1;i <f_mainValue->size(); i++){
        if(*flag)
            return;

            if(m_curve->data(i) ==1)
            {
                per->drawLine(QPointF(multiplierWidth,f_mainValue->data(i)*f_scaleForMainValue- f_yTop + f_topOffset),QPointF(f_width,f_mainValue->data(i)*f_scaleForMainValue- f_yTop + f_topOffset));


            }
            else if(m_curve->data(i)==2)
            {
                per->drawLine(QPointF(2*multiplierWidth,f_mainValue->data(i)*f_scaleForMainValue- f_yTop + f_topOffset),QPointF(f_width,f_mainValue->data(i)*f_scaleForMainValue- f_yTop + f_topOffset));


            }

    }



}
