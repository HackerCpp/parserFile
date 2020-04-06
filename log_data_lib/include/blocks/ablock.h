#ifndef ABLOCK_H
#define ABLOCK_H

#include "iblock.h"

class ABlock : public IBlock{
protected:
    TypeBlock m_type;
    QString m_name;
public:
    ABlock();
    virtual ~ABlock();

    TypeBlock name();
    virtual bool parser(const char *body,uint32_t size);
    virtual void setName(QString name);
    virtual QString names();

};

#endif // ABLOCK_H
