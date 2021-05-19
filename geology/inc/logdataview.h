#ifndef LOGDATAVIEW_H
#define LOGDATAVIEW_H

#include <QWidget>
#include "ilogdata.h"
#include <QSharedPointer>
#include <QTabWidget>
#include <QHBoxLayout>
#include <QSplitter>
#include "datamodel.h"
#include "datatreeview.h"
#include "graphicwidget.h"
using namespace std;

class LogDataView : public QWidget
{
    Q_OBJECT

    QList<shared_ptr<ILogData> > *m_logDataList;
    QHBoxLayout *m_mainHorLayout;
    QSplitter *m_splitter;
    DataModel *m_dataModel;
    DataTreeView *m_dataTreeView;
    GraphicWidget *m_graphicWidget;

public:
    explicit LogDataView(QWidget *parent = nullptr);
    ~LogDataView();

    void addLogData(shared_ptr<ILogData> logData);
    shared_ptr<ILogData> currentLogData();//{return m_dataModel->curentLogData();};
    //ILogData* currentLogData(){return m_dataModel->curentLogData();};
public slots:
    void lastDataReady();

signals:

};

#endif // LOGDATAVIEW_H
