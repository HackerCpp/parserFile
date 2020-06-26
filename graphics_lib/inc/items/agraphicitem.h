#ifndef AGRAPHICITEM_H
#define AGRAPHICITEM_H
#include "aitem.h"
#include "icurve.h"
#include <QPainter>
#include "boardfortrack.h"

class AGraphicItem
{
protected:
    AItem *m_itemInfo;
    ICurve *m_curve;
    BoardForTrack *m_board;
    bool m_isActive;
    int m_positionHeaderArea,m_heightHeaderArea;
    qreal m_recordPointDepth;

    virtual void drawBody(QPainter *per,QRectF visibleRect,bool *flag){Q_UNUSED(per) Q_UNUSED(visibleRect) Q_UNUSED(flag)}


public:
    AGraphicItem(ICurve *curve,BoardForTrack *board);
    AGraphicItem(const AGraphicItem &other);
    virtual ~AGraphicItem();

    qreal topValue();
    qreal bottomValue();

    virtual void drawHeader(QPainter *per,int &position,bool *flag){Q_UNUSED(per) Q_UNUSED(position) Q_UNUSED(flag)}
    virtual void paint(QPainter *per,QPainter *perHead,QRectF visibleRect,int &position,bool *flag);
    virtual bool isLocatedInTheArea(QRectF area,QRectF visibleRect,QPainter *per){Q_UNUSED(area) Q_UNUSED(visibleRect) Q_UNUSED(per) return false;}
    virtual bool isClickHeaderArea(QPoint pos){Q_UNUSED(pos)return false;}
    virtual void setActive(bool active){m_isActive = active;}

    virtual void updateParam(int pictureWidth){Q_UNUSED(pictureWidth)}
    virtual void updateParam(){}
    ICurve *curve(){return m_curve;}
    AItem *itemInfo(){return m_itemInfo;}
    virtual QColor color(){return Qt::black;}
    virtual void setColor(QColor color){Q_UNUSED(color)}
    BoardForTrack *board(){return m_board;}

    bool isActive(){return m_isActive;}
};

#endif // AGRAPHICITEM_H
