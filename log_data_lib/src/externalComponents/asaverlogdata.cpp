#include "asaverlogdata.h"

ASaverLogData::ASaverLogData()
    :m_blocks(nullptr){

}

ASaverLogData::~ASaverLogData(){

}


bool ASaverLogData::save(){
    return false;
}

bool ASaverLogData::isReady(){
    return false;
}

bool ASaverLogData::setBlocks(QList<QSharedPointer<IBlock> > *blocks){
    m_blocks = blocks;
    return false;
}
