#include "sqlite3loader.h"
#include <QSqlDatabase>
#include <QFileDialog>
#include <QSqlError>
#include <QSettings>
#include <QDebug>
#include <QSqlQuery>
#include <icurve.h>

SQLite3Loader::SQLite3Loader()
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

SQLite3Loader::~SQLite3Loader(){

    if(m_db){
        if(m_db->isOpen())
            m_db->close();
        delete m_db;m_db = nullptr;
    }
    QSqlDatabase::removeDatabase(QLatin1String(QSqlDatabase::defaultConnection));
}


ICurve * SQLite3Loader::loadCurve(int index){
    if(!m_db->isOpen())
        return nullptr;
    QSqlQuery f_query;
    f_query.prepare("SELECT LDCurveID,LDCLastСhanges,LDCMnemonic,\
                    LDCTimeID,LDCDepthID, LDCShortCutID,\
                    LDCSizeOffsetInByte,LDCSizeOfType,LDCDataType,\
                    LDCRecordPoint, LDCUID,LDCDATA\
               FROM LogDataCurve\
               WHERE LogDataCurve.LDCurveID = ?;");
    f_query.addBindValue(index);
    f_query.exec();
    if(!f_query.lastError().text().isEmpty())
        return nullptr;
    ICurve *f_curve;
    if(f_query.next()){
        f_curve = ICurve::curveCreater(f_query.value("LDCDataType").toString());
        f_curve->setMnemonic(f_query.value("LDCMnemonic").toString());
        f_curve->setRecordPoint(f_query.value("LDCRecordPoint").toDouble());
        uint f_sizeOffsetInBytes = f_query.value("LDCSizeOffsetInByte").toUInt();
        f_curve->setSizeOffsetInBytes(f_sizeOffsetInBytes);
        QByteArray f_data = f_query.value("LDCDATA").toByteArray();
        f_curve->setData(f_data.data(),f_data.size() / f_sizeOffsetInBytes);
        f_curve->setDesc(loadDesc(index));
        qDebug() << f_curve->mnemonic() << f_curve->data(100);
        return f_curve;
    }
    return nullptr;
}

Desc *SQLite3Loader::loadDesc(int curveIndex){
    if(!m_db->isOpen())
        return nullptr;
    Desc *f_desc = new Desc();
    auto f_parameters = f_desc->parameters();
    auto f_calibrations = f_desc->calibrations();

    QSqlQuery f_query;
    f_query.prepare("SELECT LogDataParamInfo.LDPIIndex,LogDataParamInfo.LDPIValue,LogDataParamInfo.LDPIType\
                    FROM LogDataLinkCurveParamInfo\
                    JOIN LogDataParamInfo ON LogDataParamInfo.LDParamInfoID = LogDataLinkCurveParamInfo.LDLPPIParamInfoID\
                    WHERE LogDataLinkCurveParamInfo.LDLPPICurveID = ?;");
    f_query.addBindValue(curveIndex);
    f_query.exec();
    if(!f_query.lastError().text().isEmpty())
        return nullptr;
    while(f_query.next()){
        qDebug() << f_query.value("LogDataParamInfo.LDPIType").toInt()
                 << f_query.value("LogDataParamInfo.LDPIIndex").toString()
                 << f_query.value("LogDataParamInfo.LDPIValue").toString();
        if(f_query.value("LogDataParamInfo.LDPIType").toInt() == Parameters::CALIB)
            f_calibrations->insert(f_query.value("LogDataParamInfo.LDPIIndex").toString(),f_query.value("LogDataParamInfo.LDPIValue").toString());
        if(f_query.value("LogDataParamInfo.LDPIType").toInt() == Parameters::PARAM)
            f_parameters->insert(f_query.value("LogDataParamInfo.LDPIIndex").toString(),f_query.value("LogDataParamInfo.LDPIValue").toString());
    }
    return f_desc;
}
