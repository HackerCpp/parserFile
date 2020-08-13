#ifndef TWODIMENSIONALARRAYITEM_H
#define TWODIMENSIONALARRAYITEM_H
#include "drawingthroughadisk.h"
#include "verticalitem.h"
#include "aitem.h"
#include "icurve.h"
#include "boardfortrack.h"

class TwoDimensionalArrayItem : public DrawingThroughADisk , public VerticalItem
{

protected:
    qreal m_dataStepPix;
    qreal m_offsetPix;
    qreal m_dataStep;
    qreal m_dataBegin;
    qreal m_widthPicturePix;
    void(TwoDimensionalArrayItem::*pDrawingFunction)(QPainter *,int ,int ,bool *);


public:
    TwoDimensionalArrayItem(AItem *itemInfo,ICurve *curve,BoardForTrack *board);
    TwoDimensionalArrayItem(const TwoDimensionalArrayItem &other);
    virtual ~TwoDimensionalArrayItem()override{}

    void drawHeader(QPainter *per,int &position,bool *flag)override;
    void drawBody(QPainter *per,QRectF visibleRect,bool *flag)override;

    void run()override;

protected:
    virtual void selectOptions(){pDrawingFunction = nullptr;}
public:
    virtual void inline drawInterpolationHorizontalNoOffset(QPainter *per,int y_top,int y_bottom,bool *flag){Q_UNUSED(per) Q_UNUSED(y_top) Q_UNUSED(y_bottom) Q_UNUSED(flag)}
    virtual void inline drawInterpolationVerticalNoOffset(QPainter *per,int y_top,int y_bottom,bool *flag){Q_UNUSED(per) Q_UNUSED(y_top) Q_UNUSED(y_bottom) Q_UNUSED(flag)}
    virtual void inline drawPointsTwoColorsNoOffset(QPainter *per,int y_top,int y_bottom,bool *flag){Q_UNUSED(per) Q_UNUSED(y_top) Q_UNUSED(y_bottom) Q_UNUSED(flag)}
    virtual void inline drawWaveNoOffset(QPainter *per,int y_top,int y_bottom,bool *flag){Q_UNUSED(per) Q_UNUSED(y_top) Q_UNUSED(y_bottom) Q_UNUSED(flag)}
    // index_x ,index_y
    QPoint indexesFromScenePoint(QPointF point);

};

#endif // TWODIMENSIONALARRAYITEM_H
