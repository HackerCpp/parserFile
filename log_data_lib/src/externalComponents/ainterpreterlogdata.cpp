#include "ainterpreterlogdata.h"

AinterpreterLogData::AinterpreterLogData(){

}

AinterpreterLogData::~AinterpreterLogData(){

}

bool AinterpreterLogData::openConsole(){
    return false;
}

bool AinterpreterLogData::openScript(){
    return false;
}

bool AinterpreterLogData::setBlocks(QList<IBlock *> *blocks){
    m_blocks = blocks;
    return true;
}
