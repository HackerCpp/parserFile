#ifndef ALOGDATA_H
#define ALOGDATA_H

#include "ilogdata.h"
#include <QList>
#include "iblock.h"

class ALogData : public ILogData{
protected:
    bool m_isReady;
public:
    ALogData();
    virtual ~ALogData()override;

    virtual bool load()override;
    virtual bool save()override;
    virtual bool openInterpreter()override;

    virtual bool isReady()override;

    virtual bool setLoader(ILoaderLogData *loader)override;
    virtual bool setInterpreter(IInterpreterLogData *interpreter)override;

    virtual QMap<QString,ICurve*> *curves()override;
    virtual QList<IBlock*> *blocks()override;

/*signals:
    virtual void ready()override;*/

public slots:
    virtual void findCurvesMap()override;
};

#endif // ALOGDATA_H
