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

ReferenceSaver::ReferenceSaver()
{
    if(m_db->isOpen()){
        QSqlQuery f_query;
        f_query.prepare("CREATE TABLE IF NOT EXISTS SpectrumCalibReference (\
                            SCReferenceID  INTEGER  PRIMARY KEY AUTOINCREMENT UNIQUE,\
                            SCRLastСhanges DATETIME,\
                            SCRCurveMaxID  INTEGER  REFERENCES LogDataCurve (LDCurveID),\
                            SCRCurveAverID INTEGER  REFERENCES LogDataCurve (LDCurveID),\
                            SCRLines       INTEGER,\
                            SCRDataStep    TEXT,\
                            SCRComment     TEXT\
                        );"
            );
        f_query.exec();
        qDebug() << f_query.lastError().text();
    }

}


ReferenceSaver::~ReferenceSaver(){
}

int ReferenceSaver::saveReference(const ICurve &curveMaximum,const ICurve &curveAverage){
    if(!m_db->isOpen())
        return 0;
    auto f_saverLogData = std::make_unique<SQLite3Saver>(m_db);
    int f_indexRefMAX = f_saverLogData->saveCurve(curveMaximum);
    int f_indexRefAVER = f_saverLogData->saveCurve(curveAverage);

    QSqlQuery f_query;
    f_query.prepare("INSERT INTO SpectrumCalibReference (\
                    SCRLastСhanges,SCRCurveMaxID,SCRCurveAverID,SCRLines,SCRDataStep ,SCRComment )\
                    VALUES (?,?,?,?,?,?);");
    f_query.addBindValue(QDateTime::currentDateTime().toString());
    f_query.addBindValue(f_indexRefMAX);
    f_query.addBindValue(f_indexRefAVER);
    f_query.addBindValue(curveMaximum.sizeOffset());
    f_query.addBindValue(curveMaximum.desc()->param("data_step"));
    bool bOk;
    QString f_name = QInputDialog::getText( 0, tr("Comment"),"",QLineEdit::Normal,
                                         curveMaximum.shortCut().name(),&bOk);
    f_query.addBindValue(f_name);
    f_query.exec();
    if(f_query.lastError().text().isEmpty())
        QMessageBox::question(nullptr,tr("Saver DB"),tr("Reference Saved!"),QMessageBox::Ok);
    else
        QMessageBox::warning(nullptr,tr("Warning"),f_query.lastError().text(),QMessageBox::Ok);
    return 0;
}
