#ifndef LOGDATA_H
#define LOGDATA_H

#include "alogdata.h"
#include "aloaderlogdata.h"



class LogData : public ALogData{
    ILoaderLogData *m_loader;
    IInterpreterLogData *m_interpreter;
    QList<IBlock*> *m_blocks;
    QMap<QString,ICurve*> *m_curvesMap;

public:
    LogData();
    ~LogData()override;

    bool load()override;
    bool save()override;
    bool openInterpreter()override;

    bool setLoader(ILoaderLogData *loader)override;
    bool setInterpreter(IInterpreterLogData *interpreter)override;

    virtual QMap<QString,ICurve*> *curves()override;
    virtual QList<IBlock*> *blocks()override;

public slots:
    void findCurvesMap()override;

};

#endif // LOGDATA_H
