#ifndef GEOMETROLOGYDB_H
#define GEOMETROLOGYDB_H

#include "geometrologyDB_global.h"
#include "iinterpreterlogdata.h"
#include <QWidget>
#include <QVBoxLayout>
#include <QPointer>
#include <QSplitter>
#include <QTextEdit>
#include <QPushButton>
#include "calibserialization.h"

class QSqlDatabase;
class QTableView;
class QSqlQueryModel;
class QVBoxLayout;

class GEOMETROLOGYDB_EXPORT GeometrologyDB : public QWidget
{
    Q_OBJECT
    QVector<QString> m_types = {"QSQLITE"};
    QSqlDatabase *m_db;
    QPointer<QTableView> m_view;
    QSqlQueryModel *m_model;
    QPointer<QVBoxLayout> m_mainLayout;
    IInterpreterLogData *m_interpreter;
    QPointer<QSplitter> m_splitter;
    QPointer<QTextEdit> m_textedit;
    QPointer<QPushButton> m_btnInsert;
    CalibrSerialization *m_serialization;
public:
    enum TypesDb{SQLITE};

    GeometrologyDB();
    ~GeometrologyDB();

    void setTypeDB(const TypesDb type);
    void setNameDB(const QString &name);

    bool connectDB();
    void disconnectDB();

    void setInterpreterInterpreter(IInterpreterLogData *interpreter);

public slots:
    void updateCalibInfo(const QModelIndex &index);
    void insertDataInterpreter();

};

#endif // GEOMETROLOGYDB_H
