#include "widgetselectwavesegment.h"


WidgetSelectWaveSegment::WidgetSelectWaveSegment(QVector<VAcuItem *> acuItems)
    :m_acuItems(acuItems){
    m_hSplitter = new QSplitter;
    m_sliderAmplitude = new QxtSpanSlider(Qt::Vertical);
    m_chartViews = new QVector<ChartViewSelectSegment *>;
    m_series = new QVector<QLineSeries *>;
    m_sliderMicroSec = new QVector<QxtSpanSlider *>;

    m_vLayout = new QVBoxLayout;
    m_vLayout->setMargin(0);

    m_graphicsWidgets = new QVector<QWidget *>;
    m_vLayouts = new QVector<QVBoxLayout *>;

    xAxis = new QVector<QValueAxis *>;
    yAxis = new QVector<QValueAxis *>;

    m_hSplitter->addWidget(m_sliderAmplitude);

    QString valueRange = m_acuItems.last()->curve()->desc()->param("val_range");
    int f_minimum = valueRange.left(valueRange.indexOf("..")).toDouble();
    int f_maximum = valueRange.mid(valueRange.indexOf("..") + 2).toDouble();
    m_sliderAmplitude->setRange(f_minimum,f_maximum);
    m_sliderAmplitude->setSpan(m_sliderAmplitude->minimum(),m_sliderAmplitude->maximum());


//Вставляем отрисовку сбоку всех акустик, слева направо

    foreach(auto acuItem,m_acuItems){
        m_chartViews->push_back(new ChartViewSelectSegment(this));
        m_chartViews->last()->installEventFilter(this);
        m_chartViews->last()->chart()->setTheme(QChart::ChartThemeDark);
        //m_chartViews->last()->chart()->setTheme(QChart::ChartThemeLight);
        m_series->push_back(new QLineSeries(this));

        m_series->last()->setName(acuItem->curve()->mnemonic());
        AcuItem *f_itemInfo = dynamic_cast<AcuItem *>(acuItem->itemInfo());
        if(f_itemInfo)
            m_series->last()->setPen(QPen(QColor(f_itemInfo->transparentColor()),2));
        else
            m_series->last()->setPen(QPen(Qt::green,2));

        m_sliderMicroSec->push_back(new QxtSpanSlider(Qt::Horizontal));
        qreal f_dataStep  = acuItem->dataStep();
        m_sliderMicroSec->last()->setRange(-10,acuItem->curve()->sizeOffset() * f_dataStep + 10);
        m_sliderMicroSec->last()->setSpan(m_sliderMicroSec->last()->minimum(),m_sliderMicroSec->last()->maximum());

        m_graphicsWidgets->push_back(new QWidget());
        m_vLayouts->push_back(new QVBoxLayout);
        m_vLayouts->last()->setMargin(0);

        QValueAxis *f_xAxis = new QValueAxis;
        xAxis->push_back(f_xAxis);
        xAxis->last()->setRange(m_sliderMicroSec->last()->minimum(),m_sliderMicroSec->last()->maximum());
        xAxis->last()->setTitleText(tr("mkSec"));
        xAxis->last()->setTitleBrush(Qt::magenta);
        xAxis->last()->setLabelsColor(Qt::magenta);
        xAxis->last()->setTickCount(6);

        yAxis->push_back(new QValueAxis);
        yAxis->last()->setRange(m_sliderAmplitude->minimum(), m_sliderAmplitude->maximum());
        yAxis->last()->setTitleText(tr("Amplitude"));
        yAxis->last()->setTitleBrush(Qt::yellow);
        yAxis->last()->setLabelsColor(Qt::yellow);
        yAxis->last()->setTickCount(10);

        m_chartViews->last()->chart()->addSeries(m_series->last());
        m_chartViews->last()->chart()->setAxisX(xAxis->last(), m_series->last());
        m_chartViews->last()->chart()->setAxisY(yAxis->last(), m_series->last());
        //m_chartViews->last()->chart()->addAxis(xAxis->last(),Qt::AlignBottom);
        //m_chartViews->last()->chart()->addAxis(yAxis->last(),Qt::AlignLeft);

        m_vLayouts->last()->addWidget(m_chartViews->last());
        m_vLayouts->last()->addWidget(m_sliderMicroSec->last());
        m_graphicsWidgets->last()->setLayout(m_vLayouts->last());
        m_hSplitter->addWidget(m_graphicsWidgets->last());

        connect(m_sliderMicroSec->last(),&QxtSpanSlider::spanChanged,[=](int min,int max){f_xAxis->setRange(min,max);chartResize();});
    }

    m_vLayout->addWidget(m_hSplitter);
    setLayout(m_vLayout);

    connect(m_sliderAmplitude,&QxtSpanSlider::spanChanged,this,&WidgetSelectWaveSegment::changeVerticalCoord);
}

bool WidgetSelectWaveSegment::eventFilter(QObject *object, QEvent *event)
{
    foreach(auto chart,*m_chartViews){
        if (object == chart && event->type() == QEvent::Resize) {
                chartResize();
                return false;
        }
    }

    return false;
}

void WidgetSelectWaveSegment::update(QPoint scenePoint){ //Добавляет точки из SpectrItem по координатам на сцене
    bool f_flag = false;
    for(int i = 0;i < m_acuItems.size();++i){
        m_series->operator[](i)->replace(m_acuItems[i]->oneWave(scenePoint.y(),&f_flag));
    }
}

void WidgetSelectWaveSegment::chartResize(){
    foreach(auto chart,*m_chartViews)
        chart->resize();
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

QPair<int,int> WidgetSelectWaveSegment::leftAndRightBandAcu(int index){
    if(index >= m_chartViews->size())
        return QPair<int,int>(0,0);
    return leftAndRightBand(m_chartViews->operator[](index),m_series->operator[](index));
}

qreal WidgetSelectWaveSegment::ampAcu(int index){
    if(index >= m_chartViews->size())
        return 0;
    return m_chartViews->operator[](index)->ampLine();
}

void WidgetSelectWaveSegment::changeVerticalCoord(int downValue ,int upValue){
    foreach(auto y,*yAxis){
        y->setRange(downValue, upValue);
    }
    chartResize();
}
