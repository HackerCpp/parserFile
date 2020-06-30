#ifndef VSPECTR_H
#define VSPECTR_H
#include "verticalitem.h"
#include "specItem.h"
#include "drawingthroughadisk.h"


class VSpectrItem : public DrawingThroughADisk, public VerticalItem{
    qreal m_dataStepPix;
    qreal m_offsetPix;
    qreal m_dataStep;
    qreal m_dataBegin;
    qreal m_widthPicturePix;


public:
    VSpectrItem(AItem *itemInfo,ICurve *curve,BoardForTrack *board);
    VSpectrItem(const VSpectrItem &other);
    ~VSpectrItem()override{}

private:
    void inline drawInterpolationVertical(QPainter *per,QRectF visibleRect,bool *flag);
    void inline drawInterpolationVerticalNoOffset(QPainter *per,int y_top,int y_bottom,bool *flag);
    void drawInterpolationHorForCheckArea(QPainter *per,QRectF visibleRect,bool *flag);
public:
    void drawBody(QPainter *per,QRectF visibleRect,bool *flag)override;
    void drawOneWawe(QPainter *per,int position,bool *flag);
    QList<QPointF> oneWave(int position,bool *flag);
    void updateParam(int pictureWidth)override;
    void updateParam()override;
    bool isLocatedInTheArea(QRectF area,QRectF visibleRect,QPainter *per)override;
    void loadDrawingParam(int width)override;
    virtual void drawOnTheDisk()override;
    void run()override;



};

#endif // VSPECTR_H
