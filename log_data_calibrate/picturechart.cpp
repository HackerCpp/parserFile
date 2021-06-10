#include "picturechart.h"
#include <QChartView>
#include <QValueAxis>
#include <QLineSeries>
#include "icurve.h"


using namespace QtCharts;
PictureChart::PictureChart()
{

}

PictureChart::~PictureChart(){
    for(auto path : m_picturesPaths){
        QFile::remove(path);
    }
}

void seriesAddRef(const ICurve &curve,QLineSeries *series,qreal &maximum,qreal &minimum){

    QList<QPointF> f_newPoints;
    bool ok;
    QString f_dataStepStr = curve.desc()->param("data_step").replace(",",".");
    qreal f_dataStep =  f_dataStepStr.left(f_dataStepStr.indexOf("(")).toDouble(&ok);

    int indexBegin = curve.size()  -  curve.sizeOffset();
    int indexEnd = curve.size();
    for(int i =  indexBegin; i < indexEnd; ++i){
        qreal f_data = curve.data(i);
        maximum = maximum > f_data ? maximum : f_data;
        minimum = minimum < f_data ? minimum : f_data;
        f_newPoints.append(QPointF((i - indexBegin) * f_dataStep,f_data));
    }
    series->replace(f_newPoints);
}

QString PictureChart::refToPicture(const ICurve &curveMAX,const ICurve &curveAVER){
    QChartView f_chart;
    QValueAxis f_xAxis,f_yAxis;

    QLineSeries f_seriesRefMax,f_seriesRefAVER;
    f_seriesRefMax.setName(curveMAX.mnemonic());
    f_seriesRefAVER.setName(curveAVER.mnemonic());
    f_seriesRefMax.setPen(QPen(Qt::green,1));
    f_seriesRefAVER.setPen(QPen(Qt::blue,1));
    f_xAxis.setGridLinePen(QPen(Qt::black,0.1));
    f_yAxis.setGridLinePen(QPen(Qt::black,0.1));
    f_xAxis.setTitleText(tr("Frequency(Hz)"));
    f_yAxis.setTitleText(tr("Amplitude(DB)"));

    f_chart.chart()->legend()->setFont(QFont("Times new roman",24,QFont::Bold));
    f_chart.chart()->addSeries(&f_seriesRefMax);
    f_chart.chart()->addSeries(&f_seriesRefAVER);
    f_chart.chart()->setAxisX(&f_xAxis, &f_seriesRefMax);   // Назначить ось xAxis, осью X для diagramA
    f_chart.chart()->setAxisY(&f_yAxis, &f_seriesRefMax);
    f_chart.chart()->setAxisX(&f_xAxis, &f_seriesRefAVER);   // Назначить ось xAxis, осью X для diagramA
    f_chart.chart()->setAxisY(&f_yAxis, &f_seriesRefAVER);
    qreal f_yMax = -120;
    qreal f_yMin = 0;

    seriesAddRef(curveMAX,&f_seriesRefMax,f_yMax,f_yMin);
    seriesAddRef(curveAVER,&f_seriesRefAVER,f_yMax,f_yMin);

    bool ok;
    QString f_dataStepStr = curveMAX.desc()->param("data_step").replace(",",".");
    qreal f_dataStep =  f_dataStepStr.left(f_dataStepStr.indexOf("(")).toDouble(&ok);
    f_xAxis.setRange(0,f_dataStep * qreal(curveMAX.sizeOffset() + 1));
    f_yAxis.setRange(f_yMin,f_yMax);

    QString f_picturePath = QDir().currentPath() + "/protocols/"+ curveMAX.mnemonic() + curveAVER.mnemonic() +".png";
    f_chart.resize(1000,500); //72dpi  564X744px
    f_chart.grab(QRect(QPoint(20, 20), QSize(f_chart.width() - 40,f_chart.height() - 40))).save(f_picturePath,"png");
    m_picturesPaths.push_back(f_picturePath);
    return f_picturePath;
}

QString PictureChart::coeffToPicture(QVector<CoeffsLinearDependence> *coeffs){
    QChartView f_chart;
    QValueAxis f_xAxis,f_yAxis;

    QLineSeries f_seriesA,f_seriesB;
    f_seriesA.setName(tr("coefficients A"));
    f_seriesB.setName(tr("coefficients B"));
    f_seriesA.setPen(QPen(Qt::green,1));
    f_seriesB.setPen(QPen(Qt::blue,1));
    f_xAxis.setGridLinePen(QPen(Qt::black,0.1));
    f_yAxis.setGridLinePen(QPen(Qt::black,0.1));
    f_xAxis.setTitleText("Lines");

    f_chart.chart()->legend()->setFont(QFont("Times new roman",24,QFont::Bold));
    f_chart.chart()->addSeries(&f_seriesA);
    f_chart.chart()->addSeries(&f_seriesB);
    f_chart.chart()->setAxisX(&f_xAxis, &f_seriesA);   // Назначить ось xAxis, осью X для diagramA
    f_chart.chart()->setAxisY(&f_yAxis, &f_seriesA);
    f_chart.chart()->setAxisX(&f_xAxis, &f_seriesB);   // Назначить ось xAxis, осью X для diagramA
    f_chart.chart()->setAxisY(&f_yAxis, &f_seriesB);

    QList<QPointF> f_coeffsA;
    QList<QPointF> f_coeffsB;
    int f_y = 0;
    qreal m_minimumA = 1 ;
    qreal m_maximumA = 0 ;
    qreal m_minimumB = 1 ;
    qreal m_maximumB = 0 ;
    for(auto&& [coef_a,coef_b] : *coeffs){
        m_minimumA = m_minimumA < coef_a ? m_minimumA : coef_a;
        m_maximumA = m_maximumA > coef_a ? m_maximumA : coef_a;
        m_minimumB = m_minimumB < coef_b ? m_minimumB : coef_b;
        m_maximumB = m_maximumB > coef_b ? m_maximumB : coef_b;
        f_coeffsA.push_back(QPointF(f_y,coef_a));
        f_coeffsB.push_back(QPointF(f_y++,coef_b));
    }
    f_yAxis.setRange(m_minimumA < m_minimumB ? m_minimumA : m_minimumB,m_maximumA > m_maximumB ? m_maximumA : m_maximumB);
    f_xAxis.setRange(0,coeffs->size());
    f_seriesA.replace(f_coeffsA);
    f_seriesB.replace(f_coeffsB);
    QString f_picturePath = QDir().currentPath() + "/protocols/" + QString(qrand()) +".png";
    f_chart.resize(1000,500); //72dpi  564X744px
    f_chart.grab(QRect(QPoint(20, 20), QSize(f_chart.width() - 40,f_chart.height() - 40))).save(f_picturePath,"png");
    m_picturesPaths.push_back(f_picturePath);
    return f_picturePath;

}
