#ifndef ALOADERLOGDATA_H
#define ALOADERLOGDATA_H

#include "iloaderlogdata.h"

class ALoaderLogData :public ILoaderLogData{
protected:
    QList<IBlock> *m_blocks;

    ALoaderLogData();
    ~ALoaderLogData();


    virtual bool start();
    virtual bool stop();
    virtual bool isReady();

    bool setBlocks(QList<IBlock> *blocks)override;
};

#endif // ALOADERLOGDATA_H
