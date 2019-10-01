#ifndef CURVELINE_H
#define CURVELINE_H

#include <inc/graphic/basecurveclass.h>
#include <QColor>

class CurveLine : public BaseCurveClass{
    QVector<qreal>* m_dataLine;
    QPen *m_pen;
    double m_min,m_max,m_scale;
    int m_width;
    QPainterPath path;
    bool isPaint;
    QRectF *m_rect;
    int m_rectheight;
public:
    CurveLine(QVector<qreal>*dataLine);
    CurveLine();
protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem*, QWidget*);
    QRectF boundingRect() const;
    qreal saturation(qreal value);
    int amountOfSaturation(qreal value);
    //void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    //void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
    //void mousePressEvent(QGraphicsSceneMouseEvent *event);
    //void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    //void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    //void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);
};

#endif // CURVELINE_H
