#ifndef VSPECTR_H
#define VSPECTR_H
#include "specItem.h"
#include "twodimensionalarrayitem.h"



class VSpectrItem : public TwoDimensionalArrayItem{



public:
    VSpectrItem(AItem *itemInfo,ICurve *curve,BoardForTrack *board);
    VSpectrItem(const VSpectrItem &other);
    ~VSpectrItem();

private:
    void inline drawInterpolationVertical(QPainter *per,QRectF visibleRect,bool *flag);
    void inline drawInterpolationVerticalNoOffset(QPainter *per,int y_top,int y_bottom,bool *flag)override;
    void inline drawWaveNoOffset(QPainter *per,int y_top,int y_bottom,bool *flag)override;
    void drawInterpolationHorForCheckArea(QPainter *per,QRectF visibleRect,bool *flag);
public:
    void drawOneWawe(QPainter *per,int position,bool *flag);
    QList<QPointF> oneWave(int position,bool *flag);
    void updateParam(int pictureWidth)override;
    void updateParam()override;
    bool isLocatedInTheArea(QRectF area,QRectF visibleRect,QPainter *per)override;
    void loadDrawingParam(int width)override;
    virtual void drawOnTheDisk()override;
    //void run()override;
    void selectOptions()override;
    qreal dataStep(){return m_dataStep;}



};

#endif // VSPECTR_H
