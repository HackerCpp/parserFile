#ifndef ISAVERLOGDATA_H
#define ISAVERLOGDATA_H
#include "iblock.h"
#include <QList>
#include <QObject>

class ISaverLogData : public QObject
{
        Q_OBJECT
public:
    ISaverLogData();
    virtual ~ISaverLogData();

    virtual bool save();
    virtual bool isReady();

    virtual bool setBlocks(QList<IBlock*> *blocks);

signals:
    void ready();
};

#endif // ISAVERLOGDATA_H
