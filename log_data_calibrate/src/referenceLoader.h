#ifndef SELECTCURVEDB_H
#define SELECTCURVEDB_H

#include <memory>
#include <QWidget>
#include "geologysqlitedb.h"

class QSqlDatabase;
class QSettings;
class ICurve;
class Desc;
class QSqlQueryModel;
class QTableView;
class QVBoxLayout;

class ReferenceLoader : public QWidget,public GeologySQLiteDB
{
    QSqlQueryModel *m_model;
    QTableView *m_tableView;
    QVBoxLayout *m_mainLayout;
    int m_currentCurveIndex;

public:
    explicit ReferenceLoader(int lines,QString data_step,QSqlDatabase *db = nullptr);
    ~ReferenceLoader();

    void loadRefCurves(QVector<ICurve*> &referenceSpectrums,int &idReference);

    void closeEvent (QCloseEvent *event) override;
    bool eventFilter(QObject *object, QEvent *event)override;
    int findReference(const ICurve &refMax,const ICurve &refAver);
};

#endif // SELECTCURVEDB_H
