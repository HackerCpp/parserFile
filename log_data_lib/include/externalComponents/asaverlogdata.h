#ifndef ASAVERLOGDATA_H
#define ASAVERLOGDATA_H
#include "isaverlogdata.h"

class ASaverLogData : public ISaverLogData
{
public:
    ASaverLogData();
    ~ASaverLogData()override;


    virtual bool save()override;
    virtual bool isReady()override;

    virtual bool setBlocks(QList<IBlock*> *blocks)override;
};

#endif // ASAVERLOGDATA_H
