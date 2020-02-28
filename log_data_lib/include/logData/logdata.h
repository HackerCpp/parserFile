#ifndef LOGDATA_H
#define LOGDATA_H

#include "alogdata.h"
#include "aloaderlogdata.h"


class LogData : public ALogData{
    ILoaderLogData *m_loader;
    QList<IBlock> *m_blocks;

public:
    LogData();
    ~LogData()override;

    bool load()override;
    bool save()override;

    bool setLoader(ILoaderLogData *loader)override;
};

#endif // LOGDATA_H
