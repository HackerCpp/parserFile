#include "sqlite3saver.h"
#include <QSqlDatabase>
#include <QDebug>
#include <QSqlError>
#include <QSettings>
#include <QFileDialog>
#include "icurve.h"
#include <QSqlQuery>
#include <QByteArray>
#include <QDateTime>
#include "shortcut.h"


SQLite3Saver::SQLite3Saver()
{
    m_settings = std::make_unique<QSettings>(new QSettings("settings.ini",QSettings::IniFormat));
    m_db = new QSqlDatabase(QSqlDatabase::addDatabase("QSQLITE"));
    QString f_openPath = m_settings->value("paths/pathOpenDB").toString();
    QString filePath = QFileDialog().getOpenFileName(nullptr, tr("Open File"),f_openPath,tr("*.db"));
    m_settings->setValue("paths/pathOpenDB",filePath);
    m_db->setDatabaseName(filePath);
    if(!m_db->open()){
        qDebug() << m_db->lastError().text();
    }
    else{
        qDebug() << "OpenDb";

    }
}

SQLite3Saver::~SQLite3Saver(){
    if(m_db){
        if(m_db->isOpen())
            m_db->close();
        delete m_db;m_db = nullptr;
    }
    QSqlDatabase::removeDatabase(QLatin1String(QSqlDatabase::defaultConnection));
}

int SQLite3Saver::saveCurve(ICurve &curve){
    if(!m_db->isOpen())
        return 0;
    ShortCut f_shortCut = curve.shortCut();
    int f_ShortCutId = saveShortCut(f_shortCut);
    int f_timeId = 0;
    int f_depthId = 0;
    if(QString f_draw_type = curve.desc()->param("draw_type");
            f_draw_type != "DEPTH" && f_draw_type != "TIME" ){
        if(curve.time()){
            if(f_timeId = findCurve(*curve.time());!f_timeId)
                f_timeId = saveCurve(*curve.time());
        }
        if(curve.depth())
            if(f_depthId = findCurve(*curve.depth());!f_depthId)
                f_depthId = saveCurve(*curve.depth());
    }
    QSqlQuery f_query;
    f_query.prepare(
        "INSERT INTO LogDataCurve (\
        LDCLastСhanges,LDCMnemonic,LDCTimeID,LDCDepthID,\
        LDCShortCutID,LDCSizeOffsetInByte,LDCSizeOfType,\
        LDCDataType,LDCRecordPoint,LDCUID,LDCDATA)\
        VALUES (\
        ?,?,?,?,?,?,?,?,?,?,?);");
     f_query.addBindValue(QDateTime::currentDateTime().toString());
     f_query.addBindValue(curve.mnemonic());
     f_query.addBindValue(f_timeId);
     f_query.addBindValue(f_depthId);
     f_query.addBindValue(f_ShortCutId);
     f_query.addBindValue(curve.sizeOffsetInBytes());
     f_query.addBindValue(curve.sizeOffsetInBytes() / curve.sizeOffset());
     f_query.addBindValue(curve.dataType());
     f_query.addBindValue(curve.recordPoint());
     f_query.addBindValue(curve.uniqID());
     f_query.addBindValue(curve.data());
    f_query.exec();
    f_query.prepare("SELECT LDCurveID\
                    FROM LogDataCurve\
                    WHERE LogDataCurve.LDCUID = ?;");
    f_query.addBindValue(curve.uniqID());
    f_query.exec();
    int f_currentIndexCurve = 0;
    if(f_query.next())
       f_currentIndexCurve = f_query.value(0).toInt();
    if(f_currentIndexCurve)
        saveDesc(*curve.desc(),f_currentIndexCurve);
    return f_currentIndexCurve;
}



int SQLite3Saver::saveShortCut(ShortCut &shortCut){
    if(!m_db->isOpen() || shortCut.name().isEmpty())
        return 0;
    if(int f_indexShortCut = findShortCut(shortCut);f_indexShortCut)
        return f_indexShortCut;
    QSqlQuery f_query;
    f_query.prepare(
        "INSERT INTO LogDataShortCut (\
        LDSCRef,LDSCName)\
        VALUES (?,?);");
     f_query.addBindValue(shortCut.ref());
     f_query.addBindValue(shortCut.name());
     f_query.exec();
     return findShortCut(shortCut);
}

