#ifndef ILOADLOGDATA_H
#define ILOADLOGDATA_H

#include "iblock.h"
#include <QList>
#include <QObject>

class ILoaderLogData : public QObject{
    Q_OBJECT
public:
    ILoaderLogData();
    virtual ~ILoaderLogData();

    virtual bool download();
    virtual bool isReady();

    virtual bool setBlocks(QList<IBlock*> *blocks);

signals:
    void ready();
};

#endif // ILOADLOGDATA_H
