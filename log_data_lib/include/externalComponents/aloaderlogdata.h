#ifndef ALOADERLOGDATA_H
#define ALOADERLOGDATA_H

#include "iloaderlogdata.h"


class ALoaderLogData :public ILoaderLogData{

protected:
    bool m_isReady;
    QList<IBlock *> *m_blocks;
public:
    ALoaderLogData();
    virtual ~ALoaderLogData();


    virtual bool download()override;
    virtual bool isReady()override;

     virtual bool setBlocks(QList<IBlock *> *blocks)override;
};

#endif // ALOADERLOGDATA_H
