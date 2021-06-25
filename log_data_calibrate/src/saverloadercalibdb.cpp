#include "saverloadercalibdb.h"
#include <QSqlQuery>
#include <QDebug>
#include <QSqlError>
#include <memory>
#include "icurve.h"
#include "referenceLoader.h"
#include <QInputDialog>
#include <QLineEdit>
#include "sqlite3loader.h"
#include <QMessageBox>


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
                        SCRStatus      INTEGER,\
                        SCRCurveMaxID  INTEGER  REFERENCES LogDataCurve (LDCurveID),\
                        SCRCurveMinID  INTEGER  REFERENCES LogDataCurve (LDCurveID),\
                        SCRCurveNoiseID  INTEGER  REFERENCES LogDataCurve (LDCurveID),\
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
                        CCoeffsUpID     INTEGER  REFERENCES SpectrumCalibCoeffs (SCCoeffsID),\
                        CCoeffsDownID   INTEGER  REFERENCES SpectrumCalibCoeffs (SCCoeffsID),\
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
    //bool bOk;
    //QString f_comment = QInputDialog::getText( 0, tr("Comment coefficients"),"",QLineEdit::Normal,"",&bOk);
    f_query.addBindValue("");
    f_query.addBindValue(QByteArray((const char*)coeffs.data(),coeffs.size() * sizeof(CoeffsLinearDependence)));
    f_query.exec();
    qDebug() << f_query.lastError().text();
    return findCoeffs(f_indexDevice, origin.sizeOffset(),origin.desc()->param("data_step"),f_currentDateTime);
}

int SaverLoaderCalibDB::saveReference(const QVector<ICurve*> &referenceSpectrums,ReferenceStatus status){
    auto f_saverRef = std::make_unique<ReferenceSaver>(m_db);
    int indexDevice = saveDevice(referenceSpectrums[MAXIMUM_SPECTRUM]->shortCut().deviceName(),referenceSpectrums[MAXIMUM_SPECTRUM]->shortCut().deviceNum(),"");
    return f_saverRef->saveReference(referenceSpectrums,indexDevice,status);
}

int SaverLoaderCalibDB::saveNoiseProtocol(std::shared_ptr<ProtocolInfo> protInfo){
    if(!m_db->isOpen())
        return 0;
    int f_indexOperator  = saveOperator(protInfo->operatorer());
    int f_indexDevice = saveDevice(protInfo->deviceName(),protInfo->deviceNum());
    int f_indexMetodic = 0;
    int f_sourceID = saveReference(protInfo->sources());
    int f_referenceID = protInfo->indexRefDB();
    int f_coeffsUpID = saveCoeffs(*protInfo->coeffsUp(),*protInfo->source(MAXIMUM_SPECTRUM));
    int f_coeffsDownID = saveCoeffs(*protInfo->coeffsDown(),*protInfo->source(MAXIMUM_SPECTRUM));
    QString f_comment;
    QSqlQuery f_query;
    f_query.prepare("INSERT INTO Calibrations (\
                    CDateTime,COperatorID,CDeviceID,CChannel,CMetodicID,\
                    CSourceRefID,CReferenceRefID,CCoeffsUpID,CCoeffsDownID,CComment)\
                VALUES (?,?,?,?,?,?,?,?,?,?);"
        );
    f_query.addBindValue(protInfo->dateTime());//dateTime
    f_query.addBindValue(f_indexOperator);
    f_query.addBindValue(f_indexDevice);
    f_query.addBindValue(protInfo->channelName());
    f_query.addBindValue(f_indexMetodic);
    f_query.addBindValue(f_sourceID);
    f_query.addBindValue(f_referenceID);
    f_query.addBindValue(f_coeffsUpID);
    f_query.addBindValue(f_coeffsDownID);
    f_query.addBindValue(f_comment);
    f_query.exec();
    qDebug() << f_query.lastError().text() << "saveNoiseProtocol";
    return findNoiseProtocol(protInfo);
}

void SaverLoaderCalibDB::loadReference(int lines,QString data_step,QVector<ICurve*> &referenceSpectrums,int &idReference){
    ReferenceLoader(lines,data_step,m_db).loadRefCurves(referenceSpectrums,idReference);
}

