#ifndef CURVELINE_H
#define CURVELINE_H

#include "curvebaseitem.h"
#include <QPainter>
#include <QTimer>

class CurveLineItem : public CurveBaseItem{

public:
    CurveLineItem(Curve *curve);
    void paint(QPainter *painter,QPainter *painterHeader,qreal y) override;
    bool isCrosses(QPoint point,int y) override;
    qreal operator[](int index);
    virtual uint amountSaturation(uint index)override;
    virtual ~CurveLineItem()override;


};

#endif // CURVELINE_H
