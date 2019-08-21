#include "inc/parsers/findblocks.h"
#include <QDebug>
#include <QtEndian>
#include <QTextCodec>


void FindBlocks::findBlocksFFFE(QString hexTextFile,int position){
    bool ok;
    QString beginBlock = "5b00",endBlock = "5d00";
    int indexBeginBlock = hexTextFile.indexOf(beginBlock,position);
    int indexEndBlock = hexTextFile.indexOf(endBlock,position);
    if(indexBeginBlock == -1 || indexEndBlock == -1)
        return;
    int sizeNameBlock = (hexTextFile.mid(indexBeginBlock - 2,2)+hexTextFile.mid(indexBeginBlock - 4,2)).toInt(&ok,16);
    if(sizeNameBlock != (((indexEndBlock+ 4) - indexBeginBlock)/2))
        findBlocksFFFE(hexTextFile,indexEndBlock+1);
    else{
        Block block;
        uint sizeDataBlock =(hexTextFile.mid(indexEndBlock + 10,2)+hexTextFile.mid(indexEndBlock + 8,2)+hexTextFile.mid(indexEndBlock + 6,2) + hexTextFile.mid(indexEndBlock + 4,2)).toUInt(&ok,16);
        block.sizeNameBlock = sizeNameBlock;
        block.nameBlock = hexTextFile.mid(indexBeginBlock,sizeNameBlock * 2).remove("00");
        block.sizeBodyBlock = sizeDataBlock;
        if(sizeDataBlock > INT_MAX/2){
            block.bodyBlock = hexTextFile.mid(indexEndBlock + 20);
            this->blocksList->push_back(block);
            return;
        }
        else{
            int sizeBodyBlock = static_cast<int>(sizeDataBlock*2);
            block.bodyBlock = hexTextFile.mid(indexEndBlock + 20,sizeBodyBlock - 16);
        }
        this->blocksList->push_back(block);
        findBlocksFFFE(hexTextFile,indexEndBlock + 9 + static_cast<int>(sizeDataBlock));
    }
}
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
FindBlocks::FindBlocks(QString hexTextFile){
    this->bom = hexTextFile.mid(0,4);
    this->blocksList = new QList<Block>;
    this->blocksListByte = nullptr;
    if(this->bom == "fffe"){
        findBlocksFFFE(hexTextFile,0);
        return;
    }
    else if (this->bom == "feff")
        QMessageBox::about(nullptr,"Warning", "Поиск блоков с кодировкой FEFF не реализован, пожалуйста обратитесь к разработчику");
    else
        QMessageBox::about(nullptr,"Warning", "Неизвестная кодировка файла, пожалуйста обратитесь к разработчику");

    this->blocksList = nullptr;
}
FindBlocks::FindBlocks(QByteArray byteArrayFile){
   this->bom = byteArrayFile.mid(0,2).toHex();
   this->blocksList = nullptr;
   this->blocksListByte = new QList<BlockByte>;
   if(this->bom == "fffe"){
        findBlocksByteFFFE(byteArrayFile,0);
        return;
    }
}

QList<Block> *FindBlocks::getBlockList(){
    return this->blocksList;
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
    if(this->blocksList){
        delete this->blocksList;
        this->blocksList = nullptr;
    }
}
