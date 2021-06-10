#ifndef PROTOCOLNOISE_H
#define PROTOCOLNOISE_H

#include "QString"
#include "coeffs.h"
#include "operator.h"
#include "picturechart.h"
#include <QWidget>


class ICurve;
class QWidget;
class QVBoxLayout;
class QPushButton;
class QWebEngineView;

class ProtocolNoise : public QWidget
{
    Q_OBJECT
    std::unique_ptr<PictureChart> m_pictureCreater;
    QWebEngineView *m_webView;
    QVBoxLayout *m_mainLayout;
    QPushButton *m_btnSaveFile;

    QString m_deviceName,m_deviceNum,m_channelName;
    Operator m_operator;
    QVector<CoeffsLinearDependence> *m_coeffs;
    ICurve *m_referenceMaximum;
    ICurve *m_referenceAverage;
    ICurve *m_currentMaximum;
    ICurve *m_currentAverage;
    ICurve *m_recalculateMaximum;
    ICurve *m_recalculateAverage;
public:
    ProtocolNoise(QWidget* parent = nullptr);
    void addReference(ICurve *refMax,ICurve *refAver);
    void addCurrent(ICurve *curMax,ICurve *curAver);
    void addRecalc(ICurve *recalcMax,ICurve *racalcAver);
    void addCoeffs(QVector<CoeffsLinearDependence> *coeffs);
    void addOperator(Operator operatorer);
    void addChannelName(QString channelName){m_channelName = channelName;}

    QString deviceName()const{return m_deviceName;}
    QString deviceNum()const{return m_deviceNum;}
    QString channelName()const{return m_channelName;}
    Operator operatorer()const{return m_operator;}

    void createPDF();

public slots:
    void loadFinished(bool loaded);
    void saveProtocol();
};

#endif // PROTOCOLNOISE_H
