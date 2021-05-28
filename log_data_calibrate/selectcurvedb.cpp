#include "selectcurvedb.h"
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


ReferenceLoader::ReferenceLoader(int lines,QString data_step){

    m_currentCurveIndex = -1;
    m_model = new QSqlQueryModel;

    m_tableView = new QTableView;
    m_mainLayout = new QVBoxLayout();
    if(!m_db->isOpen()){
        qDebug() << m_db->lastError().text();
        return;
    }
    m_model->setQuery(QString("SELECT SCReferenceID,\
                      SCRLastСhanges,SCRCurveMaxID,\
                      SCRCurveAverID,SCRLines,SCRDataStep,SCRComment\
                 FROM SpectrumCalibReference\
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

ICurve *ReferenceLoader::getCurve(){
    while(m_currentCurveIndex == -1){
        qApp->processEvents();
    }
    ICurve *f_curve = nullptr;
    if(m_currentCurveIndex){
        auto f_loaderDB = std::make_unique<SQLite3Loader>(m_db);
        f_curve = f_loaderDB->loadCurve(m_currentCurveIndex);
    }
    return f_curve;
}

void ReferenceLoader::loadRefCurves(ICurve *&refCurveMAX,ICurve *&refCurveAver){
    while(m_currentCurveIndex == -1){
        qApp->processEvents();
    }

    if(m_currentCurveIndex >= 0){
        int indexCurveMaximum = m_model->data(m_model->index(m_currentCurveIndex,2)).toInt();
        int indexCurveAverage = m_model->data(m_model->index(m_currentCurveIndex,3)).toInt();

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
