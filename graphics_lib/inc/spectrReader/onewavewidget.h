#ifndef ONEWAVEWIDGET_H
#define ONEWAVEWIDGET_H
#include <QtCharts>
#include <vspectritem.h>
#include <QPair>
#include "qxtspanslider.h"




class OneWaveWidget : public QWidget
{
    Q_OBJECT
    QList<QSplineSeries> *m_iagrams;

    QChartView *m_chartView;
    QValueAxis *xAxis;  // Ось X
    QValueAxis *yAxis;  // Ось Y
    QList<QPair<VSpectrItem *, QSplineSeries *> > *m_spectrIitems;
    QSplitter *m_hSplitter;
    QxtSpanSlider *m_sliderAmplitude, *m_sliderFrequency;
    QVBoxLayout *m_vLayout;
    QGridLayout *m_graphicGridLayout;
    QWidget *m_graphicsWidget;
public:
    OneWaveWidget(VSpectrItem *spectrItem);
    ~OneWaveWidget();

    void update(const QList<QPointF> &newPoints);
    void update(QPoint point);

    void addItem(VSpectrItem *spectrItem);
public slots:
    void changeVerticalCoord(int downValue ,int upValue);
    void changeHorizontalCoord(int downValue ,int upValue);

};

#endif // ONEWAVEWIDGET_H
