#include "inc/parsers/parsertlm.h"
#include <QMessageBox>
#include <QTextCodec>
#include <QDebug>

void ParserTLM::findPuckFFFE(QString TlmPackString,TlmPack *TlmPack){
    bool ok;
    if(!(TlmPack->state & 0x80)){
        TlmPack->dataPucket.time = (TlmPackString.mid(6,2)+TlmPackString.mid(4,2)+TlmPackString.mid(2,2) + TlmPackString.mid(0,2)).toUInt(&ok,16);
        TlmPackString.remove(0,8);
    }
    else
        TlmPack->dataPucket.time = 0;
    int index = static_cast<char>(TlmPackString.mid(0,2).toUInt(&ok,16)) - 0x41;
    TlmPack->dataPucket.dev_type = devTypeArray[index<10?index:8];
    index = static_cast<uchar>(TlmPackString.mid(2,2).toUInt(&ok,16));
    TlmPack->dataPucket.inf_type = infTypeArray[index<14?index:2];
    TlmPack->dataPucket.data = TlmPackString.mid(4);
}

void ParserTLM::findTlmPackFFFE(QString blockTlmString,BlockTlm* blockTlm){
    int position = 0;
    int size = blockTlmString.length() - 2;
    bool ok;
    TlmPack TlmPack;
    while(position < size){
        TlmPack.state = static_cast<uchar>(blockTlmString.mid(position,2).toUInt(&ok,16));
        TlmPack.length = static_cast<ushort>((blockTlmString.mid(position + 4,2)+blockTlmString.mid(position + 2,2)).toUInt(&ok,16));
        findPuckFFFE(blockTlmString.mid(position + 6,TlmPack.length * 2),&TlmPack);
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

QList<BlockTlm> *ParserTLM::getBlocks(){
    return this->tlmBlocks;
}

ParserTLM::~ParserTLM(){
    delete this->tlmBlocks;
    this->tlmBlocks = nullptr;
}
