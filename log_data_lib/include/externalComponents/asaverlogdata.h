#ifndef ASAVERLOGDATA_H
#define ASAVERLOGDATA_H
#include "isaverlogdata.h"

class ASaverLogData : public ISaverLogData{
protected:
    bool m_isReady;
    QList<IBlock *> *m_blocks;
public:
    ASaverLogData();
    ~ASaverLogData()override;


    virtual bool save()override;
    virtual bool isReady()override;

    virtual bool setBlocks(QList<IBlock *> *blocks)override;
};

#endif // ASAVERLOGDATA_H
