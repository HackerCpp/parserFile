#include "aloaderlogdata.h"

ALoaderLogData::ALoaderLogData(){
    m_blocks = nullptr;
    m_isReady = false;
}


ALoaderLogData::~ALoaderLogData(){

}


bool ALoaderLogData::download(){
    return false;
}


bool ALoaderLogData::isReady(){
    return m_isReady;

}

bool ALoaderLogData::setBlocks(QList<QSharedPointer<IBlock> > *blocks){
    m_blocks = blocks;
    return false;
}


