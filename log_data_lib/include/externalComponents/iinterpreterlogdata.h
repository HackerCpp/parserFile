#ifndef IINTERPRETERLOGDATA_H
#define IINTERPRETERLOGDATA_H

#include "icurve.h"
#include "iblock.h"

class IInterpreterLogData{

public:
    IInterpreterLogData();
    virtual ~IInterpreterLogData();

    virtual bool openConsole();
    virtual bool openScript();

    virtual bool setBlocks(QList<IBlock *> *blocks);

    virtual void dataUpdate(){}
};

#endif // IINTERPRETERLOGDATA_H
