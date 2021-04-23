#include "ilogdata.h"
#include "logdata.h"
#include <QSharedPointer>

std::shared_ptr<ILogData> ILogData::createLogData(){
    return std::make_shared<LogData>();
    //QSharedPointer<ILogData> f_ptrLogData(dynamic_cast<ILogData*>(new LogData()));
    //return f_ptrLogData;
}
