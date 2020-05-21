#ifndef ASAVERLOGDATA_H
#define ASAVERLOGDATA_H
#include "isaverlogdata.h"

class ASaverLogData : public ISaverLogData{
protected:
    bool m_isReady;
    QList<QSharedPointer<IBlock> > *m_blocks;
public:
    ASaverLogData();
    ~ASaverLogData()override;


    virtual bool save()override;
    virtual bool isReady()override;

    virtual bool setBlocks(QList<QSharedPointer<IBlock> > *blocks)override;
};

#endif // ASAVERLOGDATA_H
