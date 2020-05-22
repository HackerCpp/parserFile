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
    //QTabWidget *m_tabs;
    QHBoxLayout *m_mainHorLayout;
    QSplitter *m_splitter;
    DataModel *m_dataModel,*m_doubleDataModel;
    DataTreeView *m_dataTreeView,*m_doubleDataTreeWiev;
    GraphicWidget *m_graphicWidget;

public:
    explicit LogDataView(QWidget *parent = nullptr);
    ~LogDataView();

    void addLogData(QSharedPointer<ILogData> logData);
public slots:
    void lastDataReady();

signals:

};

#endif // LOGDATAVIEW_H
