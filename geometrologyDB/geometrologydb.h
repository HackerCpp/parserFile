#ifndef GEOMETROLOGYDB_H
#define GEOMETROLOGYDB_H

#include "geometrologyDB_global.h"
#include "iinterpreterlogdata.h"

class QSqlDatabase;

class GEOMETROLOGYDB_EXPORT GeometrologyDB : public QObject
{
    Q_OBJECT
    QVector<QString> m_types = {"QSQLITE"};
    QSqlDatabase *m_db;
public:
    enum TypesDb{SQLITE};

    GeometrologyDB();

    void setTypeDB(const TypesDb type);
    void setNameDB(const QString &name);

    bool connectDB();
    void disconnectDB();

    void insertCalibrationDataIntoTheInterpreter(IInterpreterLogData *interpreter);
};

#endif // GEOMETROLOGYDB_H
