#ifndef VACUITEM_H
#define VACUITEM_H
#include "verticalitem.h"
#include "drawingthroughadisk.h"
#include "acuItem.h"
#include "colorscale.h"

class VAcuItem : public DrawingThroughADisk , public VerticalItem{
    Q_OBJECT

    qreal m_dataStepPix;
    qreal m_offsetPix;
    qreal m_dataStep;
    qreal m_widthPicturePix;


    void inline drawInterpolationHorizontal(QPainter *per,QRectF visibleRect,bool *flag);
    void inline drawInterpolationHorizontalNoOffset(QPainter *per,int y_top,int y_bottom,bool *flag);
    void drawInterpolationHorForCheckArea(QPainter *per,QRectF visibleRect,bool *flag);

    void drawHeader(QPainter *per,int &position,bool *flag)override;
    void drawBody(QPainter *per,QRectF visibleRect,bool *flag)override;
    void updateParam(int pictureWidth)override;
    void updateParam()override;
    bool isLocatedInTheArea(QRectF area,QRectF visibleRect,QPainter *per)override;
    void loadDrawingParam(int width) override;
    void run()override;

    void drawOnTheDisk()override;

public:
    VAcuItem(AItem *itemInfo,ICurve *curve,BoardForTrack *board);
    ~VAcuItem()override;

};

#endif // VACUITEM_H
