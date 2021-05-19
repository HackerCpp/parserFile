#include "sqlite3saver.h"
#include <QSqlDatabase>
#include <QDebug>
#include <QSqlError>
#include <QSettings>
#include <QFileDialog>
#include "icurve.h"
#include <QSqlQuery>
#include <QByteArray>


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
}

int SQLite3Saver::saveCurve(ICurve &curve){
    if(!m_db->isOpen())
        return 0;
    int f_descId = saveDesc(*curve.desc());
    int f_ShortCutId = saveShortCut(curve.shortCut());
    int f_timeId = 1;//saveCurve(*curve.time());
    int f_depthId = 2;//saveCurve(*curve.depth());
    QString f_dataAsString = QTextCodec::codecForMib(1015)->toUnicode(curve.data());
    QSqlQuery f_query;
    f_query.exec(
        QString("INSERT INTO LogDataCurve (\
        LDCMnemonic,LDCTimeID,LDCDepthID,LDCDescID,\
        LDCShortCutID,LDCSizeOffsetInByte,LDCSizeOfType,\
        LDCDataType,LDCRecordPoint,LDCUID,LDCDATA)\
        VALUES (\
        '%1','%2','%3','%4','%5','%6',\
        '%7','%8','%9','%10','%11' );")
        .arg(curve.mnemonic())
        .arg(f_timeId).arg(f_depthId).arg(f_descId).arg(f_ShortCutId)
        .arg(curve.sizeOffsetInBytes()).arg(curve.sizeOffsetInBytes()/curve.sizeOffset())
            .arg(curve.dataType()).arg(curve.recordPoint()).arg(curve.uniqID()).arg(f_dataAsString)
);
    qDebug() << f_query.lastError().text();
}

int SQLite3Saver::saveDesc(const Desc &desc){
    if(!m_db->isOpen())
        return 0;
}

int SQLite3Saver::saveShortCut(const ShortCut &shortCut){
    if(!m_db->isOpen())
        return 0;

}
