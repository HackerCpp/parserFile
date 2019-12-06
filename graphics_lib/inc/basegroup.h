#ifndef BASEGROUP_H
#define BASEGROUP_H
#include <QGraphicsItem>
#include <QThread>
#include <QGraphicsScene>
#include <QPainter>
#include <QDebug>
#include <QTimer>
#include <QGraphicsSceneMouseEvent>
#include "tabgroupsettings.h"


class BaseGroup : public QThread, public QGraphicsItem{
    Q_OBJECT
protected:
    static int m_top, m_bottom;
    QRectF *m_visibilitySquare;
    int m_leftX, m_rightX;
    QImage *m_curentPixmap,*m_doublePixMap;

    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem*, QWidget*) override;
    virtual void run()override;
    virtual void swapPixMap();
public:
    static void setTopAndBottom(qreal top,qreal bottom);
    BaseGroup();
    virtual QRectF boundingRect()const override;
    int getRightX();
public slots:
    virtual void updateP(QPointF leftUp,QPointF rightDown);
    void setRightPosition(int rightPosition);
    void setLeftPosition(int leftPosition);
    void sceneUpdate();
    virtual void shift(int leftPosition);
signals:
    void leftPositionChanged(int leftPosition);
    void rightPositionChanged(int rightPosition);
};

#endif // BASEGROUP_H
