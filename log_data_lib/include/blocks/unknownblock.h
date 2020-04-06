#ifndef UNKNOWNBLOCK_H
#define UNKNOWNBLOCK_H

#include "ablock.h"

class UnknownBlock : public ABlock
{
    QByteArray *m_unknowBlock;
public:
    UnknownBlock();
    void setUnknownBlock(QByteArray *unknowBlock);
    QByteArray unknownBlock();
};

#endif // UNKNOWNBLOCK_H
