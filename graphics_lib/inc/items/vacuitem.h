#ifndef VACUITEM_H
#define VACUITEM_H
#include "verticalitem.h"
#include "drawingthroughadisk.h"
#include "acuItem.h"
#include "colorscale.h"
#include "twodimensionalarrayitem.h"

class VAcuItem : public TwoDimensionalArrayItem{
    Q_OBJECT


    void inline drawInterpolationHorizontal(QPainter *per,QRectF visibleRect,bool *flag);
    void inline drawInterpolationHorizontalNoOffset(QPainter *per,int y_top,int y_bottom,bool *flag)override;
    void inline drawPointsTwoColorsNoOffset(QPainter *per,int y_top,int y_bottom,bool *flag)override;
    void inline drawWaveNoOffset(QPainter *per,int y_top,int y_bottom,bool *flag)override;
    void drawInterpolationHorForCheckArea(QPainter *per,QRectF visibleRect,bool *flag);

public:
    void updateParam(int pictureWidth)override;
    void updateParam()override;
    QList<QPointF> oneWave(int position,bool *flag);
    bool isLocatedInTheArea(QRectF area,QRectF visibleRect,QPainter *per)override;
    void loadDrawingParam(int width) override;
    //void run()override;
    void selectOptions()override;

    void drawOnTheDisk()override;

    VAcuItem(AItem *itemInfo,ICurve *curve,BoardForTrack *board);
    ~VAcuItem()override;

    qreal dataStep(){return m_dataStep;}

};

#endif // VACUITEM_H
