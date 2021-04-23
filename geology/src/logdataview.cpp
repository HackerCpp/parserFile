#include "logdataview.h"
#include "formsblock.h"
#include "graphiceditor.h"

LogDataView::LogDataView(QWidget *parent) : QWidget(parent)
{
    m_logDataList = new QList<shared_ptr<ILogData> >;
    m_mainHorLayout = new QHBoxLayout(this);
    m_splitter = new QSplitter();
    m_dataModel = new DataModel();
    m_dataTreeView = new DataTreeView();
    m_graphicWidget = new GraphicWidget();
    m_dataTreeView->setModel(m_dataModel);

    m_splitter->addWidget(m_dataTreeView);
    m_splitter->addWidget(m_graphicWidget);
    m_mainHorLayout->addWidget(m_splitter);
    m_mainHorLayout->setMargin(0);

    this->setLayout(m_mainHorLayout);
}

LogDataView::~LogDataView(){
    if(m_logDataList){delete m_logDataList; m_logDataList = nullptr;}

}

void LogDataView::addLogData(shared_ptr<ILogData> logData){
    m_logDataList->push_back(logData);
    if(!logData->isReady()){
        connect(logData.get(),&ILogData::ready,this,&LogDataView::lastDataReady);
    }
    else{
        lastDataReady();
    }
}

void LogDataView::lastDataReady(){
    shared_ptr<ILogData> f_curentLogData = m_logDataList->last();
    disconnect(f_curentLogData.get(),&ILogData::ready,this,&LogDataView::lastDataReady);
    if(f_curentLogData == nullptr){
        m_logDataList->removeLast();
        return;
    }
    m_dataModel->addLogData(f_curentLogData);
    m_graphicWidget->addLogData(f_curentLogData);
}
