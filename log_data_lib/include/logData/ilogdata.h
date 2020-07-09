#ifndef ILOGDATA_H
#define ILOGDATA_H

#include <QObject>
#include "iloaderlogdata.h"
#include "iinterpreterlogdata.h"
#include "isaverlogdata.h"


class ILogData : public QObject{
    Q_OBJECT

public:
    ILogData();
    ILogData(ILogData &logData){Q_UNUSED(logData)}

    ILogData &operator=(const ILogData &logData){Q_UNUSED(logData)}

    virtual ~ILogData();

    virtual bool load();
    virtual bool save();
    virtual bool openInterpreterConsole(){return false;}
    virtual bool openInterpreterScript(){return false;}
    virtual bool openInterpreterEditor(){return false;}

    virtual bool isReady();
    virtual bool isInterpreter(){return false;}

    virtual bool setLoader(ILoaderLogData *loader);
    virtual bool setSaver(ISaverLogData *saver);
    virtual bool setInterpreter(IInterpreterLogData *interpreter);
    virtual void setName(QString name){Q_UNUSED(name)}

    virtual void addBlock(IBlock *block){Q_UNUSED(block)}

    virtual QMap<QString,ICurve*> *curves();
    virtual QList<IBlock *> *blocks();
    virtual QString name(){return QString();}

signals:
    void ready();

public slots:
    virtual void dataUpdate(){}
    virtual void dataReady(){}

public:
    static QSharedPointer<ILogData> createLogData();
};

#endif // ILOGDATA_H
