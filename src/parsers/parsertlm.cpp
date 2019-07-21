#include "inc/parsers/parsertlm.h"
#include <QMessageBox>
#include <QTextCodec>

void findPuckFFFE(QString tlmPuckString,TlmPuck *tlmPuck){
    bool ok;
    if(!(tlmPuck->state & 0x80)){
        tlmPuck->dataPucket.time = (tlmPuckString.mid(6,2)+tlmPuckString.mid(4,2)+tlmPuckString.mid(2,2) + tlmPuckString.mid(0,2)).toUInt(&ok,16);
        tlmPuckString.remove(0,8);
    }
    else
        tlmPuck->dataPucket.time = 0;
    tlmPuck->dataPucket.dev_type = static_cast<char>(tlmPuckString.mid(0,2).toUInt(&ok,16));
    tlmPuck->dataPucket.inf_type = static_cast<uchar>(tlmPuckString.mid(2,2).toUInt(&ok,16));
    tlmPuck->dataPucket.data = tlmPuckString.mid(4);
}

void findTlmPuckFFFE(QString blockTlmString,BlockTlm* blockTlm){
    int position = 0;
    int size = blockTlmString.length() - 2;
    bool ok;
    while(position < size){
        TlmPuck tlmPuck;
        tlmPuck.state = static_cast<uchar>(blockTlmString.mid(position,2).toUInt(&ok,16));
        tlmPuck.length = static_cast<ushort>((blockTlmString.mid(position + 4,2)+blockTlmString.mid(position + 2,2)).toUInt(&ok,16));
        findPuckFFFE(blockTlmString.mid(position + 6,tlmPuck.length * 2),&tlmPuck);
        blockTlm->tlmPuckList.push_back(tlmPuck);
        position+=(tlmPuck.length * 2) + 6;
    }
}


ParserTLM::ParserTLM(QString hexTextTlmFile){
    this->tlmBlocks = new QList<BlockTlm>;
    FindBlocks *blocks = new FindBlocks(hexTextTlmFile);
    QList<Block> *tlmBlocksList = blocks->getBlockList();
    QString boom = blocks->getBoom();
    if(tlmBlocksList->isEmpty())
        return;
    BlockTlm blockTlm;
    for(auto i = tlmBlocksList->begin(); i < tlmBlocksList->end();++i ){
        blockTlm.name = QByteArray::fromHex(i->nameBlock.toLocal8Bit());
        blockTlm.boom = boom;
        if(boom == "fffe")
            findTlmPuckFFFE(i->bodyBlock,&blockTlm);
        else if(boom == "feff")
            QMessageBox::about(nullptr,"Warning", "Кодировка FEFF не реализована, пожалуйста обратитесь к разработчику");
        else
            QMessageBox::about(nullptr,"Warning", "Неизвестная кодировка файла.");
        this->tlmBlocks->push_back(blockTlm);
    }
    delete blocks;
    blocks = nullptr;

    uint64_t qu= 0;

    if(!this->tlmBlocks->isEmpty()){
        for(auto tlmBlock = tlmBlocks->begin(); tlmBlock < tlmBlocks->end();++tlmBlock ){
            qu  = 0;
            this->string += tlmBlock->name + "<br>";
            if(!tlmBlock->tlmPuckList.isEmpty()){
                for(auto tlmPuck = tlmBlock->tlmPuckList.begin(); tlmPuck < tlmBlock->tlmPuckList.end();++tlmPuck ){
                    this->string+="size = " + QString::number(tlmPuck->length)
                        +"time = " + QString::number(tlmPuck->dataPucket.time)
                        +"  dev_type = " + tlmPuck->dataPucket.dev_type
                        +"  inf_type = " + QString::number(tlmPuck->dataPucket.inf_type)
                        +"  data = " + tlmPuck->dataPucket.data + "<br>";
                    qu++;
                }
             }
               this->string += "<br> Количество записей: " + QString::number(qu) + "<br>";
        }
    }
}

QString ParserTLM::getHexString(){
    return this->string;
}
QList<BlockTlm> *ParserTLM::getBlocks(){
    return this->tlmBlocks;
}
