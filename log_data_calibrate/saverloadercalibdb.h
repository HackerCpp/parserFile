#ifndef SAVERLOADERCALIBDB_H
#define SAVERLOADERCALIBDB_H

#include "geologysqlitedb.h"
#include "coeffs.h"
#include "operator.h"
#include "protocolnoise.h"


class SaverLoaderCalibDB : public GeologySQLiteDB
{
public:
    SaverLoaderCalibDB();
    int saveDevice(QString devName,QString devNum,QString desc = "");
    int saveOperator(Operator operatorer);
    int saveCoeffs(const QVector<CoeffsLinearDependence> &coeffs,const ICurve &origin);
    int saveReference(const ICurve &curveMaximum,const ICurve &curveAverage);
    int saveNoiseProtocol(std::shared_ptr<ProtocolNoise> protocol);

    void loadReference(int lines,QString data_step,ICurve *&refCurveMAX,ICurve *&refCurveAver);

    int findDevice(QString devName,QString devNum);
    int findOperator(Operator operatorer);
    int findCoeffs(int deviceID, int numLines,QString dataStep,QString dateSave);
};

#endif // SAVERLOADERCALIBDB_H
