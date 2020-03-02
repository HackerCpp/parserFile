#ifndef ALOGDATA_H
#define ALOGDATA_H

#include "ilogdata.h"
#include <QList>
#include "iblock.h"

class ALogData : public ILogData{

public:
    ALogData();
    virtual ~ALogData();

    virtual bool load();
    virtual bool save();
    virtual bool openInterpreter();

    virtual bool setLoader(ILoaderLogData *loader);
    virtual bool setInterpreter(IInterpreterLogData *interpreter);

};

#endif // ALOGDATA_H
