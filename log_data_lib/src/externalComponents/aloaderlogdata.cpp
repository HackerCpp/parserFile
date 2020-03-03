#include "aloaderlogdata.h"

ALoaderLogData::ALoaderLogData(){
    m_blocks = nullptr;
}


ALoaderLogData::~ALoaderLogData(){

}


bool ALoaderLogData::download(){
    return false;
}


bool ALoaderLogData::isReady(){
    return true;

}

bool ALoaderLogData::setBlocks(QList<IBlock*> *blocks){
    m_blocks = blocks;
    return false;
}


