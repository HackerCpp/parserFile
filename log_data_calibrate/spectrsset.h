#ifndef SPECTRSSET_H
#define SPECTRSSET_H

#include <QWidget>
#include <QSplitter>
#include <QHBoxLayout>
#include <QSlider>
#include <QSpinBox>
#include "coefficientsdisplaying.h"

class ICurve;
class OneWaveWidget;
class QCheckBox;
class QPushButton;
class QComboBox;

class SpectrsSet : public QWidget
{
    Q_OBJECT
#pragma pack(push, 1)
    struct CoeffsLinearDependence{
        float k_a;
        float k_b;
    };
#pragma pack(pop)
    QVector<CoeffsLinearDependence> *m_coeffs;
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
    *m_btnCalcCoeffs, *m_btnApplyOrigin;
    QVector<Qt::CheckState> *m_useVectorMaximum;
    QVector<Qt::CheckState> *m_useVectorAverage;
    QVector<Qt::CheckState> *m_currentUseVector;
    ICurve *m_resultSpectrMAX , *m_resultSpectrAVER;
    ICurve *m_currentResultSpectr;
    ICurve *m_originalSpectr,*m_duplicateSpectr;
    ICurve *m_referenceSpectrMAX,*m_referenceSpectrAVER;
    CoefficientsDisplaying * m_coeffDispl;
    void(SpectrsSet::*pCurrentCalcFunction)();

    void calculateAccumulationMaximum();
    void calculateAccumulationAverage();
    void calcCoeffLinePolinom(qreal x1,qreal x2,qreal y1,qreal y2,CoeffsLinearDependence &k);
public:
    explicit SpectrsSet(ICurve *curve,QWidget *parent = nullptr);

    void mousePressEvent(QMouseEvent *event) override;
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


};

#endif // SPECTRSSET_H
