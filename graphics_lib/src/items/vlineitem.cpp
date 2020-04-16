#include "vlineitem.h"

VLineItem::VLineItem(AItem *itemInfo,ICurve *curve,BoardForTrack *board)
    :VerticalItem(curve,board)
{
    m_scale = 0.1;
    LineItem * f_lineitem = dynamic_cast<LineItem*>(itemInfo);
    if(f_lineitem)
        m_itemInfo = f_lineitem;
    else{
        qDebug() << "Не удалось преобразовать AItemInfo в LineItemInfo" << itemInfo->name() << itemInfo->Type();
    }

}
uint VLineItem::amountSaturation(uint index,uint width){
    if(width && index < static_cast<uint>(m_curve->size()))
        return static_cast<uint>((m_curve->data(index) * m_scale)/width);
    return 0;
}

void VLineItem::drawBody(QPainter *per,QRectF visibleRect,bool *flag){
    if(!m_itemInfo || !per || !m_board){
        qDebug() << "LineItemInfo = nullptr или painter = nullptr m_board = null Не удаётся нарисовать кривую";
        return;
    }
    if(!m_curve){
        qDebug() << "Нулевой указатель mCurve";
        return;
    }
    LineItem *f_lineItemInfo = dynamic_cast<LineItem*>(m_itemInfo);
    if(!f_lineItemInfo){
        qDebug() << "m_itemInfo не переводится в m_lineItem не получается нарисовать";
        return;
    }
    QColor f_color = QColor(f_lineItemInfo->color());
    QPen f_pen(f_color);
    int f_widthLine = m_isActive ? f_lineItemInfo->widthLine() + 4 : f_lineItemInfo->widthLine();
    f_pen.setWidth(f_widthLine);
    per->setPen(f_pen);
    int f_width = per->device()->width();
    int f_height = per->device()->height();
    ICurve *f_mainValue = m_board->isDrawTime() ? m_curve->time() :  m_curve->depth();
    int f_yTop = visibleRect.y();
    int f_topOffset = m_board->offsetUp();
    int f_downOffset = f_height - f_topOffset;
    int indexBegin  = 0;
    qreal f_scaleForMainValue = m_board->scale();
    if((f_mainValue->minimum() * f_scaleForMainValue) > f_yTop  + f_downOffset || (f_mainValue->maximum() * f_scaleForMainValue) < f_yTop - f_topOffset){
        return;
    }
    for(uint i = 0; i < f_mainValue->size(); ++i){
       if((f_mainValue->data(i) * f_scaleForMainValue) > f_yTop - f_topOffset && (f_mainValue->data(i) * f_scaleForMainValue) < f_yTop + f_downOffset){
           indexBegin = i;// > 2?i - 2 : 0;
           break;
       }
    }
    uint i = 0;
    uint prevIndex = 0;
    if(f_mainValue->size() > m_curve->size()){
        qDebug() << "size mainValue > m_curve";
        return;
    }
    QPointF prevPoint = QPointF(pixelX(indexBegin,f_width),(f_mainValue->data(indexBegin) * f_scaleForMainValue) - f_yTop + f_topOffset - 1);
    for(i = indexBegin + 1;i < f_mainValue->size(); ++i){
        if(*flag)
            return;
        if(amountSaturation(i,f_width) > amountSaturation(prevIndex,f_width)){
            per->drawLine(prevPoint,QPointF(f_width,(f_mainValue->data(i) * f_scaleForMainValue) - f_yTop + f_topOffset));
            per->drawLine(QPointF(0,(f_mainValue->data(i) * f_scaleForMainValue) - f_yTop + f_topOffset),QPointF(pixelX(i,f_width),(f_mainValue->data(i)*f_scaleForMainValue) - f_yTop + f_topOffset));
            per->drawText(QPointF(50,(f_mainValue->data(i) * f_scaleForMainValue) - f_yTop + f_topOffset),QString::number(f_mainValue->data(i)));
        }
        else if(amountSaturation(i,f_width) < amountSaturation(prevIndex,f_width)){
            per->drawLine(prevPoint,QPointF(0,(f_mainValue->data(i) * f_scaleForMainValue) - f_yTop + f_topOffset));
            per->drawLine(QPointF(f_width,(f_mainValue->data(i) * f_scaleForMainValue) - f_yTop + f_topOffset),QPointF(pixelX(i,f_width),(f_mainValue->data(i)*f_scaleForMainValue) - f_yTop + f_topOffset));
        }
        else{
            per->drawLine(prevPoint,QPointF(pixelX(i,f_width),(f_mainValue->data(i) * f_scaleForMainValue) - f_yTop + f_topOffset));
            //per->drawText(QPointF(pixelX(i,f_width) + 50,(f_mainValue->data(i)*f_scaleForMainValue) - f_yTop + f_topOffset),QString::number(m_curve->data(i)));
        }

        prevPoint = QPointF(pixelX(i,f_width),((f_mainValue->data(i)*f_scaleForMainValue) - f_yTop) + f_topOffset);
        prevIndex = i;
        if((f_mainValue->data(i) * f_scaleForMainValue) > f_yTop + f_downOffset || (f_mainValue->data(i) * f_scaleForMainValue) < f_yTop - f_topOffset){
            break;
        }
    }
}

void VLineItem::drawHeader(QPainter *per,int &position,bool *flag){
    LineItem *f_lineItemInfo = dynamic_cast<LineItem*>(m_itemInfo);
    if(!f_lineItemInfo){
        qDebug() << "m_itemInfo не переводится в m_lineItem не получается нарисовать";
        return;
    }
    QColor f_color = f_lineItemInfo->color();
    per->setPen(QPen(f_color,f_lineItemInfo->widthLine()));
    per->setFont(QFont("Times", 10, QFont::Bold));
    int f_width = per->device()->width();
    per->setBrush(QBrush(QColor(255,255,255,200)));
    per->drawRect(1,position,f_width - 2,40);
    per->drawText(QRect(1,position,f_width - 2,40),Qt::AlignHCenter|Qt::AlignVCenter,m_curve->mnemonic());
    position += 40;
}

qreal VLineItem::operator[](int index){
    if(index < m_curve->size())
        return m_curve->data(index) * m_scale;
    else
        return 0;
}

qreal VLineItem::pixelX(int index,int width){
    if(index < m_curve->size())
        return fmod(m_curve->data(index) * m_scale,width);
    else
        return 0;
}

bool VLineItem::isLocatedInTheArea(QRectF area,QRectF visibleRect,QPainter *per){
    QImage *img = dynamic_cast<QImage*>(per->device());
    if(!img){
        qDebug() << "Невозможно проверить картинка для проверки не найдена";
        return false;
    }
    img->fill(0x0);
    bool flag = false;
    drawBody(per,visibleRect,&flag);
    for(int i = area.left(); i < area.right();++i){
        for(int j = area.top(); j < area.bottom();++j){
            if(img->pixel(i,j) != 4278190080){
                return true;
            }
        }
    }
    return false;
}



