#ifndef ILOADLOGDATA_H
#define ILOADLOGDATA_H

#include "iblock.h"
#include <QList>
#include <QObject>
#include <QThread>

class ILoaderLogData : public QThread{
    Q_OBJECT
public:
    ILoaderLogData();
    virtual ~ILoaderLogData();

    virtual bool download();
    virtual bool isReady();

    virtual bool setBlocks(QList<IBlock *> *blocks);

signals:
    void ready();
};

#endif // ILOADLOGDATA_H
