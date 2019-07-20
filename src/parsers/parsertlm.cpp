#include "inc/parsers/parsertlm.h"
#include <QMessageBox>

void findPuck(QString tlmPuck,Pucket *pucket,uchar state){
    bool ok;
    if(!(state & 0x80)){
        pucket->time = (tlmPuck.mid(6,2)+tlmPuck.mid(4,2)+tlmPuck.mid(2,2) + tlmPuck.mid(0,2)).toUInt(&ok,16);
        tlmPuck.remove(0,8);
    }
    else {
        pucket->time = 0;
    }
    pucket->dev_type = static_cast<char>(tlmPuck.mid(0,2).toUInt(&ok,16));
    pucket->inf_type = static_cast<uchar>(tlmPuck.mid(2,2).toUInt(&ok,16));
    pucket->data = tlmPuck.mid(4);
}

void findTlmPuck(QString dataBlock,int position,QList<TlmPuck> *tlmPuckList){
    int size = dataBlock.length() - 2;
    bool ok;
    while(size > 0){
        TlmPuck tlmPuck;
        tlmPuck.state = static_cast<uchar>(dataBlock.mid(position,2).toUInt(&ok,16));
        tlmPuck.length = static_cast<ushort>((dataBlock.mid(position + 4,2)+dataBlock.mid(position + 2,2)).toUInt(&ok,16));
        tlmPuck.data = dataBlock.mid(position + 6,tlmPuck.length * 2);
        tlmPuckList->push_back(tlmPuck);
        position+=(tlmPuck.length * 2) + 6;
        size -= (tlmPuck.length * 2) + 6;
    }
}

void findTlmBlock(QString file,int position,QList<TlmBlock> *tlmBlocksList){
    //QString mess = "Начало поиска пакета";
    //QMessageBox::about(nullptr,"Title", mess);
    bool ok;
    QString beginBlock = "5b00",endBlock = "5d00";
    int indexBeginBlock = file.indexOf(beginBlock,position);
    int indexEndBlock = file.indexOf(endBlock,position);
    if(indexBeginBlock == -1 || indexEndBlock == -1)
        return;
    int sizeNameBlock = (file.mid(indexBeginBlock - 2,2)+file.mid(indexBeginBlock - 4,2)).toInt(&ok,16);
    if(sizeNameBlock != (((indexEndBlock+ 4) - indexBeginBlock)/2)){
        findTlmBlock(file,indexEndBlock+1,tlmBlocksList);
    }
    else{
        TlmBlock tlmBlock;
        uint sizeDataBlock =(file.mid(indexEndBlock + 10,2)+file.mid(indexEndBlock + 8,2)+file.mid(indexEndBlock + 6,2) + file.mid(indexEndBlock + 4,2)).toUInt(&ok,16);
        tlmBlock.sizeNameBlock = sizeNameBlock;
        tlmBlock.nameBlock = file.mid(indexBeginBlock,sizeNameBlock * 2);
        tlmBlock.sizeBodyBlock = sizeDataBlock;
        if(sizeDataBlock > INT_MAX/2){
            tlmBlock.bodyBlock = file.mid(indexEndBlock + 20);
            tlmBlocksList->push_back(tlmBlock);
            return;
        }
        else{
            int sizeBodyBlock = static_cast<int>(sizeDataBlock*2);
            tlmBlock.bodyBlock = file.mid(indexEndBlock + 20,sizeBodyBlock - 16);
        }
        tlmBlocksList->push_back(tlmBlock);
        findTlmBlock(file,indexEndBlock + 9 + static_cast<int>(sizeDataBlock),tlmBlocksList);
    }
}


ParserTLM::ParserTLM(QString tlmFile):m_tlmFile(tlmFile){
    this->tlmBlocksList = new QList<TlmBlock>;
    findTlmBlock(m_tlmFile,0,this->tlmBlocksList);
    if(!tlmBlocksList->isEmpty()){
        for(auto i = tlmBlocksList->begin(); i < tlmBlocksList->end();++i ){
            i->tlmPuckList = new QList<TlmPuck>;
            findTlmPuck(i->bodyBlock,0,i->tlmPuckList);
            if(!i->tlmPuckList->isEmpty()){
                for(auto j = i->tlmPuckList->begin(); j < i->tlmPuckList->end();++j ){
                    findPuck(j->data,&j->dataPucket,j->state);
                }
            }
        }
    }
    uint64_t qu= 0;
    if(!tlmBlocksList->isEmpty()){
        for(auto i = tlmBlocksList->begin(); i < tlmBlocksList->end();++i ){
            qu  = 0;
            this->string += "<br/>" + i->nameBlock + "<br/>";
            if(!i->tlmPuckList->isEmpty()){
                for(auto tlmPuck = i->tlmPuckList->begin(); tlmPuck < i->tlmPuckList->end();++tlmPuck ){

                        this->string+="size = " + QString::number(tlmPuck->length)
                        +"time = " + QString::number(tlmPuck->dataPucket.time)
                        +"  dev_type = " + tlmPuck->dataPucket.dev_type
                        +"  inf_type = " + QString::number(tlmPuck->dataPucket.inf_type)
                        +"  data = " + tlmPuck->dataPucket.data + "<br>";
                    qu++;
                }
               this->string += "<br> Количество записей: " + QString::number(qu) + "<br>";
            }
        }
    }
}

QString ParserTLM::getHexString(){
    return this->string;
}
