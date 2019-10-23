#include "inc/parsers/parsertlm.h"
#include <QMessageBox>
#include <QTextCodec>
#include <QDebug>




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
