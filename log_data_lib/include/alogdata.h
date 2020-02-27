#ifndef ALOGDATA_H
#define ALOGDATA_H

#include "ilogdata.h"
#include <QList>
#include "iblock.h"

class ALogData : public ILogData{
    QList<IBlock*> *m_blocks;
public:
    ALogData();
    virtual ~ALogData();

    virtual bool load();
    virtual bool save();
};

#endif // ALOGDATA_H
