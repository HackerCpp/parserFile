#ifndef ONEWAVEWIDGET_H
#define ONEWAVEWIDGET_H
#include <QtCharts>
#include "vspectritem.h"
#include "vacuitem.h"
#include <QPair>
#include "qxtspanslider.h"
#include "chartvievforonewavewidget.h"
#include "modelonewave.h"
#include <QSizePolicy>




class OneWaveWidget : public QWidget
{
    Q_OBJECT

    ChartViewForOneWaveWidget *m_chartView;

    QValueAxis *xAxis;  // Ось X
    QValueAxis *yAxis;  // Ось Y
    QList<QPair<AGraphicItem *, QLineSeries *> > *m_items;
    QSplitter *m_hSplitter;
    QxtSpanSlider *m_sliderAmplitude, *m_sliderFrequency;
    QVBoxLayout *m_vLayout;
    QGridLayout *m_graphicGridLayout;
    QWidget *m_graphicsWidget;

    ModelOneWave *m_modelOneWave;
    QTableView *m_tableViewOneWavenfo;
public:
    OneWaveWidget(AGraphicItem *item);
    ~OneWaveWidget();

    void update(const QList<QPointF> &newPoints);
    void update(QPoint point);

    void addItem(AGraphicItem *item);
public slots:
    void changeVerticalCoord(int downValue ,int upValue);
    void changeHorizontalCoord(int downValue ,int upValue);

};

#endif // ONEWAVEWIDGET_H
