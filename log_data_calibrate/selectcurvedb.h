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
    ReferenceLoader(int lines,QString data_step);
    ~ReferenceLoader();

    ICurve *getCurve();
    void loadRefCurves(ICurve *&refCurveMAX,ICurve *&refCurveAver);

    void closeEvent (QCloseEvent *event) override;
    bool eventFilter(QObject *object, QEvent *event)override;
};

#endif // SELECTCURVEDB_H
