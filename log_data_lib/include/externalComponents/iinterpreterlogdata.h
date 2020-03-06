#ifndef IINTERPRETERLOGDATA_H
#define IINTERPRETERLOGDATA_H

#include "icurve.h"

class IInterpreterLogData{

public:
    IInterpreterLogData();
    virtual ~IInterpreterLogData();

    virtual bool openConsole();
    virtual bool openScript();

    virtual bool setCurves(QMap<QString,ICurve*> *curves);
};

#endif // IINTERPRETERLOGDATA_H
