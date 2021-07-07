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
#include "gfmsaver.h"
#include <QMessageBox>


SQLite3Saver::SQLite3Saver(QSqlDatabase *db) :
    m_db(db),m_isDeleteDB(false)
{

    if(!m_db){
        m_isDeleteDB = true;
        m_settings = std::make_unique<QSettings>(new QSettings("settings.ini",QSettings::IniFormat));
        m_db = new QSqlDatabase(QSqlDatabase::addDatabase("QSQLITE"));
        /*QString f_openPath = m_settings->value("paths/pathOpenDB").toString();
        QString filePath = QFileDialog().getOpenFileName(nullptr, tr("Open File"),f_openPath,tr("*.db"));
        if(filePath.isEmpty())
            return;
        m_settings->setValue("paths/pathOpenDB",filePath);*/
        m_db->setDatabaseName("sqliteDB\\GeoDB.db");
        if(!m_db->open()){
            qDebug() << m_db->lastError().text();
        }
    }
    if(m_db->isOpen()){
        QSqlQuery f_query;
        f_query.prepare(
            "CREATE TABLE IF NOT EXISTS LogDataDataBlock (\
                    LDDataBlockID       INTEGER PRIMARY KEY AUTOINCREMENT,\
                    LDDBLastСhanges     DATETIME,\
                    LDDBQuantityVectors STRING,\
                    LDDBModuleMnemonic  STRING,\
                    LDDBNameRecord      STRING,\
                    LDDCPlugins         TEXT,\
                    LDDCTimeID          INTEGER REFERENCES LogDataCurve (LDCurveID),\
                    LDDCDepthID         INTEGER REFERENCES LogDataCurve (LDCurveID) \
                );");
        f_query.exec();
        qDebug() << f_query.lastError().text();
        f_query.prepare(
            "CREATE TABLE IF NOT EXISTS LogDataCurve (\
                    LDCurveID           INTEGER  PRIMARY KEY AUTOINCREMENT UNIQUE,\
                    LDCLastСhanges      DATETIME,\
                    LDCMnemonic         TEXT,\
                    LDCTimeID           INTEGER  REFERENCES LogDataCurve (LDCurveID),\
                    LDCDepthID          INTEGER  REFERENCES LogDataCurve (LDCurveID),\
                    LDCShortCutID       INTEGER  REFERENCES LogDataShortCut (LDShortCutID),\
                    LDCSizeOffsetInByte INTEGER,\
                    LDCSizeOfType       INTEGER,\
                    LDCDataType         TEXT,\
                    LDCRecordPoint      DOUBLE,\
                    LDCUID              TEXT,\
                    LDCDATA             BLOB,\
                    LDCCompressionRatio DOUBLE,\
                    LDCCompressionMethod INTEGER  DEFAULT (1),\
                    LDCDataBlockID       INTEGER  REFERENCES LogDataDataBlock (LDDataBlockID) \
                );");
        f_query.exec();
        qDebug() << f_query.lastError().text();
        f_query.prepare("CREATE TABLE IF NOT EXISTS LogDataLinkCurveParamInfo (\
                    LDLinkParameterParamInfoID INTEGER PRIMARY KEY AUTOINCREMENT UNIQUE,\
                    LDLPPICurveID              INTEGER REFERENCES LogDataCurve (LDCurveID),\
                    LDLPPIParamInfoID          INTEGER REFERENCES LogDataParamInfo (LDParamInfoID) \
                );");
        f_query.exec();
        qDebug() << f_query.lastError().text();
        f_query.prepare("CREATE TABLE IF NOT EXISTS LogDataParamInfo (\
                    LDParamInfoID INTEGER PRIMARY KEY AUTOINCREMENT UNIQUE,\
                    LDPIIndex     TEXT,\
                    LDPIValue     TEXT,\
                    LDPIType      INTEGER\
        );");
        f_query.exec();
        qDebug() << f_query.lastError().text();
        f_query.prepare("CREATE TABLE IF NOT EXISTS LogDataShortCut (\
                    LDShortCutID INTEGER PRIMARY KEY AUTOINCREMENT UNIQUE,\
                    LDSCRef      TEXT,\
                    LDSCName     TEXT\
                );");
         f_query.exec();
         qDebug() << f_query.lastError().text();
    }
}

SQLite3Saver::~SQLite3Saver(){
    if(m_isDeleteDB){
        if(m_db){
            if(m_db->isOpen())
                m_db->close();
            delete m_db;m_db = nullptr;
        }
        QSqlDatabase::removeDatabase(QLatin1String(QSqlDatabase::defaultConnection));
    }
}


bool SQLite3Saver::save(){
    m_isReady = false;
    if(!m_blocks){
        qDebug() << "Нечего сохранять,добавьте данные GFMSaver::save()";
    }
    for(auto block : *m_blocks)
        saveBlock(*block);

    m_isReady = true;
    return true;
}

int SQLite3Saver::saveDataBlockAndCurves(const IBlock &block){
    auto f_dataBlock = dynamic_cast<const DataBlock *>(&block);
    if(!m_db->isOpen() || !f_dataBlock)
        return 0;
    int f_indexDataBlock = saveDataBlock(block);
    if(!f_indexDataBlock)
        return f_indexDataBlock;
    for(auto curve : *f_dataBlock->curves()){
        saveCurve(*curve,f_indexDataBlock);
    }

}

