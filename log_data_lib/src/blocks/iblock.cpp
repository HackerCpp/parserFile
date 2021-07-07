#include "iblock.h"
#include <QDebug>
#include "datablock.h"
#include "formsblock.h"
#include "headerblock.h"
#include "toolinfoblock.h"
#include "labelblock.h"

IBlock::IBlock(){}
IBlock::~IBlock(){}


IBlock::TypeBlock IBlock::name()const{
    return NO_BLOCK;
}

bool IBlock::parser(const char *body,uint32_t size){
    Q_UNUSED(body)
    Q_UNUSED(size)
    return false;
}

IBlock *IBlock::blockCreater(IBlock::TypeBlock type){
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
            f_block = new HeaderBlock();
            break;
        }
        case LABELS_BLOCK:{
            f_block = new LabelBlock();
            break;
        }
    }
    return f_block;
}

IBlock *IBlock::blockCreater(const IBlock &block){
    IBlock &f_block = const_cast<IBlock &>(block);
    IBlock *f_returnBlock = nullptr;
    TypeBlock f_type = f_block.name();
    switch (f_type){
        case NO_BLOCK:{
            break;
        }
        case DATA_BLOCK:{
            f_returnBlock = new DataBlock(dynamic_cast<DataBlock &>(f_block));
            break;
        }
        case FORMS_BLOCK:{
            f_returnBlock = new FormsBlock(dynamic_cast<FormsBlock &>(f_block));
            break;
        }
        case TOOLINFO_BLOCK:{
            f_returnBlock = new ToolInfoBlock(dynamic_cast<ToolInfoBlock &>(f_block));
            break;
        }
        case HEADER_BLOCK:{
            f_returnBlock = new HeaderBlock(dynamic_cast<HeaderBlock &>(f_block));
            break;
        }
        case LABELS_BLOCK:{
            f_returnBlock = new LabelBlock(dynamic_cast<LabelBlock &>(f_block));
            break;
        }
    }
    return f_returnBlock;
}