void SaverLoaderCalibDB::loadReference(int index,QVector<ICurve*> &referenceSpectrums){
    if(!m_db->isOpen())
        return;
    QSqlQuery f_query;
    f_query.prepare(" \
SELECT SCRCurveMaxID,SCRCurveMinID,SCRCurveNoiseID \n\
FROM SpectrumCalibReference \n\
WHERE SCReferenceID=?;");
    f_query.addBindValue(index);
    f_query.exec();
    qDebug() << f_query.lastError().text() << "loadReference";
    int f_indexCurveMAX,f_indexCurveMIN,f_indexCurveNoise;
    if(f_query.next()){
       f_indexCurveMAX = f_query.value(0).toInt();
       f_indexCurveMIN = f_query.value(1).toInt();
       f_indexCurveNoise = f_query.value(2).toInt();
    }
    auto f_loaderDB = std::make_unique<SQLite3Loader>(m_db);
    referenceSpectrums[MAXIMUM_SPECTRUM] = f_loaderDB->loadCurve(f_indexCurveMAX);
    referenceSpectrums[MINIMUM_SPECTRUM] = f_loaderDB->loadCurve(f_indexCurveMIN);
    referenceSpectrums[NOISE_SPECTRUM] = f_loaderDB->loadCurve(f_indexCurveNoise);
   return;
}

void SaverLoaderCalibDB::loadCoeffs(int index,QVector<CoeffsLinearDependence> *&coeffs){
    if(!m_db->isOpen())
        return;
    QSqlQuery f_query;
    f_query.prepare("\
SELECT CalibDevice.CDName,CalibDevice.CDNumber,\
        SpectrumCalibCoeffs.SCCNumLines,SpectrumCalibCoeffs.SCCDataStep,\
        SpectrumCalibCoeffs.SCCDateSave,length(SpectrumCalibCoeffs.SCCData),\
        SpectrumCalibCoeffs.SCCData \n\
FROM SpectrumCalibCoeffs \n\
JOIN CalibDevice ON CalibDevice.CDeviceID=SpectrumCalibCoeffs.SCCDeviceID \n\
WHERE SpectrumCalibCoeffs.SCCoeffsID=?;");
    f_query.addBindValue(index);
    f_query.exec();
    qDebug() << f_query.lastError().text() << "loadCoeffs";
    int f_numBytesData;
    QString f_dateTime;
    QByteArray f_data;
    if(f_query.next()){
       f_numBytesData = f_query.value(5).toInt();
       f_data = f_query.value(6).toByteArray();
    }
    coeffs = new QVector<CoeffsLinearDependence>(f_numBytesData / sizeof(CoeffsLinearDependence));
    memcpy(coeffs->data(),f_data.data(),f_numBytesData);
}

void SaverLoaderCalibDB::loadOperator(int index,Operator &oper){
    if(!m_db->isOpen())
        return;
    QSqlQuery f_query;
    f_query.prepare(" \
SELECT COLastName,COFirstName,COPatronymic \
FROM CalibOperator \
WHERE COperatorID=?;");
    f_query.addBindValue(index);
    f_query.exec();
    qDebug() << f_query.lastError().text() << "loadOperator";
    if(f_query.next()){
       oper.setLastName(f_query.value("COLastName").toString());
       oper.setFirstName(f_query.value("COFirstName").toString());
       oper.setLastPatronymic(f_query.value("COPatronymic").toString());
    }
}

