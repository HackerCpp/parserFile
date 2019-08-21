#include "inc/parsers/findblocks.h"
#include <QDebug>
#include <QtEndian>
#include <QTextCodec>


void FindBlocks::findBlocksByteFFFE(QByteArray byteArrayFile,int position){
    bool ok;
    int indexBeginBlock = byteArrayFile.indexOf("[",position);
    int indexEndBlock = byteArrayFile.indexOf("]",position) + 1;
    if(indexBeginBlock == -1 || indexEndBlock == -1)
        return;
    int sizeNameBlock = *byteArrayFile.mid(indexBeginBlock - 2,2).data();
    if(sizeNameBlock != (indexEndBlock - indexBeginBlock + 1))
        findBlocksByteFFFE(byteArrayFile,indexEndBlock+1);
    else{
        BlockByte block;
        uint sizeDataBlock = *reinterpret_cast<uint*>(byteArrayFile.mid(indexEndBlock + 1,4).data());
        block.sizeNameBlock = sizeNameBlock;
        block.nameBlock = byteArrayFile.mid(indexBeginBlock,sizeNameBlock).toHex();
        block.nameBlock = QByteArray::fromHex(block.nameBlock.remove("00").toLocal8Bit());
        block.sizeBodyBlock = sizeDataBlock;
        if(sizeDataBlock > INT_MAX/2){
            block.bodyBlock = byteArrayFile.mid(indexEndBlock+9);
            this->blocksListByte->push_back(block);
            return;
        }
        else{
            block.bodyBlock = byteArrayFile.mid(indexEndBlock + 9,static_cast<int>(sizeDataBlock - 8));
        }
        this->blocksListByte->push_back(block);
        findBlocksByteFFFE(byteArrayFile,indexEndBlock + 9 + static_cast<int>(sizeDataBlock - 8));
    }
}
FindBlocks::FindBlocks(QByteArray byteArrayFile){
   this->bom = byteArrayFile.mid(0,2).toHex();
   this->blocksListByte = new QList<BlockByte>;
   if(this->bom == "fffe"){
        findBlocksByteFFFE(byteArrayFile,0);
        return;
    }
}

QList<BlockByte> *FindBlocks::getBlockListBytes(){
    return this->blocksListByte;
}
QString FindBlocks::getBom(){
    return this->bom;
}
FindBlocks::~FindBlocks(){
    if(this->blocksListByte){
        delete this->blocksListByte;
        this->blocksListByte = nullptr;
    }
}
