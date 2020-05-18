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


bool ILogData::openInterpreter(){
   return false;
}

bool ILogData::isReady(){
    return true;
}

bool ILogData::setLoader(ILoaderLogData *loader){
    return false;
}

bool ILogData::setSaver(ISaverLogData *saver){
    return false;
}

bool ILogData::setInterpreter(IInterpreterLogData *interpreter){
    return false;
}

QMap<QString,ICurve*> *ILogData::curves(){
    return nullptr;
}

QList<IBlock*> *ILogData::blocks(){
    return nullptr;
}

void ILogData::findCurvesMap(){

}


QSharedPointer<ILogData> ILogData::createLogData(){
    QSharedPointer<ILogData> f_ptrLogData(dynamic_cast<ILogData*>(new LogData()));
    return f_ptrLogData;
}
