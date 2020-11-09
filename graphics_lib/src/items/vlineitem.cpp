#include "vlineitem.h"

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

VLineItem::VLineItem(const VLineItem &other)
    :VerticalItem(other){
    m_scale = other.m_scale;
    m_offsetPix = other.m_offsetPix;
    LineItem *f_linetemInfo = dynamic_cast<LineItem *>(other.m_itemInfo);
    if(f_linetemInfo)
        m_itemInfo = new LineItem(*f_linetemInfo);
    else{
        qDebug() << "VAcuItem::VAcuItem copy constructor VAcuItem AcuItem info not found";
        m_itemInfo = nullptr;
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
        m_offsetPix = (f_lineItemInfo->zeroOffset()/10) * f_pixelPerMM;
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
    if(!currentMainValue() || !m_itemInfo || !per || !m_board){
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
    m_curve->load();
    QPen f_pen(QColor(f_lineItemInfo->color()),
               (m_isActive ? f_lineItemInfo->widthLine() + 4 : f_lineItemInfo->widthLine()));

    per->setPen(f_pen);
    int f_width = per->device()->width();
    int f_height = per->device()->height();
    int f_yTop = visibleRect.y();
    int f_topOffset = m_board->offsetUp();
    int f_downOffset = f_height - f_topOffset;
    int indexBegin  = 0;

    if(mainValueMinimum() > f_yTop  + f_downOffset || mainValueMaximum() < f_yTop - f_topOffset){
        m_curve->unload();
        return;
    }

    for(uint i = 0; i < currentMainValue()->size(); ++i){
       if(mainValue(i) > f_yTop - f_topOffset && mainValue(i) < f_yTop + f_downOffset){
           indexBegin = i;
           break;
       }
    }
    uint i = 0;
    if(currentMainValue()->size() > m_curve->size()){
        qDebug() << "size mainValue > m_curve  VLineItem::drawBody" << currentMainValue()->size() << m_curve->size() ;
        m_curve->unload();
        return;
    }

    QPointF prevPoint = QPointF(pixelX(indexBegin,f_width),mainValue(indexBegin) - f_yTop + f_topOffset - 1);
    for(i = indexBegin + 1;i < currentMainValue()->size(); ++i){
        if(*flag){
            m_curve->unload();
            return;
        }
        VLineItem::Transition f_transition = amountSaturation(i,f_width);
        if(f_transition == RIGHT_TRANSITION ){
            per->drawLine(prevPoint,QPointF(f_width,mainValue(i) - f_yTop + f_topOffset));
            per->drawLine(QPointF(0,mainValue(i) - f_yTop + f_topOffset),QPointF(pixelX(i,f_width),mainValue(i) - f_yTop + f_topOffset));
        }
        else if(f_transition == LEFT_TRANSITION){
            per->drawLine(prevPoint,QPointF(0,mainValue(i) - f_yTop + f_topOffset));
            per->drawLine(QPointF(f_width,mainValue(i) - f_yTop + f_topOffset),QPointF(pixelX(i,f_width),mainValue(i) - f_yTop + f_topOffset));
        }
        else{
            per->drawLine(prevPoint,QPointF(pixelX(i,f_width),mainValue(i) - f_yTop + f_topOffset));
        }

        prevPoint = QPointF(pixelX(i,f_width),(mainValue(i) - f_yTop) + f_topOffset);
        if(mainValue(i) > f_yTop + f_downOffset || mainValue(i) < f_yTop - f_topOffset){
            break;
        }
    }
    m_curve->unload();
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
    per->save();
    LineItem *f_lineItemInfo = dynamic_cast<LineItem*>(m_itemInfo);
    m_positionHeaderArea = position;
    if(!f_lineItemInfo){
        qDebug() << "m_itemInfo не переводится в m_lineItem не получается нарисовать";
        return;
    }
    per->setPen(QPen(QColor(f_lineItemInfo->color()),
                     m_isActive ? f_lineItemInfo->widthLine() + 4 : f_lineItemInfo->widthLine()));
    int f_fontSize = m_isActive ? 14 : 10;
    per->setFont(QFont("Times", f_fontSize, QFont::Bold));
    int f_width = per->device()->width();
    per->setBrush(QBrush(QColor(255,255,255,200)));
    per->drawRect(1,position,f_width - 2,m_heightHeaderArea);
    per->drawText(QRect(1,position,f_width - 2,m_heightHeaderArea),Qt::AlignHCenter|Qt::AlignVCenter,m_curve->mnemonic());
    position += m_heightHeaderArea;
    per->restore();
}

qreal VLineItem::operator[](int index){
    if(index < m_curve->size())
        return m_curve->data(index) * m_scale + m_offsetPix;
    else
        return 0;
}

qreal VLineItem::pixelX(int index,int width){
    if(index < m_curve->size()){
        qreal f_value = fmod(m_curve->data(index) * m_scale + m_offsetPix,width);
        //return f_value;
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


void VLineItem::updateParam(int pictureWidth){
    if(!m_curve || !m_board)
        return;
    if(!m_board->isDrawTime()){
        bool oka,okb,okc;
        oka = okb = okc = true;
        QString f_param = m_curve->desc()->param("shift_depth");
        QStringList f_list = f_param.split(":");
        m_modeCountedDepth = f_list[0].toInt();
        if(m_modeCountedDepth == 3){
            k_a = f_list[3].toDouble(&oka);
            k_b = f_list[2].toDouble(&okb);
            k_c = f_list[1].toDouble(&okc);
        }
        else if(m_modeCountedDepth == 2){
            k_a = f_list[2].toDouble(&oka);
            k_b = f_list[1].toDouble(&okb);
        }
        else if(m_modeCountedDepth == 1){
            k_b = f_list[1].toDouble(&okb);
        }
        if(!oka || !okb || !okc)
            m_modeCountedDepth = 0;
    }
    else
        m_modeCountedDepth = 0;
    /*bool ok;
    qreal f_scale = m_board->isDrawTime() ? m_curve->desc()->param("time_scale").replace(",",".").toDouble(&ok) :  m_curve->desc()->param("depth_scale").replace(",",".").toDouble(&ok);
    if(!ok || f_scale == 0)
        f_scale = 1;
    qreal f_offset = m_board->isDrawTime() ? m_curve->desc()->param("time_offset").replace(",",".").toDouble() :  m_curve->desc()->param("depth_offset").replace(",",".").toDouble();*/
    loadDrawingParam(pictureWidth);
    m_recordPointDepth = m_curve->recordPoint();
    m_currentMainValue = m_board->isDrawTime() ? m_curve->time() :  m_curve->depth();
    m_currentRecordPoint  = (m_board->isDrawTime() ? 0 : m_recordPointDepth);
    m_currentRecordPoint = qIsNaN(m_currentRecordPoint) ? 0 : m_currentRecordPoint;
    m_currentScaleMainValue = m_board->scale();
}
