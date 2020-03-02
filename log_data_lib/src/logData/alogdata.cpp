#include "alogdata.h"



ALogData::ALogData(){

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


bool ALogData::setInterpreter(IInterpreterLogData *interpreter){
    return false;
}

bool ALogData::setLoader(ILoaderLogData *loader){
    return false;
}
