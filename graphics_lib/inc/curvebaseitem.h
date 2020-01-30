#ifndef CURVEBASEITEM_H
#define CURVEBASEITEM_H

#include "curve.h"
#include <QPen>
#include <QGraphicsItem>
#include <QThread>
#include "mainvalue.h"


class CurveBaseItem:public QObject{
    Q_OBJECT
protected:
    bool m_isShow;
    int m_leftShift;
    qreal m_scale;
    int m_limit;
    static int m_headerSliceHeight;
    int m_positionInHeader;
    bool m_isActive;
    int m_maximumTime;
    int m_maximumDepth;
    MainValue *m_mainValue;
    Curve *m_curve;
    QPen *m_pen;
    QBrush *m_brush;
    int m_curentWidthLine;
    virtual QRectF boundingRect() const;
    virtual void drawHeader(QPainter *painterHeader);
public:
    void setPositionInHeader(int pos);
    virtual void paint(QPainter *painter,QPainter *painterHeader,qreal yTop,qreal yBottom,bool *flag);
    virtual bool isCrosses(QPoint point,int y);
    static CurveBaseItem *createCurveItem(Curve *curve);
    CurveBaseItem(Curve *curve);
    Curve *getCurve();
    void setLimit(int limit);
    int limit(){return m_limit;}
    QPen *getPen(){return m_pen;}
    void setActive(bool active);
    bool isActive();
    void setScale(qreal scale);
    void setLeftShift(int leftShift);
    int leftShift(){return m_leftShift;}
    qreal topTime();
    qreal bottomTime();
    qreal topDepth();
    qreal bottomDepth();
    void setWidthLine(int widthLine);
    void setMainValue(MainValue *mainValue);
    virtual uint amountSaturation(uint index);
    qreal scale(){return m_scale;}
    void setShow(bool isShow);
    bool isShow(){return m_isShow;}
signals:
    void updateL(QPointF leftUp,QPointF rightDown,bool forceARedraw);
};

#endif // CURVEBASEITEM_H
