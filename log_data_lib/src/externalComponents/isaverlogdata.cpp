#include "isaverlogdata.h"

ISaverLogData::ISaverLogData()
{

}

ISaverLogData::~ISaverLogData(){

}

bool ISaverLogData::save(){
    return false;
}

bool ISaverLogData::isReady(){
    return false;
}

bool ISaverLogData::setBlocks(QList<IBlock *> *blocks){
    Q_UNUSED(blocks)
    return false;
}
