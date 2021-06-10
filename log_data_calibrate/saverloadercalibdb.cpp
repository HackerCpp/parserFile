#include "saverloadercalibdb.h"
#include <QSqlQuery>
#include <QDebug>
#include <QSqlError>
#include "referencesaver.h"
#include <memory>
#include "icurve.h"
#include "referenceLoader.h"
#include <QInputDialog>
#include <QLineEdit>


SaverLoaderCalibDB::SaverLoaderCalibDB() : GeologySQLiteDB()
{
    if(m_db->isOpen()){
        QSqlQuery f_query;
        f_query.prepare("CREATE TABLE IF NOT EXISTS CalibDevice (\
                        CDeviceID     INTEGER PRIMARY KEY AUTOINCREMENT,\
                        CDName        TEXT,\
                        CDNumber      TEXT,\
                        CDDescription TEXT\
                    );"
            );
        f_query.exec();
        qDebug() << f_query.lastError().text();
        f_query.prepare("CREATE TABLE IF NOT EXISTS CalibOperator (\
                        COperatorID  INTEGER PRIMARY KEY AUTOINCREMENT,\
                        COLastName   STRING,\
                        COFirstName  STRING,\
                        COPatronymic STRING,\
                        Comment      TEXT\
                    );"
            );
        f_query.exec();
        qDebug() << f_query.lastError().text();
        f_query.prepare("CREATE TABLE IF NOT EXISTS SpectrumCalibCoeffs (\
                        SCCoeffsID  INTEGER  PRIMARY KEY AUTOINCREMENT,\
                        SCCDeviceID INTEGER  REFERENCES CalibDevice (CDeviceID),\
                        SCCNumLines INTEGER,\
                        SCCDataStep TEXT,\
                        SCCDateSave DATETIME,\
                        SCCComment  TEXT,\
                        SCCData     BLOB\
                    );"
            );
        f_query.exec();
        qDebug() << f_query.lastError().text();
        f_query.prepare("CREATE TABLE IF NOT EXISTS SpectrumCalibReference (\
                        SCReferenceID  INTEGER  PRIMARY KEY AUTOINCREMENT UNIQUE,\
                        SCRDeviceID     INTEGER  REFERENCES CalibDevice (CDeviceID),\
                        SCRLastChanges DATETIME,\
                        SCRCurveMaxID  INTEGER  REFERENCES LogDataCurve (LDCurveID),\
                        SCRCurveAverID INTEGER  REFERENCES LogDataCurve (LDCurveID),\
                        SCRLines       INTEGER,\
                        SCRDataStep    TEXT,\
                        SCRComment     TEXT\
                    );"
            );
        f_query.exec();
        qDebug() << f_query.lastError().text();
        f_query.prepare("CREATE TABLE IF NOT EXISTS Calibrations (\
                        CalibID         INTEGER  PRIMARY KEY AUTOINCREMENT,\
                        CDateTime       DATETIME,\
                        COperatorID     INTEGER  REFERENCES CalibOperator (COperatorID),\
                        CDeviceID       INTEGER  REFERENCES CalibDevice (CDeviceID),\
                        CChannel        STRING,\
                        CMetodicID      INTEGER,\
                        CSourceRefID    INTEGER  REFERENCES SpectrumCalibReference (SCReferenceID),\
                        CReferenceRefID INTEGER  REFERENCES SpectrumCalibReference (SCReferenceID),\
                        CCoeffsID       INTEGER,\
                        CComment        TEXT\
                    );"
            );
        f_query.exec();
        qDebug() << f_query.lastError().text();
    }

}

int SaverLoaderCalibDB::saveDevice(QString devName,QString devNum,QString desc ){
    if(!m_db->isOpen())
        return 0;
    if(int f_indexDev = findDevice(devName,devNum);f_indexDev )
        return f_indexDev;
    QSqlQuery f_query;
    f_query.prepare("INSERT INTO CalibDevice (CDName,CDNumber,CDDescription)\
                VALUES (?,?,?);");
    f_query.addBindValue(devName);
    f_query.addBindValue(devNum);
    f_query.addBindValue(desc);
    f_query.exec();
    qDebug() << f_query.lastError().text();
    return findDevice(devName,devNum);
}

int SaverLoaderCalibDB::saveOperator(Operator operatorer){
    if(!m_db->isOpen())
        return 0;
    if(int f_indexOperator = findOperator(operatorer);f_indexOperator)
        return f_indexOperator;
    QSqlQuery f_query;
    f_query.prepare("INSERT INTO CalibOperator (COLastName,COFirstName,COPatronymic,Comment)\
                VALUES (?,?,?,?);"
        );
    f_query.addBindValue(operatorer.lastName());
    f_query.addBindValue(operatorer.firstName());
    f_query.addBindValue(operatorer.patronymic());
    f_query.addBindValue(operatorer.comment());
    f_query.exec();
    qDebug() << f_query.lastError().text();
    return findOperator(operatorer);
}

