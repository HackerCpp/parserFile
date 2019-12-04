#ifndef CURVELINE_H
#define CURVELINE_H

#include "curvebaseitem.h"
#include <QPainter>
#include <QTimer>

class CurveLineItem : public CurveBaseItem{
public:
    CurveLineItem(Curve *curve);
    void paint(QPainter *painter,qreal y) override;
    bool isCrosses(QPoint point,int y) override;
    virtual ~CurveLineItem();


};

#endif // CURVELINE_H
