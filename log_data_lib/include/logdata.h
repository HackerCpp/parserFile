#ifndef LOGDATA_H
#define LOGDATA_H

#include "alogdata.h"


class LogData : public ALogData{

public:
    LogData();
    ~LogData();

    bool load();
    bool save();
};

#endif // LOGDATA_H
