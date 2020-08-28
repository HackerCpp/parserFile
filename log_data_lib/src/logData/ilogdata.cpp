#include "ilogdata.h"
#include "logdata.h"
#include <QSharedPointer>

QSharedPointer<ILogData> ILogData::createLogData(){
    QSharedPointer<ILogData> f_ptrLogData(dynamic_cast<ILogData*>(new LogData()));
    return f_ptrLogData;
}
