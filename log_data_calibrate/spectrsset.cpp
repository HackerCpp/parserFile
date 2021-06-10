#include "spectrsset.h"
#include "onewavewidget.h"
#include "icurve.h"
#include "QCheckBox"
#include <QMouseEvent>
#include <QWheelEvent>
#include <memory>
#include "referenceLoader.h"
#include "QMessageBox"
#include <QDebug>
#include <QComboBox>
#include <referencesaver.h>
#include "customprogressbar.h"
#include "saverloadercalibdb.h"
#include "protocolnoise.h"

SpectrsSet::SpectrsSet(ICurve *curve,QWidget *parent)
    : QWidget(parent),m_coeffs(nullptr),
      m_originalSpectr(curve),m_referenceSpectrMAX(nullptr),
      m_referenceSpectrAVER(nullptr)
{
    m_idReference = m_idOriginal = 0;
     int f_sizeSpectrums = curve->size() / curve->sizeOffset();
    m_useVectorMaximum = new QVector<Qt::CheckState>(f_sizeSpectrums + 1,Qt::Checked);
    m_useVectorAverage = new QVector<Qt::CheckState>(f_sizeSpectrums + 1,Qt::Checked);
    m_duplicateSpectr = ICurve::curveCreater(*m_originalSpectr);
    m_duplicateSpectr->setMnemonic("duplicateSpectrum(DB)");
    m_recalcSpectrMAX = ICurve::curveCreater(*m_duplicateSpectr);
    m_recalcSpectrMAX->setMnemonic("recalcSpectrumMAX(DB)");
    m_recalcSpectrAVER = ICurve::curveCreater(*m_duplicateSpectr);
    m_recalcSpectrAVER->setMnemonic("recalcSpectrumAVER(DB)");
    m_resultSpectrMAX = ICurve::curveCreater(*m_originalSpectr);
    m_resultSpectrMAX->setMnemonic("resultSpectrumMAX(DB)");
    m_resultSpectrAVER = ICurve::curveCreater(*m_originalSpectr);
    m_resultSpectrAVER->setMnemonic("resultSpectrumAVER(DB)");
    m_mainSplitter = new QSplitter(Qt::Vertical);
    m_mainHLayout = new QHBoxLayout;
    m_slider = new QSlider(Qt::Vertical);
    m_oneWave = new OneWaveWidget(m_duplicateSpectr);
    m_oneWave->addCurve(m_originalSpectr);
    m_oneWave->addCurve(m_resultSpectrAVER);
    m_oneWave->addCurve(m_resultSpectrMAX);
    m_oneWave->addCurve(m_recalcSpectrAVER);
    m_oneWave->addCurve(m_recalcSpectrMAX);
    m_widgetInfo = new QWidget;
    m_layoutInfo = new QHBoxLayout;
    m_spinNumber = new QSpinBox;
    m_coeffDispl = new CoefficientsDisplaying();
    m_checkBox = new QCheckBox(tr("Use"));
    m_comboMode = new QComboBox();
    m_comboMode->addItem(tr("Maximum"));
    m_comboMode->addItem(tr("Average"));
    m_btnLoadReference = new QPushButton(tr("Load reference"));
    m_btnSaveResult = new QPushButton(tr("Save Result"));
    m_btnCalcCoeffs = new QPushButton(tr("Calc coeffs"));
    m_btnApplyOrigin = new QPushButton(tr("Apply origin"));
    //m_btnSaveCalib = new QPushButton(tr("Save calib"));
    m_btnOpenProtocol = new QPushButton(tr("Open protocol"));
    m_btnLoadCoeffs = new QPushButton(tr("Load coeffs"));
    m_btnCalcResult = new QPushButton(tr("Calc result"));
    m_widgetInfo->setLayout(m_layoutInfo);
    m_layoutInfo->addWidget(m_spinNumber);
    m_layoutInfo->addWidget(m_checkBox);
    m_layoutInfo->addWidget(m_comboMode);
    m_layoutInfo->addWidget(m_btnCalcResult);
    m_layoutInfo->addWidget(m_btnLoadReference);
    m_layoutInfo->addWidget(m_btnSaveResult);
    m_layoutInfo->addWidget(m_btnCalcCoeffs);
    m_layoutInfo->addWidget(m_btnApplyOrigin);
    //m_layoutInfo->addWidget(m_btnSaveCalib);
    m_layoutInfo->addWidget(m_btnOpenProtocol);
    m_layoutInfo->addWidget(m_btnLoadCoeffs);
    m_btnApplyOrigin->setEnabled(false);

    m_slider->setRange(0,f_sizeSpectrums );
    m_slider->setPageStep(1);
    m_spinNumber->setRange(0,f_sizeSpectrums);

    m_mainSplitter->addWidget(m_widgetInfo);
    m_mainSplitter->addWidget(m_oneWave);
    m_mainSplitter->addWidget(m_coeffDispl);


    m_mainHLayout->addWidget(m_mainSplitter);
    m_mainHLayout->addWidget(m_slider);
    setLayout(m_mainHLayout);

    connect(m_slider,&QSlider::valueChanged,this,&SpectrsSet::changePosition);
    connect(m_spinNumber,qOverload<int>(&QSpinBox::valueChanged),this,&SpectrsSet::changePosition);
    connect(m_checkBox,&QCheckBox::clicked,this,&SpectrsSet::useSpectrumsChange);
    connect(m_btnLoadReference,&QPushButton::released,this,&SpectrsSet::loadReference);
    connect(m_btnSaveResult,&QPushButton::released,this,&SpectrsSet::saveResult);
    connect(m_btnCalcCoeffs,&QPushButton::released,this,&SpectrsSet::calcCoeffs);
    connect(m_btnApplyOrigin,&QPushButton::released,this,&SpectrsSet::applyOrigin);

    m_currentUseVector = m_useVectorMaximum;

    calcResult();

    connect(m_comboMode,&QComboBox::currentTextChanged,this,&SpectrsSet::changeCalcFun);
    //connect(m_btnSaveCalib,&QPushButton::released,this,&SpectrsSet::saveCalib);
    connect(m_btnOpenProtocol,&QPushButton::released,this,&SpectrsSet::openProtocol);
    connect(m_btnLoadCoeffs,&QPushButton::released,this,&SpectrsSet::loadCoeffs);
    connect(m_btnCalcResult,&QPushButton::released,this,&SpectrsSet::calcResult);

    m_menu.addAction (tr("Use all vectors"),this, SLOT(useAllVectors()));
    m_menu.addAction (tr("Remove all vectors"),this, SLOT(removeAllVectors()));
    m_menu.addAction (tr("Use all up"),this, SLOT(useAllUp()));
    m_menu.addAction (tr("Remove all up"),this, SLOT(removeAllUp()));
    m_menu.addAction (tr("Use all down"),this, SLOT(useAllDown()));
    m_menu.addAction (tr("Remove all down"),this, SLOT(removeAllDown()));

    m_btnCalcCoeffs->hide();
    m_btnApplyOrigin->hide();
    //m_btnSaveCalib->hide();
}

