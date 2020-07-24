#include "onewavewidget.h"
#include <QList>
#include "customdelegates.h"

OneWaveWidget::OneWaveWidget(VSpectrItem *spectrItem)
{
    m_spectrIitems =  new QList<QPair<VSpectrItem *, QLineSeries *> >;
    m_spectrIitems->push_back(QPair<VSpectrItem *, QLineSeries *>(spectrItem,new QLineSeries()));
    m_hSplitter = new QSplitter;
    m_sliderAmplitude = new QxtSpanSlider(Qt::Vertical);
    //m_sliderAmplitude->setHandleMovementMode(QxtSpanSlider::HandleMovementMode::NoOverlapping);


    m_modelOneWave = new ModelOneWave();
    m_tableViewOneWavenfo = new QTableView;
    m_tableViewOneWavenfo->setItemDelegateForColumn(0,new CheckBoxDelegate());
    m_tableViewOneWavenfo->setItemDelegateForColumn(2,new ColorDelegate());
    m_tableViewOneWavenfo->setModel(m_modelOneWave);


    QString valueRange = spectrItem->curve()->desc()->param("val_range");
    int f_minimum = valueRange.left(valueRange.indexOf("..")).toDouble();
    int f_maximum = valueRange.mid(valueRange.indexOf("..") + 2).toDouble();
    m_sliderAmplitude->setRange(f_minimum,f_maximum);
    m_sliderAmplitude->setSpan(m_sliderAmplitude->minimum(),m_sliderAmplitude->maximum());

    m_sliderFrequency = new QxtSpanSlider(Qt::Horizontal);
    m_sliderFrequency->setRange(-1,spectrItem->curve()->sizeOffset() * spectrItem->dataStep() + 1);
    m_sliderFrequency->setSpan(m_sliderFrequency->minimum(),m_sliderFrequency->maximum());

    m_vLayout = new QVBoxLayout;
    m_graphicGridLayout = new QGridLayout();
    m_graphicsWidget = new QWidget();

    xAxis = new QValueAxis;                     // Ось X
    xAxis->setRange(m_sliderFrequency->minimum(), m_sliderFrequency->maximum());
    xAxis->setTitleText(tr("Lines Hz"));       // Название оси X
    xAxis->setTitleBrush(Qt::magenta);          // Цвет названия
    xAxis->setLabelsColor(Qt::magenta);         // Цвет элементов оси
    xAxis->setTickCount(10);

    yAxis = new QValueAxis;             // Ось Y
    yAxis->setRange(m_sliderAmplitude->minimum(), m_sliderAmplitude->maximum());           // Диапазон от -20 до +20 Вольт
    yAxis->setTitleText(tr("Amplitude"));    // Название оси Y
    yAxis->setTitleBrush(Qt::yellow);   // Цвет названия
    yAxis->setLabelsColor(Qt::yellow);  // Цвет элементов оси
    m_chartView = new ChartViewForOneWaveWidget(m_modelOneWave);

    m_chartView->chart()->setTheme(QChart::ChartThemeDark);    // Установка темы QChartView

    foreach(auto value,*m_spectrIitems){
        value.second->setName(value.first->curve()->mnemonic());
        value.second->setPen(QPen(Qt::red,2));
        m_chartView->chart()->addSeries(value.second);
        m_chartView->chart()->setAxisX(xAxis, value.second);   // Назначить ось xAxis, осью X для diagramA
        m_chartView->chart()->setAxisY(yAxis, value.second);
        m_modelOneWave->insertWaveInfo(OneWaveInfo{value.second,true,value.second->name(),
                                              value.second->pen().color().name(),0,0,0,0,0});
    }
    m_graphicGridLayout->addWidget(m_sliderAmplitude,0,0);
    m_graphicGridLayout->addWidget(m_sliderFrequency,1,1);
    m_graphicGridLayout->addWidget(m_chartView,0,1);

    m_graphicsWidget->setLayout(m_graphicGridLayout);

    m_hSplitter->addWidget(m_graphicsWidget);
    m_hSplitter->addWidget(m_tableViewOneWavenfo);

    m_vLayout->addWidget(m_hSplitter);

    setLayout(m_vLayout);

    connect(m_sliderAmplitude,&QxtSpanSlider::spanChanged,this,&OneWaveWidget::changeVerticalCoord);
    connect(m_sliderFrequency,&QxtSpanSlider::spanChanged,this,&OneWaveWidget::changeHorizontalCoord);
}

OneWaveWidget::~OneWaveWidget(){

}

void OneWaveWidget::update(const QList<QPointF> &newPoints){ //Добавляет точки
    xAxis->setRange(newPoints.first().y(), newPoints.last().y());
    foreach(auto value,*m_spectrIitems){
        value.second->replace(newPoints);
    }
    m_chartView->dataUpdate();
}

void OneWaveWidget::update(QPoint point){ //Добавляет точки из SpectrItem по координатам на сцене
    bool f_flag = false;
    foreach(auto value,*m_spectrIitems){
            //second - QLineSeries, first - VSpectrItem
        value.second->replace(value.first->oneWave(point.y(),&f_flag));
    }
    m_chartView->dataUpdate();
}



void OneWaveWidget::addItem(VSpectrItem *spectrItem){
    m_spectrIitems->push_back(QPair<VSpectrItem *, QLineSeries *>(spectrItem,new QLineSeries));
    QPair<VSpectrItem *, QLineSeries *> f_value = m_spectrIitems->last();
    f_value.second->setName(f_value.first->curve()->mnemonic());
    f_value.second->setPen(QPen(QColor(qrand() %255,qrand() %255,qrand() %255),2));
    m_chartView->chart()->addSeries(f_value.second);
    m_chartView->chart()->setAxisX(xAxis, f_value.second);   // Назначить ось xAxis, осью X для diagramA
    m_chartView->chart()->setAxisY(yAxis, f_value.second);

    m_modelOneWave->insertWaveInfo(OneWaveInfo{f_value.second,true,f_value.second->name(),
                                          f_value.second->pen().color().name(),0,0,0,0,0});
}

void OneWaveWidget::changeVerticalCoord(int downValue ,int upValue){
    yAxis->setRange(downValue, upValue);
}

void OneWaveWidget::changeHorizontalCoord(int downValue ,int upValue){
    xAxis->setRange(downValue, upValue);
}
