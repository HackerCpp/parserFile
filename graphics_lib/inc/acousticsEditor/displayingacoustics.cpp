#include "displayingacoustics.h"
#include <QGraphicsView>
#include <QGraphicsScene>
#include "acousticsEditor/countingacousticsitem.h"

DisplayingAcoustics::DisplayingAcoustics(DataCountingAcoustics *dataCounting)
    : m_dataAcoustic(dataCounting)
{
    m_acuView = QPointer<AcuView>(new AcuView(dataCounting));
    m_widgetSelectingWaveSegment = QPointer<WidgetSelectWaveSegment>(new WidgetSelectWaveSegment(m_dataAcoustic));
    m_vMainSplitter = new QSplitter(Qt::Vertical);
    m_sliderWidth = new QSlider(Qt::Horizontal,this);
    m_sliderWidth->setRange(100,10000);

    m_vMainSplitter->addWidget(m_sliderWidth);
    m_vMainSplitter->addWidget(m_acuView);
    m_vMainSplitter->addWidget(m_widgetSelectingWaveSegment);

    m_vMainLayout = QPointer<QVBoxLayout>(new QVBoxLayout);
    m_vMainLayout->addWidget(m_vMainSplitter);


    this->setLayout(m_vMainLayout);

    connect(m_sliderWidth,&QSlider::valueChanged,m_acuView,&AcuView::changeWidth);
    connect(m_acuView,&AcuView::sig_changePositionOneWave,
            m_widgetSelectingWaveSegment,&WidgetSelectWaveSegment::update);
}
