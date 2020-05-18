#ifndef LOGDATA_H
#define LOGDATA_H

#include "alogdata.h"
#include "aloaderlogdata.h"



class LogData : public ALogData{
    ILoaderLogData *m_loader;
    ISaverLogData *m_saver;
    IInterpreterLogData *m_interpreter;
    QList<IBlock*> *m_blocks;
    QMap<QString,ICurve*> *m_curvesMap;
    QString m_name;

public:
    LogData();
    ~LogData()override;

    bool load()override;
    bool save()override;
    bool openInterpreter()override;

    bool setLoader(ILoaderLogData *loader)override;
    bool setSaver(ISaverLogData *saver)override;
    bool setInterpreter(IInterpreterLogData *interpreter)override;
    virtual void setName(QString name)override{m_name = name;}

    virtual QMap<QString,ICurve*> *curves()override;
    virtual QList<IBlock*> *blocks()override;
    virtual QString name()override{return m_name;}

public slots:
    void findCurvesMap()override;

};

#endif // LOGDATA_H