int SQLite3Saver::saveDataBlock(const IBlock &block){
    auto f_dataBlock = dynamic_cast<const DataBlock *>(&block);
    if(!m_db->isOpen() || !f_dataBlock)
        return 0;
    if(int indexDataBlock = findDataBlock(block);indexDataBlock)
        return indexDataBlock;
    QSqlQuery f_query;
    f_query.prepare(
"INSERT INTO LogDataDataBlock (\
    LDDBLastСhanges,LDDBQuantityVectors,LDDBModuleMnemonic,\
    LDDBNameRecord,LDDCPlugins,LDDCTimeID,LDDCDepthID)\n\
VALUES (?,?,?,?,?,?,?);");
    f_query.addBindValue(QDateTime::currentDateTime().toString());
    f_query.addBindValue(f_dataBlock->numberOfVectors());
    f_query.addBindValue(f_dataBlock->moduleMnemonic());
    f_query.addBindValue(f_dataBlock->nameRecord());
    f_query.addBindValue(f_dataBlock->plugins());
    f_query.addBindValue(saveCurve(*f_dataBlock->time()));
    f_query.addBindValue(saveCurve(*f_dataBlock->depth()));
    f_query.exec();
    return findDataBlock(block);

    return 0;
}

int SQLite3Saver::saveBlock(const IBlock &block){
    switch (block.name()) {
        case IBlock::NO_BLOCK:{
            break;
        }
        case IBlock::DATA_BLOCK:{
            return saveDataBlockAndCurves(block);
            break;
        }
        case IBlock::FORMS_BLOCK:{
            break;
        }
        case IBlock::TOOLINFO_BLOCK:{
            break;
        }
        case IBlock::HEADER_BLOCK:{
            break;
        }
        case IBlock::LABELS_BLOCK:{
            break;
        }
    }
    return 0;
}

int SQLite3Saver::saveCurve(const ICurve &curve,int indexDataBlock ){
    if(!m_db->isOpen())
        return 0;
    if(findCurve(curve))
        return updateCurve(curve);

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
        LDCDataType,LDCRecordPoint,LDCUID,LDCDATA,\
        LDCCompressionRatio,LDCCompressionMethod,LDCDataBlockID)\n\
        VALUES (\
        ?,?,?,?,?,?,?,?,?,?,?,?,?,?);");
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
     QByteArray f_baCompressed;
     GFMSaver::gzipCompress(curve.data(),f_baCompressed,7);
     f_query.addBindValue(f_baCompressed);
     f_query.addBindValue((qreal)curve.data().size() / (qreal)f_baCompressed.size() );
     f_query.addBindValue(1);
     f_query.addBindValue(indexDataBlock);
    f_query.exec();
    int f_currentIndexCurve = findCurve(curve);
    if(f_currentIndexCurve)
        saveDesc(*curve.desc(),f_currentIndexCurve);
    return f_currentIndexCurve;
}



int SQLite3Saver::saveShortCut(const ShortCut &shortCut){
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

int SQLite3Saver::saveDesc(const Desc &desc,int indexCurve){
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

int SQLite3Saver::updateCurve(const ICurve &curve){
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
        "UPDATE LogDataCurve\
        SET LDCLastСhanges = ?,LDCMnemonic = ?,LDCTimeID=?,\
            LDCDepthID=?,LDCShortCutID=?,LDCSizeOffsetInByte=?,\
            LDCSizeOfType = ?,LDCDataType = ?,LDCRecordPoint =?,\
            LDCDATA=? \
        WHERE LDCUID=?");
     f_query.addBindValue(QDateTime::currentDateTime().toString());
     f_query.addBindValue(curve.mnemonic());
     f_query.addBindValue(f_timeId);
     f_query.addBindValue(f_depthId);
     f_query.addBindValue(f_ShortCutId);
     f_query.addBindValue(curve.sizeOffsetInBytes());
     f_query.addBindValue(curve.sizeOffsetInBytes() / curve.sizeOffset());
     f_query.addBindValue(curve.dataType());
     f_query.addBindValue(curve.recordPoint());
     QByteArray f_baCompressed;
     GFMSaver::gzipCompress(curve.data(),f_baCompressed,7);
     f_query.addBindValue(f_baCompressed);
     f_query.addBindValue(curve.uniqID());
    f_query.exec();

    int f_currentIndexCurve = findCurve(curve);
    if(f_currentIndexCurve)
        saveDesc(*curve.desc(),f_currentIndexCurve);
    return f_currentIndexCurve;
}




int SQLite3Saver::findDataBlock(const IBlock &block){
    auto f_dataBlock = dynamic_cast<const DataBlock *>(&block);
    if(!m_db->isOpen() || !f_dataBlock)
        return 0;
    QSqlQuery f_query;
    f_query.prepare("\
SELECT LDDataBlockID \n\
FROM LogDataDataBlock \n\
WHERE LogDataDataBlock.LDDBQuantityVectors = ? \n\
AND LogDataDataBlock.LDDBModuleMnemonic=?\n\
AND LogDataDataBlock.LDDBNameRecord=? ;");
    f_query.addBindValue(f_dataBlock->numberOfVectors());
    f_query.addBindValue(f_dataBlock->moduleMnemonic());
    f_query.addBindValue(f_dataBlock->nameRecord());
    f_query.exec();

    if(f_query.next())
       return f_query.value(0).toInt();

   return 0;
}

int SQLite3Saver::findShortCut(const ShortCut &shortCut){
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

int SQLite3Saver::findParamInfo(const Paraminfo &paramInfo,Parameters::Type type){
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

int SQLite3Saver::findCurve(const ICurve &curve){
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
