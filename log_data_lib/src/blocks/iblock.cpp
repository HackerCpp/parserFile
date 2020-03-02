#include "iblock.h"


IBlock::IBlock(){}
IBlock::~IBlock(){}

bool IBlock::setName(const TypeBlock &typeBlock){
    return false;
}

bool IBlock::setName(const QString &name){
    return false;
}

IBlock::TypeBlock IBlock::name(){
    return NO_BLOCK;
}


bool IBlock::parser(const char *body,uint32_t size){
    return false;
}

