#ifndef AINTERPRETERLOGDATA_H
#define AINTERPRETERLOGDATA_H

#include <QMap>
#include "icurve.h"
#include "iinterpreterlogdata.h"

class AinterpreterLogData : public IInterpreterLogData{
protected:
    QMap<QString,ICurve*> *m_curves;

public:
    AinterpreterLogData();
    virtual ~AinterpreterLogData();

    virtual bool openConsole();
    virtual bool openScript();
};

#endif // AINTERPRETERLOGDATA_H