void SpectrsSet::changePosition(int value){
    m_checkBox->setCheckState(m_currentUseVector->operator[](value));
    m_spinNumber->setValue(value);
    m_slider->setValue(value);
    m_oneWave->update(value);
}

void SpectrsSet::useSpectrumsChange(bool toggled){
    m_currentUseVector->replace(m_spinNumber->value(),m_checkBox->checkState());
}

void SpectrsSet::calculateAccumulationMaximum(ICurve *spctrSrc,ICurve *spctrDst){
    if(!spctrSrc || !spctrDst)
        return;
    int f_spectrums = spctrDst->size() / spctrDst->sizeOffset();
    int f_offset = spctrDst->sizeOffset();
    QVector<qreal> f_maximumValues(f_offset,-120);
    CustomProgressBar f_progress;
    f_progress.setValue(0);
    f_progress.setText(tr("Accumulation maximum"));
    f_progress.show();
    qreal percent = 100.f / qreal(f_spectrums);
    for(int y = 0; y < f_spectrums; ++y){
        f_progress.setValue(y * percent);
        f_progress.move(QCursor::pos());
        if(m_useVectorMaximum->at(y) == Qt::Unchecked)
            for(int x = 0; x < f_offset; ++x){
                int f_curInd = y * f_offset + x;
                spctrDst->setData(f_maximumValues[x],f_curInd);
            }
        else
            for(int x = 0; x < f_offset; ++x){
                int f_curInd = y * f_offset + x;
                if(f_maximumValues[x] < spctrSrc->data(f_curInd))
                    f_maximumValues[x] = spctrSrc->data(f_curInd);
                spctrDst->setData(f_maximumValues[x],f_curInd);
            }
    }
}


