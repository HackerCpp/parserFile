#include "alogdata.h"



ALogData::ALogData(){
    m_isReady = false;
}

ALogData::~ALogData(){

}

bool ALogData::load(){
    return false;
}

bool ALogData::save(){
    return false;
}

bool ALogData::openInterpreter(){
    return false;
}

bool ALogData::isReady(){
   return m_isReady;
}

bool ALogData::setInterpreter(IInterpreterLogData *interpreter){
    return false;
}

QMap<QString,ICurve*> *ALogData::curves(){
   return nullptr;
}

QList<IBlock*> *ALogData::blocks(){
   return nullptr;
}

bool ALogData::setLoader(ILoaderLogData *loader){
    return false;
}

bool ALogData::setSaver(ISaverLogData *saver){
    return false;
}

void ALogData::findCurvesMap(){

}
