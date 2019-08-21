#include "inc/parsers/parsertlm.h"
#include <QMessageBox>
#include <QTextCodec>
#include <QDebug>

void ParserTLM::findPackFFFE(QString TlmPackString,TlmPack *TlmPack){
    bool ok;
    if(!(TlmPack->state & 0x80)){
        TlmPack->dataPacket.time = (TlmPackString.mid(6,2)+TlmPackString.mid(4,2)+TlmPackString.mid(2,2) + TlmPackString.mid(0,2)).toUInt(&ok,16);
        TlmPackString.remove(0,8);
    }
    else
        TlmPack->dataPacket.time = 0;
    int index = static_cast<char>(TlmPackString.mid(0,2).toUInt(&ok,16)) - 0x41;
    TlmPack->dataPacket.dev_type = devTypeArray[index<10?index:8];
    index = static_cast<uchar>(TlmPackString.mid(2,2).toUInt(&ok,16));
    TlmPack->dataPacket.inf_type = infTypeArray[index<14?index:2];
    TlmPack->dataPacket.data = TlmPackString.mid(4);
}

void ParserTLM::findTlmPackFFFE(QString blockTlmString,BlockTlm* blockTlm){
    int position = 0;
    int size = blockTlmString.length() - 2;
    bool ok;
    TlmPack TlmPack;
    while(position < size){
        TlmPack.state = static_cast<uchar>(blockTlmString.mid(position,2).toUInt(&ok,16));
        TlmPack.length = static_cast<ushort>((blockTlmString.mid(position + 4,2)+blockTlmString.mid(position + 2,2)).toUInt(&ok,16));
        findPackFFFE(blockTlmString.mid(position + 6,TlmPack.length * 2),&TlmPack);
        blockTlm->TlmPackList.push_back(TlmPack);
        position+=(TlmPack.length * 2) + 6;
    }
}


ParserTLM::ParserTLM(QString hexTextTlmFile){
    this->tlmBlocks = new QList<BlockTlm>;
    FindBlocks *blocks = new FindBlocks(hexTextTlmFile);
    QList<Block> *tlmBlocksList = blocks->getBlockList();
    QString boom = blocks->getBom();
    if(tlmBlocksList->isEmpty())
        return;
    BlockTlm blockTlm;
    for(auto i = tlmBlocksList->begin(); i < tlmBlocksList->end();++i ){
        blockTlm.name = QByteArray::fromHex(i->nameBlock.toLocal8Bit());
        blockTlm.boom = boom;
        if(boom == "fffe")
            findTlmPackFFFE(i->bodyBlock,&blockTlm);
        else if(boom == "feff")
            QMessageBox::about(nullptr,"Warning", "Кодировка FEFF не реализована, пожалуйста обратитесь к разработчику");
        else
            QMessageBox::about(nullptr,"Warning", "Неизвестная кодировка файла.");
        this->tlmBlocks->push_back(blockTlm);
    }
    delete blocks;
    blocks = nullptr;
    tlmBlocksList = nullptr;
}
void ParserTLM::findPackFFFE(QByteArray TlmPackByteArray,TlmPack *TlmPack){
    bool ok;
    int pos = 0;
    if(!(TlmPack->state & 0x80)){
        TlmPack->dataPacketBytes.time = *reinterpret_cast<uint*>(TlmPackByteArray.mid(0,4).data());
        pos = 4;
    }
    else
        TlmPack->dataPacketBytes.time = 0;
    int index = *TlmPackByteArray.mid(pos,1) - 0x41;
    TlmPack->dataPacketBytes.dev_type = devTypeArray[index<10?index:8];
    index = *TlmPackByteArray.mid(pos+1,1);
    TlmPack->dataPacketBytes.inf_type = infTypeArray[index<14?index:2];
    TlmPack->dataPacketBytes.data = TlmPackByteArray.mid(pos+2);
}
void ParserTLM::findTlmPackFFFE(QByteArray blockTlmByteArray,BlockTlm* blockTlm){
    int position = 0;
    int size = blockTlmByteArray.length() - 2;
    bool ok;
    TlmPack TlmPack;
    while(position < size){
        TlmPack.state = *reinterpret_cast<uchar*>(blockTlmByteArray.mid(position,1).data());
        TlmPack.length = *reinterpret_cast<ushort*>(blockTlmByteArray.mid(position+1,2).data());
        findPackFFFE(blockTlmByteArray.mid(position + 3,TlmPack.length),&TlmPack);
        blockTlm->TlmPackList.push_back(TlmPack);
        position+=(TlmPack.length) + 3;
    }
}
ParserTLM::ParserTLM(QByteArray byteArrayTlmFile){
    this->tlmBlocks = new QList<BlockTlm>;
    FindBlocks *blocks = new FindBlocks(byteArrayTlmFile);
    QList<BlockByte> *tlmBlocksList = blocks->getBlockListBytes();
    QString boom = blocks->getBom();
    if(tlmBlocksList->isEmpty())
        return;
    BlockTlm blockTlm;
    for(auto i = tlmBlocksList->begin(); i < tlmBlocksList->end();++i ){
        blockTlm.name = i->nameBlock;
        blockTlm.boom = boom;
        if(boom == "fffe")
            findTlmPackFFFE(i->bodyBlock,&blockTlm);
        else if(boom == "feff")
            QMessageBox::about(nullptr,"Warning", "Кодировка FEFF не реализована, пожалуйста обратитесь к разработчику");
        else
            QMessageBox::about(nullptr,"Warning", "Неизвестная кодировка файла.");
        this->tlmBlocks->push_back(blockTlm);
        for(auto val = blockTlm.TlmPackList.begin();val < blockTlm.TlmPackList.end();val++);
    }
    delete blocks;
    blocks = nullptr;
    tlmBlocksList = nullptr;
}

QList<BlockTlm> *ParserTLM::getBlocks(){
    return this->tlmBlocks;
}

ParserTLM::~ParserTLM(){
    delete this->tlmBlocks;
    this->tlmBlocks = nullptr;
}
