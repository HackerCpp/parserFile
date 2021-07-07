#ifndef REFERENCESAVER_H
#define REFERENCESAVER_H
#include "geologysqlitedb.h"

enum ReferenceStatus{STATUS_ORDINARY,STATUS_REFERENCE};

class ReferenceSaver : public GeologySQLiteDB
{
public:
    explicit ReferenceSaver();
    ~ReferenceSaver()override;

    int saveReference(const QVector<ICurve*> &referenceSpectrums,int deviceID,ReferenceStatus status = STATUS_ORDINARY);
    int findReference(int devID,QString lastChange,int cMaxID,int cMinID,int lines,QString dataStep);

};

#endif // REFERENCESAVER_H
