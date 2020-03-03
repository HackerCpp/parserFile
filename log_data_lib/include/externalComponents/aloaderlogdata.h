#ifndef ALOADERLOGDATA_H
#define ALOADERLOGDATA_H

#include "iloaderlogdata.h"

class ALoaderLogData :public ILoaderLogData{
protected:
    QList<IBlock*> *m_blocks;
public:
    ALoaderLogData();
    virtual ~ALoaderLogData();


    virtual bool download();
    virtual bool isReady();

     virtual bool setBlocks(QList<IBlock*> *blocks);
};

#endif // ALOADERLOGDATA_H
