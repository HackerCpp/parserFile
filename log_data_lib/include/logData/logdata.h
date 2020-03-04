#ifndef LOGDATA_H
#define LOGDATA_H

#include "alogdata.h"
#include "aloaderlogdata.h"



class LogData : public ALogData{
    ILoaderLogData *m_loader;
    IInterpreterLogData *m_interpreter;
    QList<IBlock*> *m_blocks;

public:
    LogData();
    ~LogData()override;

    bool load()override;
    bool save()override;
    bool openInterpreter()override;

    bool setLoader(ILoaderLogData *loader)override;
    bool setInterpreter(IInterpreterLogData *interpreter)override;
};

#endif // LOGDATA_H
