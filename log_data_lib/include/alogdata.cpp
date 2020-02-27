#include "alogdata.h"


ALogData::ALogData(){
    m_blocks = new QList<IBlock*>;
}

ALogData::~ALogData(){
    if(m_blocks)
        delete m_blocks;
}

bool ALogData::load(){
    return false;
}

bool ALogData::save(){
    return false;
}
