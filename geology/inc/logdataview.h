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

class LogDataView : public QWidget
{
    Q_OBJECT

    QList<QSharedPointer<ILogData> > *m_logDataList;
    QHBoxLayout *m_mainHorLayout;
    QSplitter *m_splitter;
    DataModel *m_dataModel;
    DataTreeView *m_dataTreeView;
    GraphicWidget *m_graphicWidget;

public:
    explicit LogDataView(QWidget *parent = nullptr);
    ~LogDataView();

    void addLogData(QSharedPointer<ILogData> logData);
    ILogData * curentLogData(){return m_dataModel->curentLogData();};
public slots:
    void lastDataReady();

signals:

};

#endif // LOGDATAVIEW_H
