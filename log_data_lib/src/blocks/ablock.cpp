#include "ablock.h"

ABlock::ABlock(){

}

ABlock::~ABlock(){

}

IBlock::TypeBlock ABlock::name(){
    return m_type;
}

bool ABlock::parser(const char *body,uint32_t size){
    return false;
}
