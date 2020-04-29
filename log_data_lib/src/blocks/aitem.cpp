#include "aitem.h"

AItem::AItem(){
    m_numberOfTrack = 1;
    m_begin.is_beginValue = false;
    m_begin.beginValue = 0;
    m_begin.zeroOffset = 0;
    m_end.is_endValue = false;
    m_end.endValue = 1000000;
    m_end.scale = 0.001;
    m_visible[VIEW_NUM] = MAXIMIM - 1;
    for(int visible = BOARD_GRAPH_VIEW;visible < MAXIMIM;++visible){
        m_visible[visible] = 1;
    }
}
AItem::~AItem(){

}

QString AItem::visible(){
    QString f_visible;
    for(int i = 0 ; i < VisibleView::MAXIMIM; ++i){
        f_visible.append(QString::number(m_visible[i]));
        if(i != VisibleView::MAXIMIM - 1)
            f_visible.append(":");
    }
    return f_visible;
}

void AItem::setBegin(bool isBegin,qreal begin,qreal zeroOffset){
    m_begin.is_beginValue = isBegin;
    m_begin.beginValue = begin;
    m_begin.zeroOffset = zeroOffset;
}

void AItem::setEnd(bool isEnd,qreal end,qreal scale){
    m_end.is_endValue = isEnd;
    m_end.endValue = end;
    m_end.scale = scale;
}

void AItem::setMultiScale(bool isMultiScale,qreal gleamCount,qreal gleamScale){
    m_multiScale.is_multiscale = isMultiScale;
    m_multiScale.gleamCount = gleamCount;
    m_multiScale.gleamScale = gleamScale;
}

void AItem::setName(QString name, QString visible){
    m_name = name;
    if(visible == nullptr)
        return;
    visible = visible.remove(":");
    m_visible[VisibleView::VIEW_NUM] = QString(visible[0]).toInt();
    if(m_visible[VisibleView::VIEW_NUM] != visible.size() - 1 ||
       m_visible[VisibleView::VIEW_NUM] != VisibleView::MAXIMIM - 1){
        qDebug() << "Информация о видимости item не корректная, флагов меньше  или больше чем в описании";
        qDebug() << m_visible[VisibleView::VIEW_NUM] << visible.size() - 1;
        return;
    }

    for(int i = 1 ; i < VisibleView::MAXIMIM; ++i){
        m_visible[i] = QString(visible[i]).toInt();
    }
}

void AItem::setVisible(VisibleView what,bool value){
    if(what > VisibleView::VIEW_NUM && what < VisibleView::MAXIMIM)
        m_visible[what] = value;
}

