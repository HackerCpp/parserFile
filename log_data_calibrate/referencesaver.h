#ifndef REFERENCESAVER_H
#define REFERENCESAVER_H
#include "geologysqlitedb.h"


class ReferenceSaver : public GeologySQLiteDB
{
    void createTable();
public:
    ReferenceSaver();
    ReferenceSaver(QSqlDatabase *db);
    ~ReferenceSaver()override;

    int saveReference(const ICurve &curveMaximum,const ICurve &curveAverage,int deviceID);

};

#endif // REFERENCESAVER_H
