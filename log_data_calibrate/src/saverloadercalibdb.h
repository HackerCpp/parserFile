#ifndef SAVERLOADERCALIBDB_H
#define SAVERLOADERCALIBDB_H

#include "geologysqlitedb.h"
#include "coeffs.h"
#include "operator.h"
#include "protocolnoise.h"
#include "referencesaver.h"
#include "protocolnoise.h"

class SaverLoaderCalibDB : public GeologySQLiteDB
{
public:
    SaverLoaderCalibDB();
    int saveDevice(QString devName,QString devNum,QString desc = "");
    int saveOperator(Operator operatorer);
    int saveCoeffs(const QVector<CoeffsLinearDependence> &coeffs,const ICurve &origin);
    int saveReference(const QVector<ICurve*> &referenceSpectrums,ReferenceStatus status = STATUS_ORDINARY);
    int saveNoiseProtocol(std::shared_ptr<ProtocolInfo> protInfo);

    void loadReference(int lines,QString data_step,QVector<ICurve*> &referenceSpectrums,int &idReference);
    void loadReference(int index,QVector<ICurve*> &referenceSpectrums);
    void loadCoeffs(int index,QVector<CoeffsLinearDependence> *&coeffs);
    void loadOperator(int index,Operator &oper);
    void loadNoiseProtocol(int index);

    int findDevice(QString devName,QString devNum);
    int findOperator(Operator operatorer);
    int findCoeffs(int deviceID, int numLines,QString dataStep,QString dateSave);
    int findNoiseProtocol(std::shared_ptr<ProtocolInfo> protInfo);
};

#endif // SAVERLOADERCALIBDB_H
