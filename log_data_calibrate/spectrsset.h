#ifndef SPECTRSSET_H
#define SPECTRSSET_H

#include <QWidget>
#include <QSplitter>
#include <QHBoxLayout>
#include <QSlider>
#include <QSpinBox>

class ICurve;
class OneWaveWidget;
class QCheckBox;
class QPushButton;

class SpectrsSet : public QWidget
{
    Q_OBJECT
    QSplitter *m_mainSplitter;
    QHBoxLayout *m_mainHLayout;
    QSlider *m_slider;
    OneWaveWidget *m_oneWave;
    QWidget *m_widgetInfo;
    QHBoxLayout *m_layoutInfo;
    QSpinBox *m_spinNumber;
    QCheckBox *m_checkBox;
    QPushButton *m_btnLoadReference,*m_btnSaveResult;
    QVector<Qt::CheckState> *m_useVector;
    ICurve *m_resultSpectr;
    ICurve *m_originalSpectr;
    ICurve *m_referenceSpectr;

    void calculateAccumulationMaximum();

public:
    explicit SpectrsSet(ICurve *curve,QWidget *parent = nullptr);

    void mousePressEvent(QMouseEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;
public slots:
    void changePosition(int value);
    void useSpectrumsChange(bool toggled);
    void loadReference();
    void saveResult();

};

#endif // SPECTRSSET_H
