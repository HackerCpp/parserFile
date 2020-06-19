#include "iloaderlogdata.h"

ILoaderLogData::ILoaderLogData(){

}

ILoaderLogData::~ILoaderLogData(){

}

bool ILoaderLogData::download(){
    return false;
}


bool ILoaderLogData::isReady(){
    return true;
}

bool ILoaderLogData::setBlocks(QList<IBlock *> *blocks){
    Q_UNUSED(blocks)
    return false;
}

