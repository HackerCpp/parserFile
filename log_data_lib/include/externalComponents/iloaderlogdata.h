#ifndef ILOADLOGDATA_H
#define ILOADLOGDATA_H

#include "iblock.h"
#include <QList>

class ILoaderLogData{

public:
    ILoaderLogData();
    virtual ~ILoaderLogData();

    virtual bool start();
    virtual bool stop();
    virtual bool isReady();

    virtual bool setBlocks(QList<IBlock> *blocks);
};

#endif // ILOADLOGDATA_H
