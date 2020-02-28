#include "ilogdata.h"
#include "logdata.h"

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
    return false;
}

ILogData *ILogData::createLogData(){
    return dynamic_cast<ILogData*>(new LogData());
}