int SQLite3Saver::saveParamInfo(Paraminfo &paramInfo,Parameters::Type type){
    if(!m_db->isOpen())
        return 0;

    if(int f_indexParamInfo = findParamInfo(paramInfo,type);f_indexParamInfo)
        return f_indexParamInfo;
    QSqlQuery f_query;
    f_query.prepare(
        "INSERT INTO LogDataParamInfo (\
        LDPIIndex,LDPIValue,LDPIType)\
        VALUES (?,?,?);");
     f_query.addBindValue(paramInfo.index());
     f_query.addBindValue(paramInfo.value());
     f_query.addBindValue(type);
     f_query.exec();
    return findParamInfo(paramInfo,type);
}

int SQLite3Saver::saveDesc(Desc &desc,int indexCurve){
    auto f_parsmeters = desc.parameters()->vectorParameters();
    auto f_calibrations = desc.calibrations()->vectorParameters();
    for(auto paramInfo : *f_parsmeters){
        int f_indexParamInfo = saveParamInfo(*paramInfo,Parameters::PARAM);
        linkCurveAndParamInfo(indexCurve, f_indexParamInfo);
    }
    for(auto paramInfo : *f_calibrations){
        int f_indexParamInfo = saveParamInfo(*paramInfo,Parameters::CALIB);
        linkCurveAndParamInfo(indexCurve, f_indexParamInfo);
    }
    return 0;
}

int SQLite3Saver::linkCurveAndParamInfo(int indexCurve, int indexParamInfo){
    if(!m_db->isOpen())
        return 0;

    if(int f_indexLinkCP = findLinkCurveAndParamInfo(indexCurve,indexParamInfo);f_indexLinkCP)
        return f_indexLinkCP;
    QSqlQuery f_query;
    f_query.prepare(
        "INSERT INTO LogDataLinkCurveParamInfo (\
        LDLPPICurveID,LDLPPIParamInfoID)\
        VALUES (?,?);");
     f_query.addBindValue(indexCurve);
     f_query.addBindValue(indexParamInfo);
     f_query.exec();
    return findLinkCurveAndParamInfo(indexCurve,indexParamInfo);
}





int SQLite3Saver::findShortCut(ShortCut &shortCut){
    if(!m_db->isOpen())
        return 0;
    QSqlQuery f_query;
    f_query.prepare("SELECT LDShortCutID\
                    FROM LogDataShortCut\
                    WHERE LogDataShortCut.LDSCRef = ? AND LogDataShortCut.LDSCName = ?;");
    f_query.addBindValue(shortCut.ref());
    f_query.addBindValue(shortCut.name());
    f_query.exec();
    if(f_query.next())
       return f_query.value(0).toInt();
   return 0;
}

int SQLite3Saver::findParamInfo(Paraminfo &paramInfo,Parameters::Type type){
    if(!m_db->isOpen())
        return 0;
    QSqlQuery f_query;
    f_query.prepare("SELECT LDParamInfoID\
                    FROM LogDataParamInfo\
                    WHERE LogDataParamInfo.LDPIIndex = ?\
         AND LogDataParamInfo.LDPIValue = ? AND LogDataParamInfo.LDPIType = ?;");
            f_query.addBindValue(paramInfo.index());
            f_query.addBindValue(paramInfo.value());
            f_query.addBindValue(type);
    f_query.exec();
    if(f_query.next())
       return f_query.value(0).toInt();
   return 0;
}

int SQLite3Saver::findLinkCurveAndParamInfo(int indexCurve, int indexParamInfo){
    if(!m_db->isOpen())
        return 0;
    QSqlQuery f_query;
    f_query.prepare("SELECT LDLinkParameterParamInfoID\
                    FROM LogDataLinkCurveParamInfo\
                    WHERE LogDataLinkCurveParamInfo.LDLPPICurveID = ?\
         AND LogDataLinkCurveParamInfo.LDLPPIParamInfoID = ?;");
            f_query.addBindValue(indexCurve);
            f_query.addBindValue(indexParamInfo);
    f_query.exec();
    if(f_query.next())
       return f_query.value(0).toInt();
   return 0;
}

int SQLite3Saver::findCurve(ICurve &curve){
    if(!m_db->isOpen())
        return 0;
    QSqlQuery f_query;
    f_query.prepare("SELECT LDCurveID\
                    FROM LogDataCurve\
                    WHERE LogDataCurve.LDCUID = ?;");
            f_query.addBindValue(curve.uniqID());
    f_query.exec();
    if(f_query.next())
       return f_query.value(0).toInt();
   return 0;
}
