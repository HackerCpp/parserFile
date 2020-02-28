#ifndef ILOGDATA_H
#define ILOGDATA_H

#include <QObject>
#include "iloaderlogdata.h"

class ILogData : public QObject{
    Q_OBJECT
public:
    ILogData();
    virtual ~ILogData();

    virtual bool load();
    virtual bool save();

    virtual bool isReady();

    virtual bool setLoader(ILoaderLogData *loader);

signals:
    virtual void ready();
public:
    static ILogData *createLogData();
};

#endif // ILOGDATA_H
