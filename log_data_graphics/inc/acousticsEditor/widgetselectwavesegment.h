#ifndef WIDGETSELECTWAVESEGMENT_H
#define WIDGETSELECTWAVESEGMENT_H
#include <QWidget>
#include <QChartView>
#include <QValueAxis>
#include <qxtspanslider.h>
#include <QSplitter>
#include <QVBoxLayout>
#include <QLineSeries>
#include "chartviewselectsegment.h"
#include <QPointer>
#include "vacuitem.h"

using namespace QtCharts;

class WidgetSelectWaveSegment : public QWidget
{
    Q_OBJECT
    QVector<VAcuItem *> m_acuItems;
    QVector<ChartViewSelectSegment *> *m_chartViews;
    QVector<QLineSeries*> *m_series;

    QVector<QValueAxis *> *xAxis;
    QVector<QValueAxis *> *yAxis;
    QSplitter *m_hSplitter;
    QxtSpanSlider *m_sliderAmplitude;
    QVector<QxtSpanSlider *> *m_sliderMicroSec;
    QVector<QWidget *> *m_graphicsWidgets;
    QVector<QVBoxLayout*> *m_vLayouts;
    QVBoxLayout *m_vLayout;

public:
    WidgetSelectWaveSegment(QVector<VAcuItem *> acuItems);
    ~WidgetSelectWaveSegment()override{}


    bool eventFilter(QObject *object, QEvent *event)override;
    void update(QPoint scenePoint);
    void chartResize();
    void wheelEvent(QWheelEvent *event)override;

    QPair<int,int> leftAndRightBandAcu(int index);
    qreal ampAcu(int index);

public slots:
    void changeVerticalCoord(int downValue ,int upValue);
};

#endif // WIDGETSELECTWAVESEGMENT_H