void SpectrsSet::calculateAccumulationAverage(ICurve *spctrSrc,ICurve *spctrDst){
    if(!spctrSrc || !spctrDst)
        return;
    int f_spectrums = spctrDst->size() / spctrDst->sizeOffset();
    int f_offset = spctrDst->sizeOffset();
    QVector<qreal> f_averageValues(f_offset,0);
    CustomProgressBar f_progress;
    f_progress.setValue(0);
    f_progress.setText(tr("Averaging calculation"));
    f_progress.show();
    qreal percent = 100.f / qreal(f_spectrums);
    for(int currentY = 0; currentY < f_spectrums; ++currentY){
        f_progress.setValue(currentY * percent);
        f_progress.move(QCursor::pos());
        if(m_useVectorAverage->at(currentY) == Qt::Checked){
            f_averageValues.fill(0,f_averageValues.size());
            qreal f_quantitySpectrums = currentY + 1;
            for(int y = 0; y < currentY; ++y){
                if(m_useVectorAverage->at(y) == Qt::Unchecked)
                    --f_quantitySpectrums;
            }
            qreal f_coef = 1.f / f_quantitySpectrums;
            for(int y = 0; y <= currentY; ++y){
                if(m_useVectorAverage->at(y) == Qt::Checked)
                    for(int x = 0; x < f_offset; ++x){
                        int f_curInd = y * f_offset + x;
                        f_averageValues[x] += spctrSrc->data(f_curInd) * f_coef;
                    }
            }
        }
        for(int x = 0; x < f_offset; ++x){
            int f_curInd = currentY * f_offset + x;
            spctrDst->setData(f_averageValues[x],f_curInd);
        }
    }
}

void SpectrsSet::mousePressEvent(QMouseEvent *event){
    if(event->button() == Qt::RightButton){
        m_checkBox->setCheckState(m_checkBox->checkState() ? Qt::Unchecked : Qt::Checked);
        useSpectrumsChange(false);
    }
}

void SpectrsSet::mouseDoubleClickEvent(QMouseEvent *event){
    if(event->button() == Qt::RightButton){
        m_menu.move(QCursor::pos());
        m_menu.show();
    }
}

void SpectrsSet::wheelEvent(QWheelEvent *event){
        uint f_value = m_slider->value() + (event->angleDelta().y() > 0 ? 1 : -1);
        m_slider->setValue(f_value);
}

void SpectrsSet::showCoeffs(){
   QList<QPointF> f_coeffsA;
   QList<QPointF> f_coeffsB;
   int f_y = 0;
   for(auto&& [coef_a,coef_b] : *m_coeffs){
       f_coeffsA.push_back(QPointF(f_y,coef_a));
       f_coeffsB.push_back(QPointF(f_y++,coef_b));
   }
   m_coeffDispl->addCoeffs(f_coeffsA,f_coeffsB);

}

void SpectrsSet::loadReference(){
    ICurve *f_refMaxCurve = nullptr,*f_refAverCurve = nullptr;
    auto f_loaderDB = std::make_unique<SaverLoaderCalibDB>();
    f_loaderDB->loadReference(m_originalSpectr->sizeOffset(),m_originalSpectr->desc()->param("data_step"),f_refMaxCurve,f_refAverCurve);

    if(f_refMaxCurve && f_refAverCurve){
        if(m_referenceSpectrMAX)
            m_oneWave->removeLastCurve();
        if(m_referenceSpectrAVER)
            m_oneWave->removeLastCurve();
        m_referenceSpectrMAX = f_refMaxCurve;
        m_referenceSpectrMAX->setMnemonic("refMAXIMUM(DB)");
        m_oneWave->addCurve(m_referenceSpectrMAX);
        m_referenceSpectrAVER = f_refAverCurve;
        m_referenceSpectrAVER->setMnemonic("refAVERAGE(DB)");
        m_oneWave->addCurve(m_referenceSpectrAVER);
        m_btnCalcCoeffs->show();
    }
}

