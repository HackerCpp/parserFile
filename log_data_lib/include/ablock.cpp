#include "ablock.h"

ABlock::ABlock()
{

}

ABlock::~ABlock(){

}

bool ABlock::setName(const TypeBlock &typeBlock){
    return false;
}

IBlock::TypeBlock ABlock::name(){
    return NO_BLOCK;
}

bool ABlock::parser(const char *body,uint32_t size){
    return false;
}
