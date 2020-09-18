#include "widgetselectwavesegment.h"
#include "vacuitem.h"

WidgetSelectWaveSegment::WidgetSelectWaveSegment(DataCountingAcoustics *dataAcu)
    : m_dataAcu(dataAcu){
    m_hSplitter = new QSplitter;
    m_sliderAmplitude = new QxtSpanSlider(Qt::Vertical);
    m_chartViewOne = new ChartViewSelectSegment(this);
    m_chartViewTwo = new ChartViewSelectSegment(this);
    m_oneSeries = new QLineSeries(this);
    m_twoSeries = new QLineSeries(this);
    m_chartViewOne->installEventFilter(this);
    m_chartViewTwo->installEventFilter(this);

    m_chartViewOne->chart()->setTheme(QChart::ChartThemeDark);
    m_chartViewTwo->chart()->setTheme(QChart::ChartThemeDark);
    VAcuItem *f_acuItem = nullptr;
    if(m_dataAcu->item(DataCountingAcoustics::ACU_ONE)){
        f_acuItem = dynamic_cast<VAcuItem *>(m_dataAcu->item(DataCountingAcoustics::ACU_ONE));
    }
    else if(m_dataAcu->item(DataCountingAcoustics::ACU_TWO)){
        f_acuItem = dynamic_cast<VAcuItem *>(m_dataAcu->item(DataCountingAcoustics::ACU_TWO));
    }
    if(!f_acuItem)
        return;

    QString valueRange = f_acuItem->curve()->desc()->param("val_range");
    int f_minimum = valueRange.left(valueRange.indexOf("..")).toDouble();
    int f_maximum = valueRange.mid(valueRange.indexOf("..") + 2).toDouble();
    m_sliderAmplitude->setRange(f_minimum,f_maximum);
    m_sliderAmplitude->setSpan(m_sliderAmplitude->minimum(),m_sliderAmplitude->maximum());

    m_sliderFrequencyOne = new QxtSpanSlider(Qt::Horizontal);
    m_sliderFrequencyTwo = new QxtSpanSlider(Qt::Horizontal);
    qreal f_dataStep  = f_acuItem->dataStep();

    m_sliderFrequencyOne->setRange(-1,f_acuItem->curve()->sizeOffset() * f_dataStep + 1);
    m_sliderFrequencyOne->setSpan(m_sliderFrequencyOne->minimum(),m_sliderFrequencyOne->maximum());
    m_sliderFrequencyTwo->setRange(-1,f_acuItem->curve()->sizeOffset() * f_dataStep + 1);
    m_sliderFrequencyTwo->setSpan(m_sliderFrequencyTwo->minimum(),m_sliderFrequencyTwo->maximum());

    m_vLayout = new QVBoxLayout;
    m_graphicsWidgetOne = new QWidget();
    m_graphicsWidgetTwo = new QWidget();
    m_vLayoutOne = QPointer<QVBoxLayout>(new QVBoxLayout);
    m_vLayoutTwo = QPointer<QVBoxLayout>(new QVBoxLayout);

    xAxisOne = new QValueAxis;
    xAxisOne->setRange(m_sliderFrequencyOne->minimum(), m_sliderFrequencyOne->maximum());
    xAxisOne->setTitleText(tr("Lines Hz"));
    xAxisOne->setTitleBrush(Qt::magenta);
    xAxisOne->setLabelsColor(Qt::magenta);
    xAxisOne->setTickCount(10);
    xAxisTwo = new QValueAxis;
    xAxisTwo->setRange(m_sliderFrequencyTwo->minimum(), m_sliderFrequencyTwo->maximum());
    xAxisTwo->setTitleText(tr("Lines Hz"));
    xAxisTwo->setTitleBrush(Qt::magenta);
    xAxisTwo->setLabelsColor(Qt::magenta);
    xAxisTwo->setTickCount(10);

    yAxisOne = new QValueAxis;
    yAxisOne->setRange(m_sliderAmplitude->minimum(), m_sliderAmplitude->maximum());
    yAxisOne->setTitleText(tr("Amplitude"));
    yAxisOne->setTitleBrush(Qt::yellow);
    yAxisOne->setLabelsColor(Qt::yellow);

    yAxisTwo = new QValueAxis;
    yAxisTwo->setRange(m_sliderAmplitude->minimum(), m_sliderAmplitude->maximum());
    yAxisTwo->setTitleText(tr("Amplitude"));
    yAxisTwo->setTitleBrush(Qt::yellow);
    yAxisTwo->setLabelsColor(Qt::yellow);

    m_oneSeries->setName(tr("Acu 1"));
    m_twoSeries->setName(tr("Acu 2"));
    m_oneSeries->setPen(QPen(Qt::red,2));
    m_twoSeries->setPen(QPen(Qt::red,2));



    m_chartViewOne->chart()->addSeries(m_oneSeries);
    m_chartViewOne->chart()->setAxisX(xAxisOne, m_oneSeries);
    m_chartViewOne->chart()->setAxisY(yAxisOne, m_oneSeries);

    m_chartViewTwo->chart()->addSeries(m_twoSeries);
    m_chartViewTwo->chart()->setAxisX(xAxisTwo, m_twoSeries);
    m_chartViewTwo->chart()->setAxisY(yAxisTwo, m_twoSeries);

    m_vLayoutOne->addWidget(m_chartViewOne);
    m_vLayoutOne->addWidget(m_sliderFrequencyOne);
    m_vLayoutTwo->addWidget(m_chartViewTwo);
    m_vLayoutTwo->addWidget(m_sliderFrequencyTwo);
    m_graphicsWidgetOne->setLayout(m_vLayoutOne);
    m_graphicsWidgetTwo->setLayout(m_vLayoutTwo);

    m_hSplitter->addWidget(m_sliderAmplitude);
    m_hSplitter->addWidget(m_graphicsWidgetOne);
    m_hSplitter->addWidget(m_graphicsWidgetTwo);


    m_vLayout->addWidget(m_hSplitter);

    setLayout(m_vLayout);

    connect(m_sliderAmplitude,&QxtSpanSlider::spanChanged,this,&WidgetSelectWaveSegment::changeVerticalCoord);
    connect(m_sliderFrequencyOne,&QxtSpanSlider::spanChanged,this,&WidgetSelectWaveSegment::changeHorizontalCoordOne);
    connect(m_sliderFrequencyTwo,&QxtSpanSlider::spanChanged,this,&WidgetSelectWaveSegment::changeHorizontalCoordTwo);
}

