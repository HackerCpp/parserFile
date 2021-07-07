#ifndef CHARTVIEVFORONEWAVEWIDGET_H
#define CHARTVIEVFORONEWAVEWIDGET_H

#include <QChartView>
#include <QGraphicsTextItem>
#include "modelonewave.h"

using namespace QtCharts;

class ChartViewForOneWaveWidget : public QChartView
{
    Q_OBJECT
    QGraphicsTextItem *m_textItem;
    QGraphicsLineItem *m_verticalLine,*m_horizontalLine;
    ModelOneWave * m_modelOneWave;

    bool m_flagMousePress;
public:
    ChartViewForOneWaveWidget(ModelOneWave *modelOneWave);
    ~ChartViewForOneWaveWidget()override{}

    void updateLineInfo(QPointF point);

    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void dataUpdate();
};

#endif // CHARTVIEVFORONEWAVEWIDGET_H
