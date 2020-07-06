#ifndef CHARTVIEVFORONEWAVEWIDGET_H
#define CHARTVIEVFORONEWAVEWIDGET_H

#include <QChartView>
#include <QGraphicsTextItem>
using namespace QtCharts;


class ChartVievForOneWaveWidget : public QChartView
{
    QGraphicsTextItem *m_textItem;
    QGraphicsLineItem *m_verticalLine;
public:
    ChartVievForOneWaveWidget();
    ~ChartVievForOneWaveWidget()override{}

    //void resizeEvent(QResizeEvent *event) override{}
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override{}
};

#endif // CHARTVIEVFORONEWAVEWIDGET_H
