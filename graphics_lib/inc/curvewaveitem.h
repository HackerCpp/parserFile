#ifndef CURVEWAVEITEM_H
#define CURVEWAVEITEM_H

#include "curvebaseitem.h"
#include <QPainter>
#include <QTimer>

enum DrawingMode {WAVE,MULTICOLOR,ONECOLOR};

struct Multicolor{
  QColor color;
  qreal value;
};

class CurveWaveItem : public CurveBaseItem{
    DrawingMode m_drawingMode;
    QList<Multicolor>*m_multicolor;
public:
    CurveWaveItem(Curve *curve);
    void paint(QPainter *painter,QPainter *painterHeader,qreal yTop,qreal yBottom,bool *flag) override;
    qreal operator[](int index);
    qreal data(int index);
    ~CurveWaveItem();
};

#endif // CURVEWAVEITEM_H
