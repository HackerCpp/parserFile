#ifndef CURVELINE_H
#define CURVELINE_H

#include <QGraphicsItem>
#include <QColor>

class CurveLine : public QGraphicsItem{
    QVector<qreal>* m_dataLine;
    QPen *m_pen;
    double m_min,m_max,m_width,m_scale;
    QPainterPath *path;
    double m_step;
    int m_del;
    bool isPaint;
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
