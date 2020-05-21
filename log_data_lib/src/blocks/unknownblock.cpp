#include "unknownblock.h"
#include "QDebug"
UnknownBlock::UnknownBlock(){
    m_type = TypeBlock::NO_BLOCK;

}

void UnknownBlock::setUnknownBlock(QByteArray *unknowBlock)
{
    m_unknowBlock = unknowBlock;
}

QByteArray UnknownBlock::unknownBlock()
{
    return *m_unknowBlock;
}
