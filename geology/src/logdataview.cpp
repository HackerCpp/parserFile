#include "logdataview.h"
#include "formsblock.h"
#include "graphiceditor.h"

LogDataView::LogDataView(QWidget *parent) : QWidget(parent)
{
    m_logDataList = new QList<QSharedPointer<ILogData> >;
    m_tabs = new QTabWidget(this);
    m_mainHorLayout = new QHBoxLayout(this);
    m_splitter = new QSplitter();
    m_dataModel = new DataModel();
    m_doubleDataModel = new DataModel();
    m_dataTreeView = new DataTreeView();
    m_dataTreeView->setModel(m_dataModel);
    m_doubleDataTreeWiev = new DataTreeView();
    m_doubleDataTreeWiev->setModel(m_doubleDataModel);

    m_splitter->addWidget(m_dataTreeView);
    m_splitter->addWidget(m_doubleDataTreeWiev);
    m_splitter->addWidget(m_tabs);
    m_mainHorLayout->addWidget(m_splitter);

    this->setLayout(m_mainHorLayout);
}

LogDataView::~LogDataView(){
    if(m_logDataList){delete m_logDataList; m_logDataList = nullptr;}

}

void LogDataView::addLogData(QSharedPointer<ILogData> logData){
    m_logDataList->push_back(logData);
    if(!logData->isReady()){
        connect(logData.data(),&ILogData::ready,this,&LogDataView::lastDataReady);
    }
}

void LogDataView::lastDataReady(){
    QSharedPointer<ILogData> f_curentLogData = m_logDataList->last();
    m_dataModel->addLogData(f_curentLogData);
    if(!f_curentLogData)
        return;
    GraphicEditor *m_graphicEditor = new GraphicEditor(f_curentLogData);
    m_tabs->addTab(m_graphicEditor,f_curentLogData->name());
}
