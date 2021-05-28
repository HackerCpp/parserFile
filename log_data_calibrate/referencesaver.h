#ifndef REFERENCESAVER_H
#define REFERENCESAVER_H
#include "geologysqlitedb.h"


class ReferenceSaver : public GeologySQLiteDB
{
public:
    ReferenceSaver();
    ~ReferenceSaver()override;

    int saveReference(const ICurve &curveMaximum,const ICurve &curveAverage);
};

#endif // REFERENCESAVER_H