int SaverLoaderCalibDB::saveCoeffs(const QVector<CoeffsLinearDependence> &coeffs,const ICurve &origin){
    if(!m_db->isOpen())
        return 0;
    int f_indexDevice = saveDevice(origin.shortCut().deviceName(),origin.shortCut().deviceNum());
    QSqlQuery f_query;
    f_query.prepare("INSERT INTO SpectrumCalibCoeffs (\
                    SCCDeviceID, SCCNumLines, SCCDataStep,\
                    SCCDateSave, SCCComment, SCCData)\
                VALUES (?,?,?,?,?,?);"
        );
    QString f_currentDateTime = QDateTime::currentDateTime().toString();
    f_query.addBindValue(f_indexDevice);
    f_query.addBindValue(origin.sizeOffset());
    f_query.addBindValue(origin.desc()->param("data_step"));
    f_query.addBindValue(f_currentDateTime);
    bool bOk;
    QString f_comment = QInputDialog::getText( 0, tr("Comment coefficients"),"",QLineEdit::Normal,"",&bOk);
    f_query.addBindValue(f_comment);
    f_query.addBindValue(QByteArray((const char*)coeffs.data(),coeffs.size() * sizeof(CoeffsLinearDependence)));
    f_query.exec();
    qDebug() << f_query.lastError().text();
    return findCoeffs(f_indexDevice, origin.sizeOffset(),origin.desc()->param("data_step"),f_currentDateTime);
}

int SaverLoaderCalibDB::saveReference(const ICurve &curveMaximum,const ICurve &curveAverage){
    auto f_saverRef = std::make_unique<ReferenceSaver>(m_db);
    int indexDevice = saveDevice(curveMaximum.shortCut().deviceName(),curveMaximum.shortCut().deviceNum(),"");
    return f_saverRef->saveReference(curveMaximum,curveAverage,indexDevice);
}

int SaverLoaderCalibDB::saveNoiseProtocol(std::shared_ptr<ProtocolNoise> protocol){
    if(!m_db->isOpen())
        return 0;
    QString f_currentDateTime = QDateTime::currentDateTime().toString();
    QSqlQuery f_query;
    f_query.prepare("INSERT INTO Calibrations (\
                    CDateTime,COperatorID,CDeviceID,CChannel,CMetodicID,\
                    CSourceRefID,CReferenceRefID,CCoeffsID,CComment)\
                VALUES (?,?,?,?,?,?,?,?,?);"
        );
    f_query.addBindValue(f_currentDateTime);//dateTime
    int f_indexOperator  = saveOperator(protocol->operatorer());
    f_query.addBindValue(f_indexOperator);
    int f_indexDevice = saveDevice(protocol->deviceName(),protocol->deviceNum());
    f_query.addBindValue(f_indexDevice);
    f_query.addBindValue(protocol->channelName());
    //f_query.addBindValue();
    //f_query.addBindValue();
    f_query.exec();
    qDebug() << f_query.lastError().text();
}

void SaverLoaderCalibDB::loadReference(int lines,QString data_step,ICurve *&refCurveMAX,ICurve *&refCurveAver){
    ReferenceLoader(lines,data_step,m_db).loadRefCurves(refCurveMAX,refCurveAver);
}

int SaverLoaderCalibDB::findDevice(QString devName,QString devNum){
    if(!m_db->isOpen())
        return 0;
    QSqlQuery f_query;
    f_query.prepare("SELECT CDeviceID\
               FROM CalibDevice \
               WHERE CalibDevice.CDName = ? AND CalibDevice.CDNumber = ?;");
    f_query.addBindValue(devName);
    f_query.addBindValue(devNum);
    f_query.exec();
    qDebug() << f_query.lastError().text();
    if(f_query.next())
       return f_query.value(0).toInt();
   return 0;
}

int SaverLoaderCalibDB::findOperator(Operator operatorer){
    if(!m_db->isOpen())
        return 0;
    QSqlQuery f_query;
    f_query.prepare("SELECT COperatorID\
               FROM CalibOperator \
               WHERE CalibOperator.COLastName = ? AND CalibOperator.COFirstName = ? AND CalibOperator.COPatronymic = ?;");
    f_query.addBindValue(operatorer.lastName());
    f_query.addBindValue(operatorer.firstName());
    f_query.addBindValue(operatorer.patronymic());
    f_query.exec();
    qDebug() << f_query.lastError().text();
    if(f_query.next())
       return f_query.value(0).toInt();
   return 0;
}

int SaverLoaderCalibDB::findCoeffs(int deviceID, int numLines,QString dataStep,QString dateSave){
    if(!m_db->isOpen())
        return 0;
    QSqlQuery f_query;
    f_query.prepare("SELECT SCCoeffsID\
               FROM SpectrumCalibCoeffs; \
               WHERE SCCDeviceID = ? AND SCCNumLines = ? AND SCCDataStep = ? AND SCCDateSave = ?;");
    f_query.addBindValue(deviceID);
    f_query.addBindValue(numLines);
    f_query.addBindValue(dataStep);
    f_query.addBindValue(dateSave);
    f_query.exec();
    qDebug() << f_query.lastError().text();
    if(f_query.next())
       return f_query.value(0).toInt();
   return 0;
}

