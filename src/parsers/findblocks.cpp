#include "inc/parsers/findblocks.h"



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
        block.nameBlock = hexTextFile.mid(indexBeginBlock,sizeNameBlock * 2);
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
FindBlocks::FindBlocks(QString hexTextFile){
    this->bom = hexTextFile.mid(0,4);
    this->blocksList = new QList<Block>;
    if(this->bom == "fffe"){
        findBlocksFFFE(hexTextFile,0);
        return;
    }
    else if (this->bom == "feff")
        QMessageBox::about(nullptr,"Warning", "Поиск блоков с кодировкой FEFF не реализован, пожалуйста обратитесь к разработчику");
    else {
        QMessageBox::about(nullptr,"Warning", "Неизвестная кодировка файла, пожалуйста обратитесь к разработчику");
    }
    this->blocksList = nullptr;
}
QList<Block> *FindBlocks::getBlockList(){
    return this->blocksList;
}
QString FindBlocks::getBoom(){
    return this->bom;
}
