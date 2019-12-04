#ifndef CURVEBASEITEM_H
#define CURVEBASEITEM_H

#include "curve.h"
#include <QPen>
#include <QGraphicsItem>
#include <QThread>

class CurveBaseItem:public QObject{
    Q_OBJECT
protected:
    bool m_isActive;
    int m_maximumTime;
    int m_maximumDepth;
    Curve *m_curve;
    QPen *m_pen;
    QBrush *m_brush;
    int m_curentWidthLine;
    virtual QRectF boundingRect() const;
public:
    virtual void paint(QPainter *painter,qreal y);
    virtual bool isCrosses(QPoint point,int y);
    static CurveBaseItem *createCurveItem(Curve *curve);
    CurveBaseItem(Curve *curve);
    Curve *getCurve();
    void setLimit(int limit);
    QPen *getPen(){return m_pen;}
    void setActive(bool active);
    bool isActive();
    bool setScale(qreal scale);
    qreal topTime();
    qreal bottomTime();
    qreal topDepth();
    qreal bottomDepth();
    void setWidthLine(int widthLine);
signals:
    void updateL();
};

#endif // CURVEBASEITEM_H
