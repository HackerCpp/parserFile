#include "iinterpreterlogdata.h"

IInterpreterLogData::IInterpreterLogData(){

}

IInterpreterLogData::~IInterpreterLogData(){

}

bool IInterpreterLogData::openConsole(){
    return false;
}

bool IInterpreterLogData::openScript(){
     return false;
}

bool IInterpreterLogData::setBlocks(QList<QSharedPointer<IBlock> > *blocks){
    return false;
}
