#include "vmarkitem.h"

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
    m_curve->load();
    qreal f_width = per->device()->width();
    int f_height = per->device()->height();
    QColor f_color = QColor(f_markItemInfo->color());

    QPen f_pen(f_color);
    int f_widthLine = static_cast<int>(m_isActive ? f_markItemInfo->widthLine() + 4 : f_markItemInfo->widthLine());
    f_pen.setWidth(f_widthLine);
    uint indexBegin  = 0;
    int f_yTop = visibleRect.y();
    int f_topOffset = m_board->offsetUp();
    int f_downOffset = f_height - f_topOffset;
    per->setPen(f_pen);

    for(uint i = 0; i < currentMainValue()->size(); ++i){
       if(mainValue(i) > f_yTop - f_topOffset && mainValue(i) < f_yTop + f_downOffset){
           indexBegin = i;
           break;
       }
    }

    uint i = 0;
    qreal f_multiplierWidth = f_width/3;
    for(i = indexBegin;i < currentMainValue()->size(); i++){
        if(*flag)
            return;
        if(static_cast<int>(m_curve->data(i)) == 0){
            continue;
        }
        else if(static_cast<int>(m_curve->data(i)) == 1){
            per->drawLine(QPointF(f_multiplierWidth,mainValue(i) - f_yTop + f_topOffset),QPointF(f_width,mainValue(i) - f_yTop + f_topOffset));
        }
        else if(static_cast<int>(m_curve->data(i)) == 2){
            per->drawLine(QPointF(2 * f_multiplierWidth,mainValue(i) - f_yTop + f_topOffset),QPointF(f_width,mainValue(i) - f_yTop + f_topOffset));
        }
        else{
            per->drawLine(QPointF(0,mainValue(i) - f_yTop + f_topOffset),QPointF(f_width,mainValue(i) - f_yTop + f_topOffset));
        }

        if(mainValue(i) > f_yTop + f_downOffset || mainValue(i) < f_yTop - f_topOffset){
            break;
        }
    }
    m_curve->unload();
}

void VMarkItem::drawHeader(QPainter *per,int &position,bool *flag){
    Q_UNUSED(flag)
    markItem *f_markItemInfo = dynamic_cast<markItem*>(m_itemInfo);
    m_positionHeaderArea = position;
    if(!f_markItemInfo){
        qDebug() << "m_itemInfo не переводится в f_markItemInfo не получается нарисовать";
        return;
    }
    QColor f_color = f_markItemInfo->color();
    int f_widthLine = m_isActive ? f_markItemInfo->widthLine() + 4 : f_markItemInfo->widthLine();
    per->setPen(QPen(f_color,f_widthLine));
    int f_fontSize = m_isActive ? 14 : 10;
    per->setFont(QFont("Times", f_fontSize, QFont::Bold));
    int f_width = per->device()->width();
    per->setBrush(QBrush(QColor(255,255,255,200)));
    per->drawRect(1,position,f_width - 2,m_heightHeaderArea);
    per->drawText(QRect(1,position,f_width - 2,m_heightHeaderArea),Qt::AlignHCenter|Qt::AlignVCenter,m_curve->mnemonic());
    position += m_heightHeaderArea;
}

bool VMarkItem::isLocatedInTheArea(QRectF area,QRectF visibleRect,QPainter *per){
    if(!m_itemInfo->visible(AItem::BOARD_GRAPH_VIEW)){
        return false;
    }
    QImage *img = dynamic_cast<QImage *>(per->device());
    if(!img){
        qDebug() << "Невозможно проверить картинка для проверки не найдена";
        return false;
    }
    img->fill(0xffffffff);
    bool flag = false;
    drawBody(per,visibleRect,&flag);
    for(int i = static_cast<int>(area.left()); i < area.right();++i){
        for(int j = static_cast<int>(area.top()); j < area.bottom();++j){
            if(img->pixel(i,j) != 4294967295){
                return true;
            }
        }
    }
    return false;
}

QColor VMarkItem::color(){
    markItem *f_markItemInfo = dynamic_cast<markItem*>(m_itemInfo);
    return (f_markItemInfo ? QColor(f_markItemInfo->color()) : Qt::black);
}

void VMarkItem::setColor(QColor color){
    markItem *f_markItemInfo = dynamic_cast<markItem*>(m_itemInfo);
    if(f_markItemInfo)
        f_markItemInfo->setColor(color.name(),f_markItemInfo->isDashes());
}
