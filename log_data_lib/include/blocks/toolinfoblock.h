#ifndef TOOLINFOBLOCK_H
#define TOOLINFOBLOCK_H

#include "ablock.h"


class ToolInfoBlock : public ABlock{
    QByteArray m_toolInfo;
public:
    ToolInfoBlock();
    ~ToolInfoBlock(){}

    void setToolInfo(QByteArray byteArray){m_toolInfo = byteArray;}
    QByteArray toolInfo(){return m_toolInfo;}
};

#endif // TOOLINFOBLOCK_H
