#ifndef VACUITEM_H
#define VACUITEM_H
#include "verticalitem.h"
#include "drawingthroughadisk.h"
#include "acuItem.h"
#include "colorscale.h"
#include "twodimensionalarrayitem.h"

class VAcuItem : public TwoDimensionalArrayItem{
    Q_OBJECT
    void  drawInterpolationHorizontal(QPainter *per,QRectF visibleRect,bool *flag);
    void  drawInterpolationHorizontalNoOffset(QPainter *per,int y_top,int y_bottom,bool *flag)override;
    void  drawPointsTwoColorsNoOffset(QPainter *per,int y_top,int y_bottom,bool *flag)override;
    void drawWaveNoOffset(QPainter *per,int y_top,int y_bottom,bool *flag)override;
    void drawInterpolationHorForCheckArea(QPainter *per,QRectF visibleRect,bool *flag);

public:
    void updateParam(int pictureWidth)override;
    void updateParam()override;
    bool isLocatedInTheArea(QRectF area,QRectF visibleRect,QPainter *per)override;
    void loadDrawingParam(int width) override;
    void selectOptions()override;

    void drawOnTheDisk()override;

    VAcuItem(AItem *itemInfo,ICurve *curve,BoardForTrack *board);
    VAcuItem(const VAcuItem &other);
    ~VAcuItem()override{}
    void deleteLater()override;
};

#endif // VACUITEM_H
