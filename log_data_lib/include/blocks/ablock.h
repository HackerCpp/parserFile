#ifndef ABLOCK_H
#define ABLOCK_H

#include "iblock.h"


class ABlock : public IBlock{
protected:
    TypeBlock m_type;
public:
    ABlock();
    virtual ~ABlock();

    bool setName(const TypeBlock &type);
    bool setName(const QString &name);
    TypeBlock name();
    virtual bool parser(const char *body,uint32_t size);
};

#endif // ABLOCK_H
