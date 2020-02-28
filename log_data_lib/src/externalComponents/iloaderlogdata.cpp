#include "iloaderlogdata.h"

ILoaderLogData::ILoaderLogData(){

}

ILoaderLogData::~ILoaderLogData(){

}

bool ILoaderLogData::start(){
    return false;
}

bool ILoaderLogData::stop(){
    return true;
}

bool ILoaderLogData::isReady(){
    return true;
}

bool ILoaderLogData::setBlocks(QList<IBlock> *blocks){
    return false;
}

