#ifndef ONEWAVEWIDGET_H
#define ONEWAVEWIDGET_H
#include <QtCharts>

class ICurve;
class AGraphicItem;
class ModelOneWave;
class ChartViewForOneWaveWidget;
class QxtSpanSlider;

class OneWaveWidget : public QWidget
{
    Q_OBJECT

    ChartViewForOneWaveWidget *m_chartView;

    QValueAxis *xAxis;
    QValueAxis *yAxis;
    QList<QPair<AGraphicItem *, QLineSeries *> > *m_items;
    QList<QPair<ICurve *, QLineSeries *> > *m_curves;
    QSplitter *m_hSplitter;
    QxtSpanSlider *m_sliderAmplitude, *m_sliderFrequency;
    QVBoxLayout *m_vLayout;
    QGridLayout *m_graphicGridLayout;
    QWidget *m_graphicsWidget;

    ModelOneWave *m_modelOneWave;
    QTableView *m_tableViewOneWavenfo;

public:
    OneWaveWidget(AGraphicItem *item);
    OneWaveWidget(ICurve *curve);
    ~OneWaveWidget();

    void update(const QList<QPointF> &newPoints);
    void update(QPoint point);
    void update(uint indexStr);

    void addItem(AGraphicItem *item);
    void addCurve(ICurve *curve);
public slots:
    void changeVerticalCoord(int downValue ,int upValue);
    void changeHorizontalCoord(int downValue ,int upValue);

};

#endif // ONEWAVEWIDGET_H
