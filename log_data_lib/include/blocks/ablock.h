#ifndef ABLOCK_H
#define ABLOCK_H

#include "iblock.h"
#include <QDebug>
/*! \addtogroup block Описание блоков
 * @{
 */
class ABlock : public IBlock{
protected:
    TypeBlock m_type;
public:
    ABlock(){m_type = NO_BLOCK;}
    virtual ~ABlock(){}

    TypeBlock name()override{return m_type;}
    virtual bool parser(const char *body,uint32_t size)override{Q_UNUSED(body)Q_UNUSED(size)return false;}
};
/*! @} */
#endif // ABLOCK_H