bool WidgetSelectWaveSegment::eventFilter(QObject *object, QEvent *event)
{
    if (object == m_chartViewOne || object == m_chartViewTwo && event->type() == QEvent::Resize) {
            chartResize();
            return false;
    }
    return false;
}

void WidgetSelectWaveSegment::update(QPoint scenePoint){ //Добавляет точки из SpectrItem по координатам на сцене
    bool f_flag = false;
    VAcuItem *f_acu = dynamic_cast<VAcuItem *>(m_dataAcu->item(DataCountingAcoustics::ACU_ONE));
    if(f_acu){
        m_oneSeries->replace(f_acu->oneWave(scenePoint.y(),&f_flag));
    }
    f_acu = dynamic_cast<VAcuItem *>(m_dataAcu->item(DataCountingAcoustics::ACU_TWO));
    if(f_acu){
        m_twoSeries->replace(f_acu->oneWave(scenePoint.y(),&f_flag));
    }
}

void WidgetSelectWaveSegment::chartResize(){
    if(m_chartViewOne)
        m_chartViewOne->resize();
    if(m_chartViewTwo)
        m_chartViewTwo->resize();
}

void WidgetSelectWaveSegment::wheelEvent(QWheelEvent *event){
    if(event->angleDelta().y() < 0){
        m_sliderAmplitude->setLowerValue(m_sliderAmplitude->lowerValue() - 100);
        m_sliderAmplitude->setUpperValue(m_sliderAmplitude->upperValue() + 100);
    }
    else{
        m_sliderAmplitude->setLowerValue(m_sliderAmplitude->lowerValue() + 100);
        m_sliderAmplitude->setUpperValue(m_sliderAmplitude->upperValue() - 100);
    }
}

QPair<int,int> leftAndRightBand(ChartViewSelectSegment *m_chartView,QLineSeries *series){

    int f_leftBand = 0;
    int f_rightBand = 0;
    qreal f_leftLinePos = m_chartView->posLeftLine();
    qreal f_rightLinePos = m_chartView->posRightLine();
    foreach(auto point,series->points()){
        if(point.x() >= f_leftLinePos){
            break;
        }
        ++f_leftBand;
    }

    foreach(auto point,series->points()){
        if(point.x() >= f_rightLinePos){
            break;
        }
        ++f_rightBand;
    }
    f_rightBand = f_rightBand < series->points().size() ? f_rightBand : series->points().size() - 1;
    f_leftBand = f_leftBand < series->points().size() ? f_leftBand : series->points().size() - 1;
    return QPair<int,int>(f_leftBand,f_rightBand);
}

QPair<int,int> WidgetSelectWaveSegment::leftAndRightBandAcuOne(){
    return leftAndRightBand(m_chartViewOne,m_oneSeries);
}

QPair<int,int> WidgetSelectWaveSegment::leftAndRightBandAcuTwo(){
    return leftAndRightBand(m_chartViewTwo,m_twoSeries);
}

void WidgetSelectWaveSegment::changeVerticalCoord(int downValue ,int upValue){
    yAxisOne->setRange(downValue, upValue);
    yAxisTwo->setRange(downValue, upValue);
    chartResize();
}

void WidgetSelectWaveSegment::changeHorizontalCoordOne(int downValue ,int upValue){
    xAxisOne->setRange(downValue,upValue);
    chartResize();
}

void WidgetSelectWaveSegment::changeHorizontalCoordTwo(int downValue ,int upValue){
    xAxisTwo->setRange(downValue,upValue);
    chartResize();
}