void SpectrsSet::saveResult(){
    if(!m_resultSpectrMAX || !m_resultSpectrAVER)
        return;
    auto f_saverDB = std::make_unique<SaverLoaderCalibDB>();
    f_saverDB->saveReference(*m_resultSpectrMAX,*m_resultSpectrAVER);
}

void SpectrsSet::calcCoeffs(){
    if(!m_resultSpectrMAX || !m_resultSpectrAVER || !m_referenceSpectrMAX || !m_referenceSpectrAVER){
        QMessageBox::warning(this,tr("Calc coeffs"),tr("Download the reference spectrum \n click the 'Load reference' button"));
        return;
    }
    if(m_resultSpectrMAX->sizeOffset() != m_referenceSpectrMAX->sizeOffset()){
        QMessageBox::warning(this,tr("Calc coeffs"),tr("The number of bands of the reference \n spectrum does not match the current one"));
        return;
    }
    if(!m_coeffs)
        m_coeffs = new QVector<CoeffsLinearDependence>(m_resultSpectrMAX->sizeOffset());
    int f_sizeOffset = m_resultSpectrMAX->sizeOffset();
    int f_indexBeginResultSpectrumMAX =  m_resultSpectrMAX->size() - f_sizeOffset;
    int f_indexBeginResultSpectrumAVER =  m_resultSpectrAVER->size() - f_sizeOffset;
    int f_indexBeginRefSpectrumMAX = m_referenceSpectrMAX->size() - f_sizeOffset;
    int f_indexBeginRefSpectrumAVER = m_referenceSpectrAVER->size() - f_sizeOffset;
    for(int i = 0; i < f_sizeOffset; ++i){
        calcCoeffLinePolinom(m_resultSpectrMAX->data(f_indexBeginResultSpectrumMAX + i),
                             m_resultSpectrAVER->data(f_indexBeginResultSpectrumAVER + i),
                             m_referenceSpectrMAX->data(f_indexBeginRefSpectrumMAX + i),
                             m_referenceSpectrAVER->data(f_indexBeginRefSpectrumAVER + i),
                             m_coeffs->operator[](i));
    }
    m_btnApplyOrigin->setEnabled(true);
    applyCoeffsDuplicateSpectrum();
    showCoeffs();
    m_btnOpenProtocol->show();
}

void SpectrsSet::changeCalcFun(QString text){
    if(text == tr("Maximum")){
        m_currentUseVector = m_useVectorMaximum;
    }
    else if (text == tr("Average")){
        m_currentUseVector = m_useVectorAverage;
    }
}

void SpectrsSet::applyCoeffsDuplicateSpectrum(){
    if(!m_coeffs)
        return;

    int f_spectrums = m_duplicateSpectr->size() / m_duplicateSpectr->sizeOffset();
    int f_offset = m_duplicateSpectr->sizeOffset();
    for(int currentY = 0; currentY < f_spectrums; ++currentY){
        for(int x = 0; x < f_offset; ++x){
            int f_curInd = currentY * f_offset + x;
            qreal f_data = m_originalSpectr->data(f_curInd) * m_coeffs->at(x).k_a + m_coeffs->at(x).k_b;
            m_duplicateSpectr->setData(f_data,f_curInd);
        }
    }
    calcResult();
}

void SpectrsSet::applyOrigin(){
    int f_spectrums = m_duplicateSpectr->size() / m_duplicateSpectr->sizeOffset();
    int f_offset = m_duplicateSpectr->sizeOffset();
    for(int currentY = 0; currentY < f_spectrums; ++currentY){
        for(int x = 0; x < f_offset; ++x){
            int f_curInd = currentY * f_offset + x;
            m_originalSpectr->setData(m_duplicateSpectr->data(f_curInd),f_curInd);
        }
    }
}


