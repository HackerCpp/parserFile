#include "onewavewidget.h"
#include <QList>

OneWaveWidget::OneWaveWidget(VSpectrItem *spectrItem)
{
    m_spectrIitems =  new QList<QPair<VSpectrItem *, QLineSeries *> >;
    m_spectrIitems->push_back(QPair<VSpectrItem *, QLineSeries *>(spectrItem,new QLineSeries()));
    m_hSplitter = new QSplitter;
    m_sliderAmplitude = new QxtSpanSlider(Qt::Vertical);
    //m_sliderAmplitude->setHandleMovementMode(QxtSpanSlider::HandleMovementMode::NoOverlapping);
    m_sliderAmplitude->setRange(-150,0);
    m_sliderAmplitude->setSpan(m_sliderAmplitude->minimum(),m_sliderAmplitude->maximum());

    m_sliderFrequency = new QxtSpanSlider(Qt::Horizontal);
    m_sliderFrequency->setRange(0,70000);
    m_sliderFrequency->setSpan(m_sliderFrequency->minimum(),m_sliderFrequency->maximum());

    m_vLayout = new QVBoxLayout;
    m_graphicGridLayout = new QGridLayout();
    m_graphicsWidget = new QWidget();

    xAxis = new QValueAxis;                     // Ось X
    xAxis->setRange(0, 50000);   // Диапазон от 0 до времени которое соответстует SAMPLE_NUM точек
    xAxis->setTitleText(tr("Lines Hz"));       // Название оси X
    xAxis->setTitleBrush(Qt::magenta);          // Цвет названия
    xAxis->setLabelsColor(Qt::magenta);         // Цвет элементов оси
xAxis->setTickCount(20);

    yAxis = new QValueAxis;             // Ось Y
    yAxis->setRange(-150, 0);           // Диапазон от -20 до +20 Вольт
    yAxis->setTitleText(tr("Amplitude"));    // Название оси Y
    yAxis->setTitleBrush(Qt::yellow);   // Цвет названия
    yAxis->setLabelsColor(Qt::yellow);  // Цвет элементов оси
    m_chartView = new QChartView();

    m_chartView->chart()->setTheme(QChart::ChartThemeDark);    // Установка темы QChartView

    foreach(auto value,*m_spectrIitems){
        value.second->setName(value.first->curve()->mnemonic());
        value.second->setPen(QPen(Qt::red,2));
        m_chartView->chart()->addSeries(value.second);
        m_chartView->chart()->setAxisX(xAxis, value.second);   // Назначить ось xAxis, осью X для diagramA
        m_chartView->chart()->setAxisY(yAxis, value.second);
    }

    m_graphicGridLayout->addWidget(m_sliderAmplitude,0,0);
    m_graphicGridLayout->addWidget(m_sliderFrequency,1,1);
    m_graphicGridLayout->addWidget(m_chartView,0,1);

    m_graphicsWidget->setLayout(m_graphicGridLayout);

    m_hSplitter->addWidget(m_graphicsWidget);
    m_vLayout->addWidget(m_hSplitter);

    setLayout(m_vLayout);

    connect(m_sliderAmplitude,&QxtSpanSlider::spanChanged,this,&OneWaveWidget::changeVerticalCoord);
    connect(m_sliderFrequency,&QxtSpanSlider::spanChanged,this,&OneWaveWidget::changeHorizontalCoord);
}

OneWaveWidget::~OneWaveWidget(){

}

void OneWaveWidget::update(const QList<QPointF> &newPoints){
    xAxis->setRange(newPoints.first().y(), newPoints.last().y());
    foreach(auto value,*m_spectrIitems){
        value.second->replace(newPoints);
    }
}

void OneWaveWidget::update(QPoint point){
    bool f_flag = false;
    foreach(auto value,*m_spectrIitems){
        value.second->replace(value.first->oneWave(point.y(),&f_flag));
    }
}

void OneWaveWidget::addItem(VSpectrItem *spectrItem){
    m_spectrIitems->push_back(QPair<VSpectrItem *, QLineSeries *>(spectrItem,new QLineSeries));
    QPair<VSpectrItem *, QLineSeries *> f_value = m_spectrIitems->last();
    f_value.second->setName(f_value.first->curve()->mnemonic());
    f_value.second->setPen(QPen(QColor(qrand() %255,qrand() %255,qrand() %255),2));
    m_chartView->chart()->addSeries(f_value.second);
    m_chartView->chart()->setAxisX(xAxis, f_value.second);   // Назначить ось xAxis, осью X для diagramA
    m_chartView->chart()->setAxisY(yAxis, f_value.second);
}

void OneWaveWidget::changeVerticalCoord(int downValue ,int upValue){
    //добавлено
    yAxis->setRange(downValue, upValue);
    //m_chartView->chart()->update();
}

void OneWaveWidget::changeHorizontalCoord(int downValue ,int upValue){
    xAxis->setRange(downValue, upValue);
    m_chartView->chart()->update();
}
