#ifndef AGRAPHICITEM_H
#define AGRAPHICITEM_H
#include "aitem.h"
#include "icurve.h"
#include <QPainter>
#include "boardfortrack.h"

class AGraphicItem : public QThread
{
protected:
    AItem *m_itemInfo;
    ICurve *m_curve;
    BoardForTrack *m_board;
    bool m_isActive;

    virtual void drawBody(QPainter *per,QRectF visibleRect,bool *flag){Q_UNUSED(per) Q_UNUSED(visibleRect) Q_UNUSED(flag)}
    virtual void drawHeader(QPainter *per,int &position,bool *flag){Q_UNUSED(per) Q_UNUSED(position) Q_UNUSED(flag)}

public:
    AGraphicItem(ICurve *curve,BoardForTrack *board);
    ~AGraphicItem();

    qreal topValue();
    qreal bottomValue();

    virtual void paint(QPainter *per,QPainter *perHead,QRectF visibleRect,int &position,bool *flag);
    virtual bool isLocatedInTheArea(QRectF area,QRectF visibleRect,QPainter *per){Q_UNUSED(area) Q_UNUSED(visibleRect) Q_UNUSED(per) return true;}
    virtual void setActive(bool active){m_isActive = active;}
    virtual void run()override{}
    virtual void updateParam(int pictureWidth){Q_UNUSED(pictureWidth)}
    ICurve *curve(){return m_curve;}
    AItem *itemInfo(){return m_itemInfo;}
    virtual QColor color(){return Qt::black;}
    virtual void setColor(QColor color){Q_UNUSED(color)}

    bool isActive(){return m_isActive;}
};

#endif // AGRAPHICITEM_H
