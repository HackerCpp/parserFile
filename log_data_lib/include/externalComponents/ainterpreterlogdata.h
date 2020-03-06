#ifndef AINTERPRETERLOGDATA_H
#define AINTERPRETERLOGDATA_H

#include <QMap>

#include "iinterpreterlogdata.h"

class AinterpreterLogData : public IInterpreterLogData{
protected:
    QMap<QString,ICurve*> *m_curves;

public:
    AinterpreterLogData();
    virtual ~AinterpreterLogData()override;

    virtual bool openConsole()override;
    virtual bool openScript()override;

    virtual bool setCurves(QMap<QString,ICurve*> *curves)override;
};

#endif // AINTERPRETERLOGDATA_H
