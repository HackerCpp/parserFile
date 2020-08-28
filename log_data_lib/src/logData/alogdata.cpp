#include "alogdata.h"



ALogData::ALogData()
    :   m_loader(nullptr), m_saver(nullptr),
        m_interpreter(nullptr),m_isReady(false){

}

ALogData::~ALogData(){

}

bool ALogData::load(){
    return false;
}

bool ALogData::save(){
    return false;
}

bool ALogData::isReady(){
   return m_isReady;
}

bool ALogData::setInterpreter(IInterpreterLogData *interpreter){
    Q_UNUSED(interpreter)
    return false;
}

QList<IBlock *> *ALogData::blocks(){
   return nullptr;
}

bool ALogData::setLoader(ILoaderLogData *loader){
    Q_UNUSED(loader)
    return false;
}

bool ALogData::setSaver(ISaverLogData *saver){
    Q_UNUSED(saver)
    return false;
}

void ALogData::dataReady(){
    dataUpdate();
    m_isReady = true;
    emit ready();
}

