#ifndef VACUITEM_H
#define VACUITEM_H
#include "verticalitem.h"
#include "acuItem.h"
#include "colorscale.h"

class VAcuItem : public VerticalItem{
    qreal m_dataStepPix;
    qreal m_offsetPix;
    qreal m_dataStep;
    qreal m_widthPicturePix;


    void inline drawInterpolationVertical(QPainter *per,QRectF visibleRect,bool *flag);
    void inline drawInterpolationHorizontal(QPainter *per,QRectF visibleRect,bool *flag);
    void drawInterpolationHorForCheckArea(QPainter *per,QRectF visibleRect,bool *flag);

    void drawBody(QPainter *per,QRectF visibleRect,bool *flag)override;
    void updateParam(int pictureWidth)override;
    bool isLocatedInTheArea(QRectF area,QRectF visibleRect,QPainter *per)override;
    void loadDrawingParam(int width);

public:
    VAcuItem(AItem *itemInfo,ICurve *curve,BoardForTrack *board);
    ~VAcuItem(){}

};

#endif // VACUITEM_H
