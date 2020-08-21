#ifndef WIDGETSELECTWAVESEGMENT_H
#define WIDGETSELECTWAVESEGMENT_H
#include <QWidget>
#include <QChartView>
#include <QValueAxis>
#include <qxtspanslider.h>
#include <QSplitter>
#include <QVBoxLayout>
#include "datacountingacoustics.h"
#include <QLineSeries>
#include "chartviewselectsegment.h"

using namespace QtCharts;

class WidgetSelectWaveSegment : public QWidget
{
    Q_OBJECT
    ChartViewSelectSegment *m_chartViewOne,*m_chartViewTwo;
    QLineSeries *m_oneSeries,*m_twoSeries;

    QValueAxis *xAxisOne,*xAxisTwo;
    QValueAxis *yAxisOne,*yAxisTwo;


    QSplitter *m_hSplitter;
    QxtSpanSlider *m_sliderAmplitude,*m_sliderFrequencyOne,*m_sliderFrequencyTwo;
    QVBoxLayout *m_vLayout;
    QWidget *m_graphicsWidgetOne,*m_graphicsWidgetTwo;
    QPointer<QVBoxLayout> m_vLayoutOne,m_vLayoutTwo;


    DataCountingAcoustics *m_dataAcu;

public:
    WidgetSelectWaveSegment(DataCountingAcoustics *dataAcu);
    ~WidgetSelectWaveSegment()override{}


    bool eventFilter(QObject *object, QEvent *event)override;
    void update(QPoint scenePoint);
    void chartResize();
    void wheelEvent(QWheelEvent *event)override;

    QPair<int,int> leftAndRightBandAcuOne();
    QPair<int,int> leftAndRightBandAcuTwo();
    qreal ampAcuOne(){return m_chartViewOne->ampLine();}
    qreal ampAcuTwo(){return m_chartViewTwo->ampLine();}

public slots:
    void changeVerticalCoord(int downValue ,int upValue);
    void changeHorizontalCoordOne(int downValue ,int upValue);
    void changeHorizontalCoordTwo(int downValue ,int upValue);
};

#endif // WIDGETSELECTWAVESEGMENT_H
