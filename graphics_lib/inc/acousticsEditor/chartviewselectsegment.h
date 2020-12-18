#ifndef CHARTVIEWSELECTSEGMENT_H
#define CHARTVIEWSELECTSEGMENT_H
#include <QChartView>
#include <QGraphicsTextItem>
#include "modelonewave.h"

using namespace QtCharts;

class ChartViewSelectSegment : public QChartView
{
    Q_OBJECT
    QGraphicsLineItem *m_verticalLineLeft,
    *m_verticalLineRight,*m_horizontalLine;
    QPoint prevPoint;
    bool m_isActiveLeftLine,m_isActiveRightLine,m_isActiveHLine;
    QPointF m_positionLeftLine,m_positionRightLine,m_positionHLine;
public:
    ChartViewSelectSegment(QWidget *parent = nullptr);
    ~ChartViewSelectSegment()override{}

    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

    qreal ampLine(){return m_positionHLine.y();}
    qreal posLeftLine();
    qreal posRightLine();

public slots:
    void resize();
};

#endif // CHARTVIEWSELECTSEGMENT_H
