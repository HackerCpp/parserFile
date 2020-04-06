#include "unknownblock.h"
#include "QDebug"
UnknownBlock::UnknownBlock(){


}
void UnknownBlock::setUnknownBlock(QByteArray *unknowBlock)
{
    qDebug() << "4444444444444444444444444444444444444444444444";
    m_unknowBlock = unknowBlock;
    qDebug() << "55555555555555555555555555555555555555555555555555";
}
QByteArray UnknownBlock::unknownBlock()
{
    return *m_unknowBlock;
}
