#include "aloaderlogdata.h"

ALoaderLogData::ALoaderLogData(){
    m_blocks = nullptr;
}


ALoaderLogData::~ALoaderLogData(){

}


bool ALoaderLogData::start(){
    return false;
}

bool ALoaderLogData::stop(){
    return false;

}

bool ALoaderLogData::isReady(){
    return true;

}

bool ALoaderLogData::setBlocks(QList<IBlock> *blocks){
    m_blocks = blocks;
    return false;
}


