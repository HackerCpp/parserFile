#ifndef SELECTINGIDFROMDB_H
#define SELECTINGIDFROMDB_H

#include <QWidget>
#include "geologysqlitedb.h"

class QSqlQueryModel;
class QTableView;
class QVBoxLayout;

class SelectingIDFromDB : public QWidget,public GeologySQLiteDB
{

    QSqlQueryModel *m_model;
    QTableView *m_tableView;
    QVBoxLayout *m_mainLayout;
    int m_str,m_id;

public:
    explicit SelectingIDFromDB(QString query);
    int getID();
    void closeEvent(QCloseEvent *event);
    bool eventFilter(QObject *object, QEvent *event);
};

#endif // SELECTINGIDFROMDB_H
