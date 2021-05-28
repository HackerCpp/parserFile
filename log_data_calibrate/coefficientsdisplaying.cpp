#include "coefficientsdisplaying.h"
#include <QDebug>

CoefficientsDisplaying::CoefficientsDisplaying()
{
    xAxis = new QValueAxis;
    yAxis = new QValueAxis;
    m_coeffASeries = new QLineSeries;
    m_coeffBSeries = new QLineSeries;

    m_coeffASeries->setName(tr("Coeff A"));
    m_coeffASeries->setPen(QPen(Qt::red,2));
    m_coeffBSeries->setName(tr("Coeff B"));
    m_coeffBSeries->setPen(QPen(Qt::green,2));
    chart()->addSeries(m_coeffASeries);
    chart()->addSeries(m_coeffBSeries);
    chart()->setAxisX(xAxis, m_coeffASeries);   // Назначить ось xAxis, осью X для diagramA
    chart()->setAxisY(yAxis, m_coeffASeries);
    chart()->setAxisX(xAxis, m_coeffBSeries);   // Назначить ось xAxis, осью X для diagramA
    chart()->setAxisY(yAxis, m_coeffBSeries);
}

CoefficientsDisplaying::~CoefficientsDisplaying(){

}

void CoefficientsDisplaying::addCoeffs(QList<QPointF> coeffA, QList<QPointF> coeffB){
    m_coeffASeries->replace(coeffA);
    m_coeffBSeries->replace(coeffB);


    qreal m_minimum = 0 ;
    qreal m_maximum = 0 ;
    for(int i = 0;i < coeffA.size();++i){
        qreal curMaximum;
        qreal curMinimum;
        if( coeffA.at(i).y() > coeffB.at(i).y()){
            curMaximum = coeffA.at(i).y();
            curMinimum = coeffB.at(i).y();
        }
        else{
            curMaximum = coeffB.at(i).y();
            curMinimum = coeffA.at(i).y();
        }
        m_minimum = m_minimum < curMinimum ? m_minimum : curMinimum;
        m_maximum = m_maximum > curMaximum ? m_maximum : curMaximum;
    }
    yAxis->setRange(m_minimum,m_maximum);
    xAxis->setRange(0,coeffA.size());
    update();
}
