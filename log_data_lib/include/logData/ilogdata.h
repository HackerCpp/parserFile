#ifndef ILOGDATA_H
#define ILOGDATA_H

#include <QObject>
#include "iloaderlogdata.h"
#include "iinterpreterlogdata.h"

class ILogData : public QObject{
    Q_OBJECT
public:
    ILogData();
    virtual ~ILogData();

    virtual bool load();
    virtual bool save();
    virtual bool openInterpreter();

    virtual bool isReady();

    virtual bool setLoader(ILoaderLogData *loader);
    virtual bool setInterpreter(IInterpreterLogData *interpreter);

signals:
    virtual void ready();
public:
    static ILogData *createLogData();
};

#endif // ILOGDATA_H
