#ifndef TOOLINFOBLOCKGFM_H
#define TOOLINFOBLOCKGFM_H
#include "inc/abstractblockgfm.h"

class ToolInfoBlockGFM : public AbstractBlockGFM{
public:
    ToolInfoBlockGFM();
    void parser(QByteArray *bodyBlock);
    virtual QByteArray getForSave();
    ~ToolInfoBlockGFM();
};

#endif // TOOLINFOBLOCKGFM_H
