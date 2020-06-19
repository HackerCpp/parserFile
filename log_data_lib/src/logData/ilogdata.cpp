#include "ilogdata.h"
#include "logdata.h"
#include <QSharedPointer>

ILogData::ILogData(){

}

ILogData::~ILogData(){

}

bool ILogData::load(){
   return false;
}

bool ILogData::save(){
    return false;
}

bool ILogData::isReady(){
    return true;
}

bool ILogData::setLoader(ILoaderLogData *loader){
    Q_UNUSED(loader)
    return false;
}

bool ILogData::setSaver(ISaverLogData *saver){
    Q_UNUSED(saver)
    return false;
}

bool ILogData::setInterpreter(IInterpreterLogData *interpreter){
    Q_UNUSED(interpreter)
    return false;
}

QMap<QString,ICurve*> *ILogData::curves(){
    return nullptr;
}

QList<IBlock *> *ILogData::blocks(){
    return nullptr;
}

QSharedPointer<ILogData> ILogData::createLogData(){
    QSharedPointer<ILogData> f_ptrLogData(dynamic_cast<ILogData*>(new LogData()));
    return f_ptrLogData;
}
