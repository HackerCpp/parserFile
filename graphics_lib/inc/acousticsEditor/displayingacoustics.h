#ifndef DISPLAYINGACOUSTICS_H
#define DISPLAYINGACOUSTICS_H
#include "datacountingacoustics.h"
#include <QWidget>
#include <QVBoxLayout>
#include "acuview.h"
#include <QSlider>
#include "widgetselectwavesegment.h"

class DisplayingAcoustics : public QWidget
{
    DataCountingAcoustics *m_dataAcoustic;
    QPointer<AcuView> m_acuView;
    QPointer<WidgetSelectWaveSegment> m_widgetSelectingWaveSegment;
    QSlider *m_sliderWidth;

    QSplitter *m_vMainSplitter;
    QPointer<QVBoxLayout> m_vMainLayout;
public:
    DisplayingAcoustics(DataCountingAcoustics *dataCounting);
    ~DisplayingAcoustics(){}

    QPair<int,int> leftAndRightBandAcuOne(){return m_widgetSelectingWaveSegment->leftAndRightBandAcuOne();}
    QPair<int,int> leftAndRightBandAcuTwo(){return m_widgetSelectingWaveSegment->leftAndRightBandAcuTwo();}
    qreal ampAcuOne(){return m_widgetSelectingWaveSegment->ampAcuOne();}
    qreal ampAcuTwo(){return m_widgetSelectingWaveSegment->ampAcuTwo();}
    int currentWidth(){return m_sliderWidth->value();}


};

#endif // DISPLAYINGACOUSTICS_H