void SaverLoaderCalibDB::loadNoiseProtocol(int index){
    if(!m_db->isOpen())
        return;
    QSqlQuery f_query;
    f_query.prepare("\
SELECT CDateTime,COperatorID,CDeviceID,CChannel,\
       CMetodicID,CSourceRefID,CReferenceRefID, CCoeffsUpID,CCoeffsDownID \n \
FROM Calibrations \n\
WHERE CalibID = ?;");
    f_query.addBindValue(index);
    f_query.exec();
    qDebug() << f_query.lastError().text() << "loadNoiseProtocol";

    int f_currentRefID,f_referenceRefID,f_coeffsUpID,f_coeffsDownID;
    int f_operatorID,f_deviceID;
    QString f_dateTime;
    if(f_query.next()){
       f_dateTime = f_query.value("CDateTime").toString();
       f_operatorID = f_query.value("COperatorID").toInt();
       f_deviceID = f_query.value("CDeviceID").toInt();
       f_currentRefID = f_query.value("CSourceRefID").toInt();
       f_referenceRefID = f_query.value("CReferenceRefID").toInt();
       f_coeffsUpID = f_query.value("CCoeffsUpID").toInt();
       f_coeffsDownID = f_query.value("CCoeffsDownID").toInt();
    }

    QVector<ICurve*> f_sourceSpectrums{TYPE_SPECTRUM_MAX,nullptr};
    QVector<ICurve*> f_referenceSpectrums{TYPE_SPECTRUM_MAX,nullptr};
    QVector<ICurve*> f_approcsimatedSpectrums{TYPE_SPECTRUM_MAX,nullptr};

    loadReference(f_currentRefID,f_sourceSpectrums);
    loadReference(f_referenceRefID,f_referenceSpectrums);

    f_referenceSpectrums[MAXIMUM_SPECTRUM]->setMnemonic("Reference_MAX(DB)");
    f_referenceSpectrums[MINIMUM_SPECTRUM]->setMnemonic("Reference_MIN(DB)");
    f_referenceSpectrums[NOISE_SPECTRUM]->setMnemonic("Reference_NOISE(DB)");

    ProtocolNoise *f_noiseProtocol = new ProtocolNoise(f_dateTime);
    f_noiseProtocol->addReference(f_referenceSpectrums,f_referenceRefID);
    f_noiseProtocol->addSource(f_sourceSpectrums);
    QVector<CoeffsLinearDependence> *f_coeffsUp;
    QVector<CoeffsLinearDependence> *f_coeffsDown;
    loadCoeffs(f_coeffsUpID,f_coeffsUp);
    loadCoeffs(f_coeffsDownID,f_coeffsDown);

    f_approcsimatedSpectrums[MAXIMUM_SPECTRUM] = ICurve::curveCreater(*f_sourceSpectrums[MAXIMUM_SPECTRUM]);
    f_approcsimatedSpectrums[MINIMUM_SPECTRUM] = ICurve::curveCreater(*f_sourceSpectrums[MINIMUM_SPECTRUM]);
    f_approcsimatedSpectrums[NOISE_SPECTRUM] = ICurve::curveCreater(*f_sourceSpectrums[NOISE_SPECTRUM]);
    f_approcsimatedSpectrums[MAXIMUM_SPECTRUM]->setMnemonic("Approximated_MAX(DB)");
    f_approcsimatedSpectrums[MINIMUM_SPECTRUM]->setMnemonic("Approximated_MIN(DB)");
    f_approcsimatedSpectrums[NOISE_SPECTRUM]->setMnemonic("Approximated_NOISE(DB)");
    int f_index = 0;
    for(auto koeff : *f_coeffsUp){
        for(int y = 0; y < f_approcsimatedSpectrums[MAXIMUM_SPECTRUM]->size() / f_approcsimatedSpectrums[MAXIMUM_SPECTRUM]->sizeOffset(); ++y){
            int f_curInd = f_approcsimatedSpectrums[MAXIMUM_SPECTRUM]->sizeOffset() * y + f_index;
            f_approcsimatedSpectrums[MAXIMUM_SPECTRUM]->setData(f_approcsimatedSpectrums[MAXIMUM_SPECTRUM]->data(f_curInd) * koeff.k_a + koeff.k_b,f_curInd);
            f_approcsimatedSpectrums[MINIMUM_SPECTRUM]->setData(f_approcsimatedSpectrums[MINIMUM_SPECTRUM]->data(f_curInd) * koeff.k_a + koeff.k_b,f_curInd);
        }
        ++f_index;
    }

    f_noiseProtocol->addApproximated(f_approcsimatedSpectrums);
    f_noiseProtocol->addCoeffs(f_coeffsUp,f_coeffsDown);
    f_noiseProtocol->addChannelName(f_sourceSpectrums[MAXIMUM_SPECTRUM]->mnemonic());

    Operator f_operator;
    loadOperator(f_operatorID,f_operator);
    f_noiseProtocol->addOperator(f_operator);
    f_noiseProtocol->createPDF();
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
               FROM SpectrumCalibCoeffs \
               WHERE SCCDeviceID = ? AND SCCNumLines = ? AND SCCDataStep = ? AND SCCDateSave = ?;");
    f_query.addBindValue(deviceID);
    f_query.addBindValue(numLines);
    f_query.addBindValue(dataStep);
    f_query.addBindValue(dateSave);
    f_query.exec();
    qDebug() << f_query.lastError().text() << "findCoeffs";
    if(f_query.next())
       return f_query.value(0).toInt();
   return 0;
}

int SaverLoaderCalibDB::findNoiseProtocol(std::shared_ptr<ProtocolInfo> protInfo){
    if(!m_db->isOpen())
        return 0;
    QSqlQuery f_query;
    f_query.prepare("SELECT CalibID\
               FROM Calibrations \
               WHERE CDateTime = ? AND CReferenceRefID = ? AND CChannel = ? ;");
    f_query.addBindValue(protInfo->dateTime());
    f_query.addBindValue(protInfo->indexRefDB());
    f_query.addBindValue(protInfo->channelName());
    f_query.exec();
    qDebug() << f_query.lastError().text() << "findNoiseProtocol";
    if(f_query.next())
       return f_query.value(0).toInt();
   return 0;
}

