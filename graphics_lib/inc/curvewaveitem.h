#ifndef CURVEWAVEITEM_H
#define CURVEWAVEITEM_H

#include "curvebaseitem.h"
#include <QPainter>
#include <QTimer>

enum DrawingMode {WAVE,MULTICOLOR,ONECOLOR};

class CurveWaveItem : public CurveBaseItem{
    DrawingMode m_drawingMode;
public:
    CurveWaveItem(Curve *curve);
    void paint(QPainter *painter,QPainter *painterHeader,qreal yTop,qreal yBottom,bool *flag) override;
    bool isCrosses(QPoint point,int y) override;
    qreal operator[](int index);
    virtual uint amountSaturation(uint index)override;
    ~CurveWaveItem();
};

#endif // CURVEWAVEITEM_H
