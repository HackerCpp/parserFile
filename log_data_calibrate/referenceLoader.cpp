#include "referenceLoader.h"
#include <QSettings>
#include <QSqlDatabase>
#include <QFileDialog>
#include <QSqlError>
#include <QDebug>
#include <QSqlQueryModel>
#include <QTableView>
#include <QVBoxLayout>
#include <QApplication>
#include "sqlite3loader.h"
#include <QHeaderView>
#include <QModelIndex>
#include "icurve.h"
#include "sqlite3saver.h"
#include <QSqlQuery>


ReferenceLoader::ReferenceLoader(int lines,QString data_step,QSqlDatabase *db)
    : GeologySQLiteDB(db){

    m_currentCurveIndex = -1;
    m_model = new QSqlQueryModel;

    m_tableView = new QTableView;
    m_mainLayout = new QVBoxLayout();
    if(!m_db->isOpen()){
        qDebug() << m_db->lastError().text();
        return;
    }
    m_model->setQuery(QString("SELECT SpectrumCalibReference.SCReferenceID,CalibDevice.CDName,CalibDevice.CDNumber,\
                      SpectrumCalibReference.SCRLastСhanges,SpectrumCalibReference.SCRCurveMaxID,\
                      SpectrumCalibReference.SCRCurveAverID,SpectrumCalibReference.SCRLines,SpectrumCalibReference.SCRDataStep,SpectrumCalibReference.SCRComment\
                 FROM SpectrumCalibReference\
                 JOIN CalibDevice ON CalibDevice.CDeviceID = SpectrumCalibReference.SCRDeviceID\
                 WHERE SpectrumCalibReference.SCRLines = %1 AND \
                 SpectrumCalibReference.SCRDataStep = '%2' ;").arg(lines).arg(data_step)
                );
    /*(m_model->setQuery("\
    SELECT LogDataCurve.LDCurveID,\
          LogDataCurve.LDCLastСhanges,\
          LogDataCurve.LDCMnemonic,\
          LogDataCurve.LDCSizeOffsetInByte,\
          LogDataCurve.LDCDataType,\
          LogDataCurve.LDCRecordPoint,\
          LogDataParamInfo.LDPIValue\
    FROM LogDataLinkCurveParamInfo\
    JOIN LogDataCurve ON  LogDataCurve.LDCurveID = LogDataLinkCurveParamInfo.LDLPPICurveID\
    JOIN LogDataParamInfo ON LogDataParamInfo.LDParamInfoID = LogDataLinkCurveParamInfo.LDLPPIParamInfoID\
    WHERE LogDataParamInfo.LDPIValue = 'SPECTRUM';"
    );*/
    m_tableView->setModel(m_model);
    m_tableView->horizontalHeader()->setSectionResizeMode( QHeaderView::ResizeToContents );

    m_mainLayout->addWidget(m_tableView);
    setLayout(m_mainLayout);
    m_tableView->viewport()->installEventFilter(dynamic_cast<QWidget*>(this));
    setWindowModality(Qt::ApplicationModal);
    setAttribute(Qt::WA_DeleteOnClose);
    show();
}

ReferenceLoader::~ReferenceLoader(){
    m_currentCurveIndex = -2;
}

void ReferenceLoader::loadRefCurves(ICurve *&refCurveMAX,ICurve *&refCurveAver){
    while(m_currentCurveIndex == -1){
        qApp->processEvents();
    }

    if(m_currentCurveIndex >= 0){
        int indexCurveMaximum = m_model->data(m_model->index(m_currentCurveIndex,4)).toInt();
        int indexCurveAverage = m_model->data(m_model->index(m_currentCurveIndex,5)).toInt();

        auto f_loaderDB = std::make_unique<SQLite3Loader>(m_db);
        refCurveMAX = f_loaderDB->loadCurve(indexCurveMaximum);
        refCurveAver = f_loaderDB->loadCurve(indexCurveAverage);
    }
}

void ReferenceLoader::closeEvent (QCloseEvent *event){
    Q_UNUSED(event)
    m_currentCurveIndex = -2;
}

bool ReferenceLoader::eventFilter(QObject *object, QEvent *event){
    if (object == m_tableView->viewport() && event->type() == QEvent::MouseButtonDblClick) {
        m_currentCurveIndex = m_tableView->currentIndex().row();
    }
    return false;
}

int ReferenceLoader::findReference(const ICurve &refMax,const ICurve &refAver){
    if(!m_db->isOpen())
        return 0;
    SQLite3Saver  f_saver = SQLite3Saver(m_db);
    int f_indexRefMax = f_saver.findCurve(refMax);
    int f_indexRefAver = f_saver.findCurve(refAver);
    if(!f_indexRefMax || !f_indexRefAver)
        return 0;
    QSqlQuery f_query;
    f_query.prepare("SELECT SCReferenceID \
                       FROM SpectrumCalibReference\
                       WHERE SpectrumCalibReference.SCRCurveMaxID = ? AND \
                       SpectrumCalibReference.SCRCurveAverID = ? ;");
    f_query.addBindValue(f_indexRefMax);
    f_query.addBindValue(f_indexRefAver);
    f_query.exec();
    if(QString error = f_query.lastError().text();!error.isEmpty()){
        qDebug() << error;
        return 0;
    }
    if(f_query.next())
        return f_query.value("SCReferenceID").toInt();
    return 0;

}
