#include "iblock.h"
#include <QDebug>

IBlock::IBlock(){}
IBlock::~IBlock(){}


IBlock::TypeBlock IBlock::name(){
    return NO_BLOCK;
}

bool IBlock::parser(const char *body,uint32_t size){
    return false;
}
void IBlock::setName(QString name)
{
    m_name=name;
}
QString IBlock:: names()
{
    return m_name;
}
