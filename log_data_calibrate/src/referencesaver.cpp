#include "referencesaver.h"
#include <QSqlDatabase>
#include <QDebug>
#include <QSqlError>
#include <QFileDialog>
#include <QSettings>
#include "sqlite3saver.h"
#include "icurve.h"
#include <QSqlQuery>
#include <QInputDialog>
#include <QMessageBox>
#include "protocolnoise.h"



ReferenceSaver::ReferenceSaver(QSqlDatabase *db) : GeologySQLiteDB(db){}

ReferenceSaver::~ReferenceSaver(){}

int ReferenceSaver::saveReference(const QVector<ICurve*> &referenceSpectrums,int deviceID,ReferenceStatus status){
    if(!m_db->isOpen())
        return 0;
    auto f_saverLogData = std::make_unique<SQLite3Saver>(m_db);
    int f_indexRefMAX = f_saverLogData->saveCurve(*referenceSpectrums[MAXIMUM_SPECTRUM]);
    int f_indexRefMIN = f_saverLogData->saveCurve(*referenceSpectrums[MINIMUM_SPECTRUM]);
    int f_indexRefNOISE = f_saverLogData->saveCurve(*referenceSpectrums[NOISE_SPECTRUM]);

    QSqlQuery f_query;
    QString f_dateTime = QDateTime::currentDateTime().toString();
    f_query.prepare("INSERT INTO SpectrumCalibReference \
(SCRDeviceID,SCRLastChanges,SCRStatus,SCRCurveMaxID,SCRCurveMinID,SCRCurveNoiseID,SCRLines,SCRDataStep ,SCRComment )\
                    VALUES (?,?,?,?,?,?,?,?,?);");
    f_query.addBindValue(deviceID);
    f_query.addBindValue(f_dateTime);
    f_query.addBindValue(status);
    f_query.addBindValue(f_indexRefMAX);
    f_query.addBindValue(f_indexRefMIN);
    f_query.addBindValue(f_indexRefNOISE);
    f_query.addBindValue(referenceSpectrums[MAXIMUM_SPECTRUM]->sizeOffset());
    f_query.addBindValue(referenceSpectrums[MAXIMUM_SPECTRUM]->desc()->param("data_step"));
    //bool bOk;
    //QString f_comment = QInputDialog::getText( 0, tr("Comment"),"",QLineEdit::Normal,curveMaximum.shortCut().name(),&bOk);
    f_query.addBindValue(referenceSpectrums[MAXIMUM_SPECTRUM]->shortCut().name());
    f_query.exec();
    if(f_query.lastError().text().isEmpty())
        QMessageBox::question(nullptr,tr("Saver DB"),tr("Reference Saved!"),QMessageBox::Ok);
    else
        QMessageBox::warning(nullptr,tr("Warning"),tr("Error save reference! ") + f_query.lastError().text(),QMessageBox::Ok);
    return findReference(deviceID,f_dateTime,f_indexRefMAX,f_indexRefMIN,referenceSpectrums[MAXIMUM_SPECTRUM]->sizeOffset(),referenceSpectrums[MAXIMUM_SPECTRUM]->desc()->param("data_step"));
}

int ReferenceSaver::findReference(int devID,QString lastChange,int cMaxID,int cMinID,int lines,QString dataStep){
    if(!m_db->isOpen())
        return 0;
    QSqlQuery f_query;
    f_query.prepare("SELECT SCReferenceID\
               FROM SpectrumCalibReference \
               WHERE SCRDeviceID=? AND SCRLastChanges=? AND SCRCurveMaxID=? AND SCRCurveMinID=? AND SCRLines=? AND SCRDataStep=?;");
    f_query.addBindValue(devID);
    f_query.addBindValue(lastChange);
    f_query.addBindValue(cMaxID);
    f_query.addBindValue(cMinID);
    f_query.addBindValue(lines);
    f_query.addBindValue(dataStep);
    f_query.exec();
    qDebug() << f_query.lastError().text();
    if(f_query.next())
       return f_query.value(0).toInt();
   return 0;
}
