#ifndef COEFFICIENTSDISPLAYING_H
#define COEFFICIENTSDISPLAYING_H

#include <QChartView>
#include <QGraphicsTextItem>
#include "modelonewave.h"
#include <QValueAxis>


using namespace QtCharts;

class CoefficientsDisplaying : public QChartView
{
    QValueAxis *xAxis;
    QValueAxis *yAxisA,*yAxisB;
    QLineSeries *m_coeffASeries,*m_coeffBSeries;
public:
    CoefficientsDisplaying();
    ~CoefficientsDisplaying();

    void addCoeffs(QList<QPointF> coeffA, QList<QPointF> coeffB);
};

#endif // COEFFICIENTSDISPLAYING_H