void SpectrsSet::calcCoeffLinePolinom(qreal x1,qreal x2,qreal y1,qreal y2,CoeffsLinearDependence &k){
    k.k_a = (y2 - y1) / (x2 - x1);
    k.k_b = y1 - x1 * k.k_a;
}

/*void SpectrsSet::saveCalib(){
    if(!m_originalSpectr || !m_coeffs || m_coeffs->isEmpty()){
        return;
    }
    if(!m_referenceSpectrMAX || !m_referenceSpectrAVER){
        return;
    }

    bool bOk;
    QString f_operatorName = QInputDialog::getText( 0, tr("Operator name:(last name first name patronymic)"),"",QLineEdit::Normal,"",&bOk);
    Operator f_operator(f_operatorName);

    auto f_saverDB = std::make_unique<SaverLoaderCalibDB>();
    //f_saverDB->saveNoiseProtocol(f_noiseProtocol);

}*/

void SpectrsSet::openProtocol(){
    if(!m_originalSpectr || !m_coeffs || m_coeffs->isEmpty()){
        return;
    }
    if(!m_referenceSpectrMAX || !m_referenceSpectrAVER){
        return;
    }

    bool bOk;
    QString f_operatorName = QInputDialog::getText( 0, tr("Operator name:(last name first name patronymic)"),"",QLineEdit::Normal,"",&bOk);
    Operator f_operator(f_operatorName);
    ProtocolNoise *f_noiseProtocol = new ProtocolNoise();
    f_noiseProtocol->addReference(m_referenceSpectrMAX,m_referenceSpectrAVER);
    f_noiseProtocol->addCurrent(m_resultSpectrMAX,m_resultSpectrAVER);
    f_noiseProtocol->addRecalc(m_recalcSpectrMAX,m_recalcSpectrAVER);
    f_noiseProtocol->addCoeffs(m_coeffs);
    f_noiseProtocol->addChannelName(m_originalSpectr->mnemonic());
    f_noiseProtocol->addOperator(f_operator);
    f_noiseProtocol->createPDF();
}

void SpectrsSet::loadCoeffs(){

}

void SpectrsSet::calcResult(){
    if(m_originalSpectr && m_resultSpectrMAX && m_resultSpectrAVER){
        calculateAccumulationAverage(m_originalSpectr,m_resultSpectrAVER);
        calculateAccumulationMaximum(m_originalSpectr,m_resultSpectrMAX);
    }
    if(m_duplicateSpectr && m_recalcSpectrMAX && m_recalcSpectrAVER){
        calculateAccumulationAverage(m_duplicateSpectr,m_recalcSpectrAVER);
        calculateAccumulationMaximum(m_duplicateSpectr,m_recalcSpectrMAX);
    }
}

void SpectrsSet::useAllVectors(){
    if(!m_currentUseVector)
        return;
    m_currentUseVector->fill(Qt::Checked);
}

void SpectrsSet::removeAllVectors(){
    if(!m_currentUseVector)
        return;
    m_currentUseVector->fill(Qt::Unchecked);
}

void SpectrsSet::useAllUp(){
    if(!m_currentUseVector)
        return;
    for(int i = m_slider->value();i < m_currentUseVector->size();++i)
        m_currentUseVector->operator[](i) = Qt::Checked;
}

void SpectrsSet::removeAllUp(){
    if(!m_currentUseVector)
        return;
    for(int i = m_slider->value();i < m_currentUseVector->size();++i)
        m_currentUseVector->operator[](i) = Qt::Unchecked;
}

void SpectrsSet::useAllDown(){
    if(!m_currentUseVector)
        return;
    for(int i = 0;i <= m_slider->value();++i)
        m_currentUseVector->operator[](i) = Qt::Checked;
}

void SpectrsSet::removeAllDown(){
    if(!m_currentUseVector)
        return;
    for(int i = 0;i <= m_slider->value();++i)
        m_currentUseVector->operator[](i) = Qt::Unchecked;
}
