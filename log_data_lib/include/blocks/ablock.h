#ifndef ABLOCK_H
#define ABLOCK_H

#include "iblock.h"

class ABlock : public IBlock{
protected:
    TypeBlock m_type;
public:
    ABlock(){}
    virtual ~ABlock(){}

    TypeBlock name()override{return m_type;}
    virtual bool parser(const char *body,uint32_t size)override{return false;}
};

#endif // ABLOCK_H
