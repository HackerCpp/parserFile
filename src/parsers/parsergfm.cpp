#include "inc/parsers/parsergfm.h"
#include <QMessageBox>
#include <QTextCodec>
#include <QDebug>

void ParserGFM::parserHeaderBlock(QByteArray *bodyBlock,BlockGFMData *data){
    data = new HeaderBlock();
    HeaderBlock * header = reinterpret_cast<HeaderBlock *>(data);
    int position = 0;
    int indexEndString = 0;
    do{
        indexEndString = bodyBlock->indexOf("\n",position);
        HeaderData info ={bodyBlock->mid(position,indexEndString - position + 2)};
        position += indexEndString - position + 2;
        //qDebug() << QTextCodec::codecForMib(1015)->toUnicode(info.dataString);
        header->data.push_back(info);
    }while (indexEndString != -1);
}
void ParserGFM::parserToolInfoBlock(QByteArray *bodyBlock,BlockGFMData *data){
    data = new ToolInfoBlock();
    ToolInfoBlock * header = reinterpret_cast<ToolInfoBlock *>(data);
    int position = 0;
    int indexEndString = 0;
    do{
        indexEndString = bodyBlock->indexOf("\n",position);
        ToolInfoData info ={bodyBlock->mid(position,indexEndString - position + 2)};
        position += indexEndString - position + 2;
        //qDebug() << QTextCodec::codecForMib(1015)->toUnicode(info.dataString);
        header->data.push_back(info);
    }while (indexEndString != -1);
}
void parserDataBlockHeader(QByteArray *header,int position,QList<DataBlockData> *data){
    int pos = position;
    DataBlockData dataBlock;
    int indexBeginOffset = header->indexOf("[",pos);
    if(indexBeginOffset == -1){
        qDebug() << "end of moduls";
        return;
    }
    int indexEndOffset = header->indexOf("]",pos);
    dataBlock.offset = QTextCodec::codecForMib(1015)->toUnicode(header->mid(indexBeginOffset+2,indexEndOffset - indexBeginOffset-2)).toUInt();
    pos = indexEndOffset + 2;
    int indexEndsize = header->indexOf("]",pos);
    dataBlock.size = QTextCodec::codecForMib(1015)->toUnicode(header->mid(indexEndOffset + 4,indexEndsize - indexEndOffset - 4)).toUInt();
    pos = indexEndsize + 2;
    int indexBeginParamMnemon = header->indexOf(":",pos);
    int indexEndParamMnemon =   header->indexOf(":",indexBeginParamMnemon+2);
    dataBlock.parameterMnemonics = header->mid(indexBeginParamMnemon+2,indexEndParamMnemon - indexBeginParamMnemon - 4);
    if(indexEndParamMnemon == -1)
        return;
    pos = indexEndParamMnemon + 2;
    int indexbeginRecordPoint = header->indexOf(":",pos);
    int indexEndDataType;
    if(indexbeginRecordPoint - indexEndParamMnemon > 40 || indexbeginRecordPoint == -1 ){
        indexEndDataType = header->indexOf("<",pos);
    }
    else {
        indexEndDataType = indexbeginRecordPoint;
        dataBlock.recordPoint = header->mid(indexbeginRecordPoint+4,header->indexOf("<",pos) - indexbeginRecordPoint - 6);
    }
    dataBlock.dataType = header->mid(indexEndParamMnemon+4,indexEndDataType - indexEndParamMnemon - 6);
    qDebug() << dataBlock.offset << dataBlock.size
             << QTextCodec::codecForMib(1015)->toUnicode(dataBlock.parameterMnemonics)
             << QTextCodec::codecForMib(1015)->toUnicode(dataBlock.dataType)
             << QTextCodec::codecForMib(1015)->toUnicode(dataBlock.recordPoint);
    pos = indexEndDataType + 2;
    parserDataBlockHeader(header,pos,data);
}
void ParserGFM::parserDataBlock(QByteArray *bodyBlock,BlockGFMData *data){
    data = new DataBlock();
    DataBlock *dataBlock = reinterpret_cast<DataBlock *>(data);
    QByteArray endHeader = "</PARAMETERS>",beginHeader = "<PARAMETERS";
    QTextCodec *codec1 = QTextCodec::codecForMib(1015);
    int beginHeaderIndex = bodyBlock->indexOf(codec1->fromUnicode(beginHeader).mid(4));
    int endHeaderIndex = bodyBlock->indexOf(codec1->fromUnicode(endHeader).mid(4));
    dataBlock->header = bodyBlock->mid(beginHeaderIndex-2,endHeaderIndex-beginHeaderIndex + endHeader.size()*2);
    dataBlock->numberOfVectors = *reinterpret_cast<uint*>(bodyBlock->mid(endHeaderIndex+endHeader.size()*2+2,4).data());
    QByteArray nameStartMark = "NAME=\"",moduleMnemEndMarc = "\"/>";
    int indexBeginName = dataBlock->header.indexOf(codec1->fromUnicode(nameStartMark).mid(4)) + sizeof(nameStartMark)*2 + 2;
    int indexEndName = dataBlock->header.indexOf(".",indexBeginName);
    dataBlock->nameRecord = dataBlock->header.mid(indexBeginName,indexEndName - indexBeginName);
    int indexEndmoduleMnem = dataBlock->header.indexOf(codec1->fromUnicode(moduleMnemEndMarc).mid(4),indexEndName);
    dataBlock->moduleMnemonics = dataBlock->header.mid(indexEndName+2,indexEndmoduleMnem - indexEndName - 4);

    dataBlock->data = new QList<DataBlockData>();
    parserDataBlockHeader(&dataBlock->header,indexEndmoduleMnem,dataBlock->data);
    //qDebug() << QTextCodec::codecForMib(1015)->toUnicode(dataBlock->moduleMnemonics);
}
void ParserGFM::parserUnknownBlock(QByteArray *bodyBlock,BlockGFMData *data){
    data = new UnknownBlock();
    UnknownBlock * header = reinterpret_cast<UnknownBlock *>(data);
    int position = 0;
    int indexEndString = 0;
    do{
        indexEndString = bodyBlock->indexOf("\n",position);
        UnknownData info ={bodyBlock->mid(position,indexEndString - position + 2)};
        position += indexEndString - position + 2;
        header->data.push_back(info);
    }while (indexEndString != -1);
}
ParserGFM::ParserGFM(FileReader *file){
    this->m_gfmBlocks = new QList<BlockGFM>;
    FindBlocks *blocks = new FindBlocks(file->getByteArray());
    delete file;
    file = nullptr;
    QList<BlockByte> *gfmBlocksList = blocks->getBlockListBytes();
    QString boom = blocks->getBom();
    if(gfmBlocksList->isEmpty())
        return;
    foreach(BlockByte value,*gfmBlocksList){
        BlockGFM block;
        block.boom = boom;
        block.name = value.nameBlock;
        if(block.name == "[HEADER]")
            parserHeaderBlock(&value.bodyBlock,block.data);
        else if(block.name == "[TOOL_INFO]")
            parserToolInfoBlock(&value.bodyBlock,block.data);
        else if(block.name == "[DATA_BLOCK]")
            parserDataBlock(&value.bodyBlock,block.data);
        else
            parserUnknownBlock(&value.bodyBlock,block.data);
        m_gfmBlocks->push_back(block);
    }

}



ParserGFM::~ParserGFM(){
    delete this->m_gfmBlocks;
    this->m_gfmBlocks = nullptr;
}
