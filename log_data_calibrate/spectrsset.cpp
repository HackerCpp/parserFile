#include "spectrsset.h"
#include "onewavewidget.h"
#include "icurve.h"
#include "QCheckBox"
#include <QMouseEvent>
#include <QWheelEvent>
#include "sqlite3saver.h"
#include <memory>

SpectrsSet::SpectrsSet(ICurve *curve,QWidget *parent)
    : QWidget(parent),m_originalSpectr(curve),m_referenceSpectr(nullptr)
{
    int f_sizeSpectrums = curve->size() / curve->sizeOffset();
    m_useVector = new QVector<Qt::CheckState>(f_sizeSpectrums + 1,Qt::Checked);
    m_resultSpectr = ICurve::curveCreater(*m_originalSpectr);
    m_resultSpectr->setMnemonic("resultSpectrum(DB)");
    m_mainSplitter = new QSplitter(Qt::Vertical);
    m_mainHLayout = new QHBoxLayout;
    m_slider = new QSlider(Qt::Vertical);
    m_oneWave = new OneWaveWidget(m_originalSpectr);
    m_oneWave->addCurve(m_resultSpectr);
    m_widgetInfo = new QWidget;
    m_layoutInfo = new QHBoxLayout;
    m_spinNumber = new QSpinBox;
    m_checkBox = new QCheckBox(tr("Use"));
    m_btnLoadReference = new QPushButton(tr("Load reference"));
    m_btnSaveResult = new QPushButton(tr("Save Result"));
    m_widgetInfo->setLayout(m_layoutInfo);
    m_layoutInfo->addWidget(m_spinNumber);
    m_layoutInfo->addWidget(m_checkBox);
    m_layoutInfo->addWidget(m_btnLoadReference);
    m_layoutInfo->addWidget(m_btnSaveResult);

    m_slider->setRange(0,f_sizeSpectrums );
    m_slider->setPageStep(1);
    m_spinNumber->setRange(0,f_sizeSpectrums);

    m_mainSplitter->addWidget(m_widgetInfo);
    m_mainSplitter->addWidget(m_oneWave);
    m_mainSplitter->addWidget(new QWidget);


    m_mainHLayout->addWidget(m_mainSplitter);
    m_mainHLayout->addWidget(m_slider);
    setLayout(m_mainHLayout);

    connect(m_slider,&QSlider::valueChanged,this,&SpectrsSet::changePosition);
    connect(m_spinNumber,qOverload<int>(&QSpinBox::valueChanged),this,&SpectrsSet::changePosition);
    connect(m_checkBox,&QCheckBox::clicked,this,&SpectrsSet::useSpectrumsChange);
    connect(m_btnLoadReference,&QPushButton::released,this,&SpectrsSet::loadReference);
    connect(m_btnSaveResult,&QPushButton::released,this,&SpectrsSet::saveResult);

    calculateAccumulationMaximum();
}

void SpectrsSet::changePosition(int value){
    m_checkBox->setCheckState(m_useVector->operator[](value));
    m_spinNumber->setValue(value);
    m_slider->setValue(value);
    m_oneWave->update(value);
}

void SpectrsSet::useSpectrumsChange(bool toggled){
    m_useVector->replace(m_spinNumber->value(),m_checkBox->checkState());
    calculateAccumulationMaximum();
}

void SpectrsSet::calculateAccumulationMaximum(){
    int f_spectrums = m_resultSpectr->size() / m_resultSpectr->sizeOffset();
    int f_offset = m_resultSpectr->sizeOffset();
    QVector<qreal> f_maximumValues(f_offset,-120);
    for(int y = 0; y < f_spectrums; ++y){
        if(m_useVector->at(y) == Qt::Unchecked)
            for(int x = 0; x < f_offset; ++x){
                int f_curInd = y * f_offset + x;
                m_resultSpectr->setData(f_maximumValues[x],f_curInd);
            }
        else
            for(int x = 0; x < f_offset; ++x){
                int f_curInd = y * f_offset + x;
                if(f_maximumValues[x] < m_originalSpectr->data(f_curInd))
                    f_maximumValues[x] = m_originalSpectr->data(f_curInd);
                m_resultSpectr->setData(f_maximumValues[x],f_curInd);
            }
    }
}

void SpectrsSet::mousePressEvent(QMouseEvent *event){
    if(event->button() == Qt::RightButton){
        m_checkBox->setCheckState(m_checkBox->checkState() ? Qt::Unchecked : Qt::Checked);
        useSpectrumsChange(false);
    }
}

void SpectrsSet::wheelEvent(QWheelEvent *event){
        uint f_value = m_slider->value() + (event->angleDelta().y() > 0 ? 1 : -1);
        m_slider->setValue(f_value);
}

void SpectrsSet::loadReference(){

}

void SpectrsSet::saveResult(){
    if(!m_resultSpectr)
        return;
    auto f_saverDB = std::make_unique<SQLite3Saver>();
    //SQLite3Saver *f_saverDB = new SQLite3Saver();
    f_saverDB->saveCurve(*m_resultSpectr);
}
