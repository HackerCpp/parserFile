#include "ablock.h"

ABlock::ABlock()
{

}

ABlock::~ABlock(){

}

bool ABlock::setName(const TypeBlock &type){
    m_type = type;
    return true;
}

bool ABlock::setName(const QString &name){
    if(name.indexOf("[DATA_BLOCK]") != -1)
        m_type = DATA_BLOCK;
    else if(name.indexOf("[FORMS_BLOCK]") != -1)
        m_type = FORMS_BLOCK;
    else if(name.indexOf("[HEADER_BLOCK]") != -1)
        m_type = HEADER_BLOCK;
    else if(name.indexOf("[TOOLINFO_BLOCK]") != -1)
        m_type = TOOLINFO_BLOCK;
    else
        m_type =NO_BLOCK;

    return true;
}

IBlock::TypeBlock ABlock::name(){
    return NO_BLOCK;
}

bool ABlock::parser(const char *body,uint32_t size){
    return false;
}
