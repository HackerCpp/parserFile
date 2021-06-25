#ifndef PROTOCOLINFO_H
#define PROTOCOLINFO_H

#include "coeffs.h"
#include <QVector>
#include "operator.h"
#include <QDateTime>

class ICurve;
class QWidget;
class QVBoxLayout;
class QPushButton;
class QWebEngineView;

enum TypeSpectrum{MINIMUM_SPECTRUM,MAXIMUM_SPECTRUM,NOISE_SPECTRUM,TYPE_SPECTRUM_MAX};

class ProtocolInfo
{
    QString m_deviceName,m_deviceNum,m_channelName;
    Operator m_operator;
    QVector<CoeffsLinearDependence> *m_coeffsUp;
    QVector<CoeffsLinearDependence> *m_coeffsDown;

    QVector<ICurve*> m_sourceSpectrums{TYPE_SPECTRUM_MAX,nullptr};
    QVector<ICurve*> m_approximatedSpectrums{TYPE_SPECTRUM_MAX,nullptr};
    QVector<ICurve*> m_referenceSpectrums{TYPE_SPECTRUM_MAX,nullptr};
    QString m_dateTime;
    int m_indexRefDB;
public:
    ProtocolInfo(QString currentDayTime = QDateTime().currentDateTime().toString());

    void addReference(const QVector<ICurve*> &referenceSpectrums,int indexRefDB = 0);
    void addSource(const QVector<ICurve*> &sourceSpectrums);
    void addApproximated(const QVector<ICurve*> &approximatedSpectrums);

    void addCoeffs(QVector<CoeffsLinearDependence> *coeffsUp,QVector<CoeffsLinearDependence> *coeffsDown);
    void addOperator(Operator operatorer);
    void addChannelName(QString channelName){m_channelName = channelName;}

    QString deviceName()const{return m_deviceName;}
    QString deviceNum()const{return m_deviceNum;}
    QString channelName()const{return m_channelName;}
    Operator operatorer()const{return m_operator;}

    ICurve *reference(TypeSpectrum type)const{return m_referenceSpectrums[type];}
    ICurve *approximated(TypeSpectrum type)const{return m_approximatedSpectrums[type];}
    ICurve *source(TypeSpectrum type)const{return m_sourceSpectrums[type];}

    const QVector<ICurve*> &references()const{return m_referenceSpectrums;}
    const QVector<ICurve*> &approximateds()const{return m_approximatedSpectrums;}
    const QVector<ICurve*> &sources()const{return m_sourceSpectrums;}

    QVector<CoeffsLinearDependence> *coeffsUp()const{return m_coeffsUp;}
    QVector<CoeffsLinearDependence> *coeffsDown()const{return m_coeffsDown;}
    QString dateTime(){return m_dateTime;}
    int indexRefDB()const{return m_indexRefDB;}
};

#endif // PROTOCOLINFO_H
