#ifndef LOGDATA_H
#define LOGDATA_H

#include "alogdata.h"
#include "aloaderlogdata.h"



class LogData : public ALogData{
    ILoaderLogData *m_loader;
    ISaverLogData *m_saver;
    IInterpreterLogData *m_interpreter;
    QList<QSharedPointer<IBlock> > *m_blocks;
    QString m_name;

public:
    LogData();
    LogData(const LogData &logData);

    LogData &operator=(const LogData &logData);

    ~LogData()override;

    bool load()override;
    bool save()override;
    bool openInterpreterConsole()override;
    bool openInterpreterScript()override;

    virtual bool isInterpreter()override{return m_interpreter != nullptr;}

    bool setLoader(ILoaderLogData *loader)override;
    bool setSaver(ISaverLogData *saver)override;
    bool setInterpreter(IInterpreterLogData *interpreter)override;
    virtual void setName(QString name)override{m_name = name;}

    void addBlock(QSharedPointer<IBlock> block)override;

    virtual QList<QSharedPointer<IBlock> > *blocks()override;
    virtual QString name()override{return m_name;}

public slots:
    void dataUpdate()override;
    void dataReady()override;

};

#endif // LOGDATA_H
