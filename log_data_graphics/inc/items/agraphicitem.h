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
    int m_positionHeaderArea,m_heightHeaderArea,m_heightLegend;
    QFont m_fontLegend;
    qreal m_recordPointDepth;

    ICurve *m_currentMainValue;
    volatile qreal m_currentRecordPoint;
    volatile qreal m_currentScaleMainValue;

    int m_modeCountedDepth;
    qreal k_a,k_b,k_c;

public:
    AGraphicItem(ICurve *curve,BoardForTrack *board);
    AGraphicItem(const AGraphicItem &other);
    virtual ~AGraphicItem(){}
    virtual void deleteLater(){}

    qreal topValue();
    qreal bottomValue();

    virtual void drawHeader(QPainter *per,int &position,bool *flag){Q_UNUSED(per) Q_UNUSED(position) Q_UNUSED(flag)}
    virtual void drawLegend(QPainter *per,int &position,QPointF pointStarting,QPointF pointCurrent,bool *flag){Q_UNUSED(per) Q_UNUSED(position) Q_UNUSED(pointStarting) Q_UNUSED(pointCurrent) Q_UNUSED(flag)}
    virtual void drawBody(QPainter *per,QRectF visibleRect,bool *flag){Q_UNUSED(per) Q_UNUSED(visibleRect) Q_UNUSED(flag)}
    virtual void paint(QPainter *per,QPainter *perHead,QRectF visibleRect,int &position,bool *flag);
    virtual bool isLocatedInTheArea(QRectF area,QRectF visibleRect,QPainter *per){Q_UNUSED(area) Q_UNUSED(visibleRect) Q_UNUSED(per) return false;}
    virtual bool isClickHeaderArea(QPoint pos){Q_UNUSED(pos)return false;}
    virtual void setActive(bool active){m_isActive = active;}
    virtual void setDepthCoeff(QVector<qreal> f_coeffs);

    virtual void updateParam(int pictureWidth);
    virtual void updateParam(){}

    ICurve *curve(){return m_curve;}
    ICurve *currentMainValue(){return m_currentMainValue;}
    AItem *itemInfo(){return m_itemInfo;}
    virtual QColor color(){return Qt::black;}
    virtual void setColor(QColor color){Q_UNUSED(color)}
    BoardForTrack *board(){return m_board;}
    bool is_visible(){return m_itemInfo->visible(AItem::BOARD_GRAPH_VIEW);}

    bool isActive(){return m_isActive;}
    int mainIndexFromScenePoint(QPointF point);
    qreal valueFromScenePoint(QPointF point);
    qreal maximumFromScenePoints(QPointF pointBegin,QPointF pointEnd);
    qreal minimumFromScenePoints(QPointF pointBegin,QPointF pointEnd);
    QPair<QString,qreal> mainValueFromScene(QPointF point);
    //Перед использованием данной функции нужно проверить currentMainValue() != nullptr
    //в данной функции эта проверка не производится для быстродействия
    virtual inline qreal mainValue(int index);
    virtual inline qreal mainValueMinimum();
    virtual inline qreal mainValueMaximum();
};

#endif // AGRAPHICITEM_H
