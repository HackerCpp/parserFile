#ifndef ALOGDATA_H
#define ALOGDATA_H

#include "ilogdata.h"
#include <QList>
#include "iblock.h"

class ALogData : public ILogData{

protected:
    ILoaderLogData *m_loader;
    ISaverLogData *m_saver;
    IInterpreterLogData *m_interpreter;
    bool m_isReady;
public:
    ALogData();
    ALogData(ALogData &logdata){Q_UNUSED(logdata)}

    ALogData &operator=(const ALogData &logData){Q_UNUSED(logData)}

    virtual ~ALogData()override;

    virtual bool load()override;
    virtual bool save()override;
    virtual bool openInterpreterConsole()override{return false;}
    virtual bool openInterpreterScript()override{return false;}
    virtual bool openInterpreterEditor()override{return false;}

    virtual bool isReady()override;
    virtual bool isInterpreter()override{return false;}

    virtual bool setLoader(ILoaderLogData *loader)override;
    virtual bool setSaver(ISaverLogData *saver)override;
    virtual bool setInterpreter(IInterpreterLogData *interpreter)override;
    virtual void setName(QString name)override{Q_UNUSED(name)}

    virtual void addBlock(IBlock *block)override{Q_UNUSED(block)}

    virtual QList<IBlock *> *blocks()override;
    virtual QString name()override{ return QString();}
    IInterpreterLogData *interpreter()override{return m_interpreter;}



public slots:
    virtual void dataUpdate()override{}
    virtual void dataReady()override;
};

#endif // ALOGDATA_H
