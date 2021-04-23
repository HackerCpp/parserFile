#ifndef ILOGDATA_H
#define ILOGDATA_H

#include <QObject>
#include "iloaderlogdata.h"
#include "iinterpreterlogdata.h"
#include "isaverlogdata.h"


class ILogData : public QObject{
    Q_OBJECT

public:
    ILogData(){}
    ILogData(ILogData &logData){Q_UNUSED(logData)}

    ILogData &operator=(const ILogData &logData){Q_UNUSED(logData)}

    virtual ~ILogData(){}

    virtual bool load(){return false;}
    virtual bool save(){return false;}
    virtual bool openInterpreterConsole(){return false;}
    virtual bool openInterpreterScript(){return false;}
    virtual bool openInterpreterEditor(){return false;}

    virtual bool isReady(){return true;}
    virtual bool isInterpreter(){return false;}

    virtual bool setLoader(ILoaderLogData *loader){Q_UNUSED(loader) return false;}
    virtual bool setSaver(ISaverLogData *saver){Q_UNUSED(saver) return false;}
    virtual bool setInterpreter(IInterpreterLogData *interpreter){Q_UNUSED(interpreter) return false;}
    virtual void setName(QString name){Q_UNUSED(name)}

    virtual void addBlock(IBlock *block){Q_UNUSED(block)}

    virtual QList<IBlock *> *blocks(){return nullptr;}
    virtual QString name(){return QString();}
    virtual IInterpreterLogData *interpreter(){return nullptr;}

signals:
    void ready();

public slots:
    virtual void dataUpdate(){}
    virtual void dataReady(){}

public:
    static std::shared_ptr<ILogData> createLogData() ;
};

#endif // ILOGDATA_H
