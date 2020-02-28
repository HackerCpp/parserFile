#ifndef ABLOCK_H
#define ABLOCK_H

#include "iblock.h"

class ABlock : public IBlock{
public:
    ABlock();
    virtual ~ABlock();

    virtual bool setName(const TypeBlock &typeBlock);
    virtual TypeBlock name();
    virtual bool parser(const char *body,uint32_t size);
};

#endif // ABLOCK_H
