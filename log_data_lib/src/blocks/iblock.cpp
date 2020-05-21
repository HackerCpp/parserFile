#include "iblock.h"
#include <QDebug>
#include "datablock.h"
#include "formsblock.h"
#include "headerblock.h"
#include "toolinfoblock.h"

IBlock::IBlock(){}
IBlock::~IBlock(){}


IBlock::TypeBlock IBlock::name(){
    return NO_BLOCK;
}

bool IBlock::parser(const char *body,uint32_t size){
    return false;
}

QSharedPointer<IBlock>IBlock::blockCreater(IBlock::TypeBlock type){
    IBlock *f_block = nullptr;
    switch (type) {
        case NO_BLOCK:{
            break;
        }
        case DATA_BLOCK:{
            f_block = new DataBlock();
            break;
        }
        case FORMS_BLOCK:{
            f_block = new FormsBlock();
            break;
        }
        case TOOLINFO_BLOCK:{
            f_block = new ToolInfoBlock();
            break;
        }
        case HEADER_BLOCK:{
            f_block = new HearedBlock();
            break;
        }
    }
    return QSharedPointer<IBlock>(dynamic_cast<IBlock *>(f_block));
}
