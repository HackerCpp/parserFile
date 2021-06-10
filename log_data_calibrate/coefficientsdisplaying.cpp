#include "coefficientsdisplaying.h"
#include <QDebug>

CoefficientsDisplaying::CoefficientsDisplaying()
{
    xAxis = new QValueAxis;
    yAxisA = new QValueAxis;
    yAxisB = new QValueAxis;

    m_coeffASeries = new QLineSeries;
    m_coeffBSeries = new QLineSeries;

    m_coeffASeries->setName(tr("Coeff A"));
    m_coeffASeries->setPen(QPen(Qt::red,3));

    yAxisA->setGridLinePen(QPen(Qt::black,0.5));
    yAxisA->setLabelsColor(Qt::red);
    m_coeffBSeries->setName(tr("Coeff B"));
    m_coeffBSeries->setPen(QPen(Qt::blue,3));
    yAxisB->setGridLinePen(QPen(Qt::black,0.5));
    yAxisB->setLabelsColor(Qt::blue);
    chart()->addSeries(m_coeffASeries);
    chart()->addSeries(m_coeffBSeries);
    chart()->setAxisX(xAxis, m_coeffASeries);   // Назначить ось xAxis, осью X для diagramA
    chart()->setAxisY(yAxisA, m_coeffASeries);
    chart()->setAxisX(xAxis, m_coeffBSeries);   // Назначить ось xAxis, осью X для diagramA
    chart()->setAxisY(yAxisB, m_coeffBSeries);
}

CoefficientsDisplaying::~CoefficientsDisplaying(){

}

void CoefficientsDisplaying::addCoeffs(QList<QPointF> coeffA, QList<QPointF> coeffB){
    m_coeffASeries->replace(coeffA);
    m_coeffBSeries->replace(coeffB);
    qreal m_minimumA = 1 ;
    qreal m_maximumA = 0 ;
    qreal m_minimumB = 1 ;
    qreal m_maximumB = 0 ;
    for(int i = 0;i < coeffA.size();++i){
        m_minimumA = m_minimumA < coeffA.at(i).y() ? m_minimumA : coeffA.at(i).y();
        m_maximumA = m_maximumA > coeffA.at(i).y() ? m_maximumA : coeffA.at(i).y();
        m_minimumB = m_minimumB < coeffB.at(i).y() ? m_minimumB : coeffB.at(i).y();
        m_maximumB = m_maximumB > coeffB.at(i).y() ? m_maximumB : coeffB.at(i).y();
    }
    yAxisA->setTickCount(5);
    yAxisB->setTickCount(5);
    yAxisA->setRange(m_minimumA,m_maximumA);
    yAxisB->setRange(m_minimumB,m_maximumB);
    xAxis->setRange(0,coeffA.size());
    xAxis->setTickCount(10);
    update();
}
