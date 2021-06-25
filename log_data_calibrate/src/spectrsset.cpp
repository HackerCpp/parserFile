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
#include "customprogressbar.h"
#include "saverloadercalibdb.h"


SpectrsSet::SpectrsSet(ICurve *curve,QWidget *parent)
    : QWidget(parent),m_upCoeffs(nullptr),m_downCoeffs(nullptr),
      m_originalSpectr(curve)
{
    m_idReference = m_idOriginal = 0;

    m_duplicateSpectr = ICurve::curveCreater(*m_originalSpectr);
    m_duplicateSpectr->setMnemonic("duplicateSpectrum(DB)");

    m_mainSplitter = new QSplitter(Qt::Vertical);
    m_mainHLayout = new QHBoxLayout;
    m_slider = new QSlider(Qt::Vertical);
    m_oneWave = new OneWaveWidget(m_duplicateSpectr);
    m_oneWave->addCurve(m_originalSpectr);

    m_referMnemonics << tr("Reference_MIN(DB)") << tr("Reference_MAX(DB)") << tr("Reference_NOISE(DB)");;
    m_approximatedMnemonics << tr("Approximated_MIN(DB)") << tr("Approximated_MAX(DB)") << tr("Approximated_NOISE(DB)");
    m_sourceMnemonics << tr("Source_MIN(DB)") << tr("Source_MAX(DB)") << tr("Source_NOISE(DB)");
    int f_sizeSpectrums = curve->size() / curve->sizeOffset();
    for(int type = MINIMUM_SPECTRUM;type < TYPE_SPECTRUM_MAX; ++type){
        //Create recalculated Spectrums
        m_approximatedSpectrums[type] = ICurve::curveCreater(*m_duplicateSpectr);
        m_approximatedSpectrums[type]->setMnemonic(m_approximatedMnemonics.at(type));

        //Create sourse Spectrums
        m_sourceSpectrums[type] = ICurve::curveCreater(*m_originalSpectr);
        m_sourceSpectrums[type]->setMnemonic(m_sourceMnemonics.at(type));

        //Add to one Wave
        m_oneWave->addCurve(m_sourceSpectrums[type]);
        m_oneWave->addCurve(m_approximatedSpectrums[type]);

        m_useVectors[type] = new QVector<Qt::CheckState>(f_sizeSpectrums + 1,Qt::Checked);
    }

    m_widgetInfo = new QWidget;
    m_layoutInfo = new QHBoxLayout;
    m_spinNumber = new QSpinBox;
    m_coeffDispl = new CoefficientsDisplaying();
    m_checkBox = new QCheckBox(tr("Use"));
    m_comboMode = new QComboBox();
    m_comboMode->addItem(tr("Maximum"));
    m_comboMode->addItem(tr("Minimum"));
    m_comboMode->addItem(tr("Noise"));
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

    m_currentUseVector = m_useVectors[MAXIMUM_SPECTRUM];

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

void SpectrsSet::calculateAccumulationMaximum(ICurve *spctrSrc,ICurve *spctrDst,QVector<Qt::CheckState> *useVector){
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
        if(useVector->at(y) == Qt::Unchecked)
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


void SpectrsSet::calculateAccumulationAverage(ICurve *spctrSrc,ICurve *spctrDst,QVector<Qt::CheckState> *useVector){
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
        if(useVector->at(currentY) == Qt::Checked){
            f_averageValues.fill(0,f_averageValues.size());
            qreal f_quantitySpectrums = currentY + 1;
            for(int y = 0; y < currentY; ++y){
                if(useVector->at(y) == Qt::Unchecked)
                    --f_quantitySpectrums;
            }
            qreal f_coef = 1.f / f_quantitySpectrums;
            for(int y = 0; y <= currentY; ++y){
                if(useVector->at(y) == Qt::Checked)
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
   for(auto&& [coef_a,coef_b] : *m_upCoeffs){
       f_coeffsA.push_back(QPointF(f_y,coef_a));
       f_coeffsB.push_back(QPointF(f_y++,coef_b));
   }
   m_coeffDispl->addCoeffs(f_coeffsA,f_coeffsB);

}

void SpectrsSet::loadReference(){
    auto f_loaderDB = std::make_unique<SaverLoaderCalibDB>();
    QVector<ICurve*> f_referenceSpectrums{TYPE_SPECTRUM_MAX,nullptr};
    f_loaderDB->loadReference(m_originalSpectr->sizeOffset(),m_originalSpectr->desc()->param("data_step"),f_referenceSpectrums,m_idReference);
    for(int type = MINIMUM_SPECTRUM;type < TYPE_SPECTRUM_MAX; ++type){
        if(!f_referenceSpectrums[type])
            return;
    }

    for(int type = MINIMUM_SPECTRUM;type < TYPE_SPECTRUM_MAX; ++type){
        if(m_referenceSpectrums[type])
            m_oneWave->removeLastCurve();
        m_referenceSpectrums[type] = f_referenceSpectrums[type];
        m_referenceSpectrums[type]->setMnemonic(m_referMnemonics.at(type));
        m_oneWave->addCurve(m_referenceSpectrums[type]);
    }
    m_btnCalcCoeffs->show();
}

void SpectrsSet::saveResult(){
    if(!m_sourceSpectrums[MAXIMUM_SPECTRUM] || !m_sourceSpectrums[MINIMUM_SPECTRUM])
        return;
    auto f_saverDB = std::make_unique<SaverLoaderCalibDB>();
    f_saverDB->saveReference(m_sourceSpectrums,ReferenceStatus::STATUS_REFERENCE);
}

qreal dbToV(qreal data){
    qreal f_coeff = 20 * log10(32768.0);
    return sqrt(pow(10,(f_coeff + data) / 10));
}

void SpectrsSet::calcCoeffs(){
    for(int type = MINIMUM_SPECTRUM;type < TYPE_SPECTRUM_MAX; ++type){
        if(!m_referenceSpectrums[type] || !m_sourceSpectrums[type]){
            QMessageBox::warning(this,tr("Calc coeffs"),tr("Download the reference spectrum \n click the 'Load reference' button"));
            return;
        }
        if(m_referenceSpectrums[type]->sizeOffset() != m_sourceSpectrums[type]->sizeOffset()){
            QMessageBox::warning(this,tr("Calc coeffs"),tr("The number of bands of the reference \n spectrum does not match the current one"));
            return;
        }
    }

    if(!m_upCoeffs)
        m_upCoeffs = new QVector<CoeffsLinearDependence>(m_sourceSpectrums[MINIMUM_SPECTRUM]->sizeOffset());
    if(!m_downCoeffs)
        m_downCoeffs = new QVector<CoeffsLinearDependence>(m_sourceSpectrums[MINIMUM_SPECTRUM]->sizeOffset());


    int f_sizeOffset = m_sourceSpectrums[MAXIMUM_SPECTRUM]->sizeOffset();
    int f_indexBeginResultSpectrumMAX =  m_sourceSpectrums[MAXIMUM_SPECTRUM]->size() - f_sizeOffset;
    int f_indexBeginResultSpectrumAVER =  m_sourceSpectrums[MINIMUM_SPECTRUM]->size() - f_sizeOffset;
    int f_indexBeginRefSpectrumMAX = m_referenceSpectrums[MAXIMUM_SPECTRUM]->size() - f_sizeOffset;
    int f_indexBeginRefSpectrumAVER = m_referenceSpectrums[MINIMUM_SPECTRUM]->size() - f_sizeOffset;
    for(int i = 0; i < f_sizeOffset; ++i){
        /*qreal f_resMax = dbToV(m_resultSpectrMAX->data(f_indexBeginResultSpectrumMAX + i));
        qreal f_resAVER = dbToV(m_resultSpectrAVER->data(f_indexBeginResultSpectrumAVER + i));
        qreal f_referMax = dbToV(m_referenceSpectrMAX->data(f_indexBeginRefSpectrumMAX + i));
        qreal f_referAVER = dbToV(m_referenceSpectrAVER->data(f_indexBeginRefSpectrumAVER + i));
        calcCoeffLinePolinom(f_resMax,f_resAVER,f_referMax,f_referAVER,m_coeffs->operator[](i));*/
        calcCoeffLinePolinom(m_sourceSpectrums[MAXIMUM_SPECTRUM]->data(f_indexBeginResultSpectrumMAX + i),
                             m_sourceSpectrums[MINIMUM_SPECTRUM]->data(f_indexBeginResultSpectrumAVER + i),
                             m_referenceSpectrums[MAXIMUM_SPECTRUM]->data(f_indexBeginRefSpectrumMAX + i),
                             m_referenceSpectrums[MINIMUM_SPECTRUM]->data(f_indexBeginRefSpectrumAVER + i),
                             m_upCoeffs->operator[](i));
        calcCoeffLinePolinom(m_sourceSpectrums[MINIMUM_SPECTRUM]->data(f_indexBeginResultSpectrumMAX + i),
                             m_sourceSpectrums[NOISE_SPECTRUM]->data(f_indexBeginResultSpectrumAVER + i),
                             m_referenceSpectrums[MINIMUM_SPECTRUM]->data(f_indexBeginRefSpectrumMAX + i),
                             m_referenceSpectrums[NOISE_SPECTRUM]->data(f_indexBeginRefSpectrumAVER + i),
                             m_downCoeffs->operator[](i));
    }
    applyCoeffsDuplicateSpectrum();
    showCoeffs();
    m_btnOpenProtocol->show();
    m_btnApplyOrigin->show();
}

void SpectrsSet::changeCalcFun(QString text){
    if(text == tr("Maximum"))
        m_currentUseVector = m_useVectors[MAXIMUM_SPECTRUM];
    else if (text == tr("Minimum"))
        m_currentUseVector = m_useVectors[MINIMUM_SPECTRUM];
    else if (text == tr("Noise"))
        m_currentUseVector = m_useVectors[NOISE_SPECTRUM];
}

void SpectrsSet::applyCoeffsDuplicateSpectrum(){
    if(!m_upCoeffs)
        return;

    int f_spectrums = m_duplicateSpectr->size() / m_duplicateSpectr->sizeOffset();
    int f_offset = m_duplicateSpectr->sizeOffset();
    int f_indexBeginSourceMinimum =  m_sourceSpectrums[MINIMUM_SPECTRUM]->size() - f_offset;
    int f_indexBeginSourceNoise =  m_sourceSpectrums[NOISE_SPECTRUM]->size() - f_offset;
    for(int currentY = 0; currentY < f_spectrums; ++currentY){
        for(int x = 0; x < f_offset; ++x){
            int f_curInd = currentY * f_offset + x;
            /*qreal f_dataV = dbToV(m_originalSpectr->data(f_curInd));
            qreal f_data = f_dataV * m_coeffs->at(x).k_a + m_coeffs->at(x).k_b;
            f_data = 10.0 * log10( pow(f_data,2) ) - 20.0 * log10( 32768.0 );*/
            qreal f_data = m_originalSpectr->data(f_curInd);
            if(m_originalSpectr->data(f_curInd) >= m_sourceSpectrums[MINIMUM_SPECTRUM]->data(f_indexBeginSourceMinimum + x)){
                f_data = f_data * m_upCoeffs->at(x).k_a + m_upCoeffs->at(x).k_b;
            }
            else if(m_originalSpectr->data(f_curInd) < m_sourceSpectrums[MINIMUM_SPECTRUM]->data(f_indexBeginSourceMinimum + x)
                    && m_originalSpectr->data(f_curInd) >= m_sourceSpectrums[NOISE_SPECTRUM]->data(f_indexBeginSourceNoise + x)){
                f_data = f_data * m_downCoeffs->at(x).k_a + m_downCoeffs->at(x).k_b;
            }
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
    if(!m_originalSpectr || !m_upCoeffs || m_upCoeffs->isEmpty()){
        return;
    }
    if(!m_referenceSpectrums[MAXIMUM_SPECTRUM] || !m_referenceSpectrums[MINIMUM_SPECTRUM]){
        return;
    }

    bool bOk;
    QString f_operatorName = QInputDialog::getText( 0, tr("Operator name:(last name first name patronymic)"),"",QLineEdit::Normal,"",&bOk);
    Operator f_operator(f_operatorName);
    ProtocolNoise *f_noiseProtocol = new ProtocolNoise();
    f_noiseProtocol->addReference(m_referenceSpectrums,m_idReference);
    f_noiseProtocol->addSource(m_sourceSpectrums);
    f_noiseProtocol->addApproximated(m_approximatedSpectrums);
    f_noiseProtocol->addCoeffs(m_upCoeffs,m_downCoeffs);
    f_noiseProtocol->addChannelName(m_originalSpectr->mnemonic());
    f_noiseProtocol->addOperator(f_operator);
    f_noiseProtocol->createPDF();
}

void SpectrsSet::loadCoeffs(){

}

void SpectrsSet::calcResult(){
    if(!m_originalSpectr || !m_duplicateSpectr){
        return;
    }

    for(int type = MINIMUM_SPECTRUM;type < TYPE_SPECTRUM_MAX; ++type){
        calculateAccumulationAverage(m_originalSpectr,m_sourceSpectrums[type],m_useVectors[type]);
        calculateAccumulationAverage(m_duplicateSpectr,m_approximatedSpectrums[type],m_useVectors[type]);
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
