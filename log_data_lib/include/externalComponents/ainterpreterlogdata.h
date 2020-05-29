#ifndef AINTERPRETERLOGDATA_H
#define AINTERPRETERLOGDATA_H

#include <QMap>

#include "iinterpreterlogdata.h"

class AinterpreterLogData : public IInterpreterLogData{
protected:
    QList<QSharedPointer<IBlock> > *m_blocks;

public:
    AinterpreterLogData();
    virtual ~AinterpreterLogData()override;

    virtual bool openConsole()override;
    virtual bool openScript()override;

    virtual bool setBlocks(QList<QSharedPointer<IBlock> > *blocks)override;
};

#endif // AINTERPRETERLOGDATA_H
