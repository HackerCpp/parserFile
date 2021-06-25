#ifndef SPECTRSSET_H
#define SPECTRSSET_H

#include <QWidget>
#include <QSplitter>
#include <QHBoxLayout>
#include <QSlider>
#include <QSpinBox>
#include "coefficientsdisplaying.h"
#include <QMenu>
#include "coeffs.h"
#include "protocolnoise.h"


class ICurve;
class OneWaveWidget;
class QCheckBox;
class QPushButton;
class QComboBox;



class SpectrsSet : public QWidget
{
    Q_OBJECT

    QVector<CoeffsLinearDependence> *m_upCoeffs;
    QVector<CoeffsLinearDependence> *m_downCoeffs;
    QSplitter *m_mainSplitter;
    QHBoxLayout *m_mainHLayout;
    QSlider *m_slider;
    OneWaveWidget *m_oneWave;
    QWidget *m_widgetInfo;
    QHBoxLayout *m_layoutInfo;
    QSpinBox *m_spinNumber;
    QCheckBox *m_checkBox;
    QComboBox *m_comboMode;
    QPushButton *m_btnLoadReference,*m_btnSaveResult,
    *m_btnCalcCoeffs, *m_btnApplyOrigin,/*m_btnSaveCalib,*/*m_btnOpenProtocol,
    *m_btnLoadCoeffs,*m_btnCalcResult;
    QVector<QVector<Qt::CheckState> *> m_useVectors{TYPE_SPECTRUM_MAX};
    QVector<Qt::CheckState> *m_currentUseVector;
    QVector<ICurve*> m_sourceSpectrums{TYPE_SPECTRUM_MAX,nullptr};
    QVector<ICurve*> m_approximatedSpectrums{TYPE_SPECTRUM_MAX,nullptr};
    QVector<ICurve*> m_referenceSpectrums{TYPE_SPECTRUM_MAX,nullptr};
    QStringList m_referMnemonics,m_approximatedMnemonics,m_sourceMnemonics;
    ICurve *m_originalSpectr,*m_duplicateSpectr;
    int m_idReference, m_idOriginal;
    CoefficientsDisplaying * m_coeffDispl;
    QMenu m_menu;

    void calculateAccumulationMaximum(ICurve *spctrSrc,ICurve *spctrDst,QVector<Qt::CheckState> *useVector);
    void calculateAccumulationAverage(ICurve *spctrSrc,ICurve *spctrDst,QVector<Qt::CheckState> *useVector);
    void calcCoeffLinePolinom(qreal x1,qreal x2,qreal y1,qreal y2,CoeffsLinearDependence &k);
public:
    explicit SpectrsSet(ICurve *curve,QWidget *parent = nullptr);

    void mousePressEvent(QMouseEvent *event) override;
    void mouseDoubleClickEvent(QMouseEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;
    void showCoeffs();
public slots:
    void changePosition(int value);
    void useSpectrumsChange(bool toggled);
    void loadReference();
    void saveResult();
    void calcCoeffs();
    void changeCalcFun(QString text);
    void applyCoeffsDuplicateSpectrum();
    void applyOrigin();
    //void saveCalib();
    void openProtocol();
    void loadCoeffs();
    void calcResult();

    void useAllVectors();
    void removeAllVectors();
    void useAllUp();
    void removeAllUp();
    void useAllDown();
    void removeAllDown();


};

#endif // SPECTRSSET_H
