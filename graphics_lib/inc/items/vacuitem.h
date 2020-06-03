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
    qreal m_curentPictureWidth,m_prevPictureWidth;
    bool m_updatedParam;

    void inline drawInterpolationHorizontal(QPainter *per,QRectF visibleRect,bool *flag);
    void inline drawInterpolationHorizontalNoOffset(QPainter *per,int y_top,int y_bottom);
    void drawInterpolationHorForCheckArea(QPainter *per,QRectF visibleRect,bool *flag);

    void drawBody(QPainter *per,QRectF visibleRect,bool *flag)override;
    void updateParam(int pictureWidth)override;
    bool isLocatedInTheArea(QRectF area,QRectF visibleRect,QPainter *per)override;
    void loadDrawingParam(int width);
    void run()override;

public:
    VAcuItem(AItem *itemInfo,ICurve *curve,BoardForTrack *board);
    ~VAcuItem()override;

};

#endif // VACUITEM_H
