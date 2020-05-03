#include "vlineitem.h"
#include "SFML/System.hpp"

VLineItem::VLineItem(AItem *itemInfo,ICurve *curve,BoardForTrack *board)
    :VerticalItem(curve,board)
{
    m_scale = 0.1;
    LineItem * f_lineitem = dynamic_cast<LineItem*>(itemInfo);
    if(f_lineitem)
        m_itemInfo = f_lineitem;
    else{
        qDebug() << "Не удалось преобразовать AItemInfo в LineItemInfo" << itemInfo->name() << itemInfo->type();
    }

}

VLineItem::Transition VLineItem::amountSaturation(uint curentIndex,int width){
    if(width && curentIndex < static_cast<uint>(m_curve->size()) && curentIndex > 0){
        qreal f_cur = ((m_curve->data(curentIndex) * m_scale) + m_offsetPix) / width;
        qreal f_prev = ((m_curve->data(curentIndex - 1) * m_scale) + m_offsetPix) / width;
        f_cur += (f_cur > 0 ? 1 : -1);
        f_prev += (f_prev > 0 ? 1 : -1);
        if((int)f_cur > (int)f_prev)
            return RIGHT_TRANSITION;
        else if((int)f_cur < (int)f_prev)
            return LEFT_TRANSITION;
    }
    return NO_TRANSITION;
}

void VLineItem::loadDrawingParam(int width){
    LineItem *f_lineItemInfo = dynamic_cast<LineItem*>(m_itemInfo);
    if(!f_lineItemInfo){
        qDebug() << "m_itemInfo не переводится в m_lineItem не получается нарисовать";
        return;
    }
    qreal f_pixelPerMM = m_board->pixelPerMm();
    qreal f_pixelPerUnit;
    if(!f_lineItemInfo->isBeginValue()){
        m_offsetPix = (f_lineItemInfo->zeroOffset()/10) * m_board->pixelPerMm();
        if(f_lineItemInfo->isEndValue()){
            qreal rightBorderUnit = f_lineItemInfo->endValue();
            f_pixelPerUnit = (width -  m_offsetPix) / rightBorderUnit;
        }
        else {
            qreal f_scale = f_lineItemInfo->scale();
            f_pixelPerUnit  = f_scale * f_pixelPerMM;
        }
    }
    else{
        qreal leftBorderUnit = f_lineItemInfo->beginValue()/10;
        if(f_lineItemInfo->isEndValue()){
            qreal rightBorderUnit = f_lineItemInfo->endValue();
            f_pixelPerUnit = width / (rightBorderUnit - leftBorderUnit);
        }
        else{
            qreal f_scale = f_lineItemInfo->scale();
            f_pixelPerUnit  = f_scale * f_pixelPerMM;
        }
        m_offsetPix = -leftBorderUnit * f_pixelPerUnit;
    }
    m_scale = f_pixelPerUnit;
}

void VLineItem::drawBody(QPainter *per,QRectF visibleRect,bool *flag){
    //sf::Clock f_clock;
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
    loadDrawingParam(f_width);
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
        VLineItem::Transition f_transition = amountSaturation(i,f_width);
        if(f_transition == RIGHT_TRANSITION ){
            per->drawLine(prevPoint,QPointF(f_width,(f_mainValue->data(i) * f_scaleForMainValue) - f_yTop + f_topOffset));
            per->drawLine(QPointF(0,(f_mainValue->data(i) * f_scaleForMainValue) - f_yTop + f_topOffset),QPointF(pixelX(i,f_width),(f_mainValue->data(i)*f_scaleForMainValue) - f_yTop + f_topOffset));
            per->drawText(QPointF(50,(f_mainValue->data(i) * f_scaleForMainValue) - f_yTop + f_topOffset),QString::number(f_mainValue->data(i)));
        }
        else if(f_transition == LEFT_TRANSITION){
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
    //qDebug() << f_clock.getElapsedTime().asMicroseconds();
}

QColor VLineItem::color(){
    LineItem *f_lineItemInfo = dynamic_cast<LineItem*>(m_itemInfo);
    return (f_lineItemInfo ? QColor(f_lineItemInfo->color()) : Qt::black);
}

void VLineItem::setColor(QColor color){
    LineItem *f_lineItemInfo = dynamic_cast<LineItem*>(m_itemInfo);
    if(f_lineItemInfo)
        f_lineItemInfo->setColor(color.name(),f_lineItemInfo->isDashes());
}

void VLineItem::drawHeader(QPainter *per,int &position,bool *flag){
    Q_UNUSED(flag)
    LineItem *f_lineItemInfo = dynamic_cast<LineItem*>(m_itemInfo);
    m_positionHeaderArea = position;
    if(!f_lineItemInfo){
        qDebug() << "m_itemInfo не переводится в m_lineItem не получается нарисовать";
        return;
    }
    QColor f_color = f_lineItemInfo->color();
    int f_widthLine = m_isActive ? f_lineItemInfo->widthLine() + 4 : f_lineItemInfo->widthLine();
    per->setPen(QPen(f_color,f_widthLine));
    int f_fontSize = m_isActive ? 14 : 10;
    per->setFont(QFont("Times", f_fontSize, QFont::Bold));
    int f_width = per->device()->width();
    per->setBrush(QBrush(QColor(255,255,255,200)));
    per->drawRect(1,position,f_width - 2,m_heightHeaderArea);
    per->drawText(QRect(1,position,f_width - 2,m_heightHeaderArea),Qt::AlignHCenter|Qt::AlignVCenter,m_curve->mnemonic());
    position += m_heightHeaderArea;
}

qreal VLineItem::operator[](int index){
    if(index < m_curve->size())
        return m_curve->data(index) * m_scale + m_offsetPix;
    else
        return 0;
}

qreal VLineItem::pixelX(int index,int width){
    if(index < m_curve->size()){
        qreal f_value = fmod((m_curve->data(index) * m_scale) + m_offsetPix,width);
        return f_value > 0 ? f_value : width + f_value;
    }
    else
        return 0;
}

bool VLineItem::isLocatedInTheArea(QRectF area,QRectF visibleRect,QPainter *per){
    if(!m_itemInfo->visible(AItem::BOARD_GRAPH_VIEW)){
        return false;
    }
    QImage *img = dynamic_cast<QImage*>(per->device());
    if(!img){
        qDebug() << "Невозможно проверить картинка для проверки не найдена";
        return false;
    }
    img->fill(0xffffffff);
    bool flag = false;
    drawBody(per,visibleRect,&flag);
    for(int i = area.left(); i < area.right();++i){
        for(int j = area.top(); j < area.bottom();++j){
            if(img->pixel(i,j) != 4294967295){
                return true;
            }
        }
    }
    return false;
}



