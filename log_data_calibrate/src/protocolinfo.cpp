#include "protocolinfo.h"
#include "icurve.h"

ProtocolInfo::ProtocolInfo(QString currentDayTime):
    m_coeffsUp(nullptr),m_coeffsDown(nullptr),m_dateTime(currentDayTime),m_indexRefDB(0)
{

}

void ProtocolInfo::addReference(const QVector<ICurve*> &referenceSpectrums,int indexRefDB){
    for(int type = MINIMUM_SPECTRUM;type < TYPE_SPECTRUM_MAX; ++type){
        m_referenceSpectrums[type] = referenceSpectrums[type];
    }
    m_indexRefDB = indexRefDB;
}

void ProtocolInfo::addSource(const QVector<ICurve*> &sourceSpectrums){
    for(int type = MINIMUM_SPECTRUM;type < TYPE_SPECTRUM_MAX; ++type){
        m_sourceSpectrums[type] = sourceSpectrums[type];
    }
    m_deviceName = m_sourceSpectrums[MINIMUM_SPECTRUM]->shortCut().deviceName();
    m_deviceNum = m_sourceSpectrums[MINIMUM_SPECTRUM]->shortCut().deviceNum();
}

void ProtocolInfo::addApproximated(const QVector<ICurve*> &approximatedSpectrums){
    for(int type = MINIMUM_SPECTRUM;type < TYPE_SPECTRUM_MAX; ++type){
        m_approximatedSpectrums[type] = approximatedSpectrums[type];
    }
}

void ProtocolInfo::addCoeffs(QVector<CoeffsLinearDependence> *coeffsUp,QVector<CoeffsLinearDependence> *coeffsDown){
    m_coeffsUp = coeffsUp;
    m_coeffsDown = coeffsDown;
}

void ProtocolInfo::addOperator(Operator operatorer){
    m_operator = operatorer;
}
