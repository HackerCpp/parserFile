#include "inc/parsers/parsergfm.h"
#include <QMessageBox>
#include <QTextCodec>
#include <QDebug>

void ParserGFM::parserHeaderBlock(QByteArray *bodyBlock,BlockGFM *block){
    block->data = new HeaderBlock();
    HeaderBlock * header = reinterpret_cast<HeaderBlock *>(block->data);
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
void ParserGFM::parserToolInfoBlock(QByteArray *bodyBlock,BlockGFM *block){
    block->data = new ToolInfoBlock();
    ToolInfoBlock * header = reinterpret_cast<ToolInfoBlock *>(block->data);
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
void parserDataBlockHeader(QByteArray *header,int position,QList<DataBlockCurve> *data){
    int pos = position;
    DataBlockCurve dataBlock;
    int indexBeginOffset = header->indexOf("[",pos);
    if(indexBeginOffset == -1)
        return;
    int indexEndOffset = header->indexOf("]",pos);
    dataBlock.offset = QTextCodec::codecForMib(1015)->toUnicode(header->mid(indexBeginOffset+2,indexEndOffset - indexBeginOffset-2)).toUInt();
    pos = indexEndOffset + 2;
    int indexEndsize = header->indexOf("]",pos);
    dataBlock.size = QTextCodec::codecForMib(1015)->toUnicode(header->mid(indexEndOffset + 4,indexEndsize - indexEndOffset - 4)).toUInt();
    pos = indexEndsize + 2;
    int indexBeginParamMnemon = header->indexOf(":",pos);
    int indexEndParamMnemon =   header->indexOf(":",indexBeginParamMnemon+2);
    dataBlock.parameterMnemonics = QTextCodec::codecForMib(1015)->toUnicode(header->mid(indexBeginParamMnemon+2,indexEndParamMnemon - indexBeginParamMnemon - 4));
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
    dataBlock.dataType = QTextCodec::codecForMib(1015)->toUnicode(header->mid(indexEndParamMnemon+4,indexEndDataType - indexEndParamMnemon - 6));
    pos = indexEndDataType + 2;
    int indexEndMnem = header->indexOf("\n",indexEndDataType+4);
    int indexBeginMnem = header->indexOf("<",indexEndParamMnemon + 2);
    dataBlock.desc = header->mid(indexBeginMnem,indexEndMnem - indexBeginMnem - 2);
    pos = indexEndMnem + 2;
    data->push_back(dataBlock);
    parserDataBlockHeader(header,pos,data);
}

void dataToQreal(QList<DataBlockCurve>::iterator curve,DataBlock *dataBlock,QByteArray *bodyBlock,int indexBeginData){
    uint offset = curve->offset * dataBlock->numberOfVectors;
    uint dataSizeInBytes = dataBlock->numberOfVectors * curve->size;
    if(curve->dataType.indexOf("UINT8") != -1){
        curve->sizeofType = 1;
        uint dataSize = dataBlock->numberOfVectors*(curve->size/curve->sizeofType);
        QVector<uchar> *ptr = new QVector<uchar>(dataSize);
        memcpy(ptr->data(),bodyBlock->data() + indexBeginData + offset,dataSizeInBytes);
        curve->data = new QVector<qreal>(dataSize);
        for(uint i = 0; i < dataBlock->numberOfVectors;i++)
            curve->data->data()[i] = ptr->data()[i];
        delete ptr;
        ptr = nullptr;
    }
    else if(curve->dataType.indexOf("INT8") != -1){
        curve->sizeofType = 1;
        uint dataSize = dataBlock->numberOfVectors*(curve->size/curve->sizeofType);
        QVector<char> *ptr = new QVector<char>(dataSize);
        memcpy(ptr->data(),bodyBlock->data() + indexBeginData + offset,dataSizeInBytes);
        curve->data = new QVector<qreal>(dataSize);
        for(uint i = 0; i < dataBlock->numberOfVectors;i++)
            curve->data->data()[i] = ptr->data()[i];
        delete ptr;
        ptr = nullptr;
    }
    else if(curve->dataType.indexOf("UINT32") != -1){
        curve->sizeofType = 4;
        uint dataSize = dataBlock->numberOfVectors*(curve->size/curve->sizeofType);
        QVector<uint> *ptr = new QVector<uint>(dataSize);
        memcpy(ptr->data(),bodyBlock->data() + indexBeginData + offset,dataSizeInBytes);
        curve->data = new QVector<qreal>(dataSize);
        for(uint i = 0; i < dataBlock->numberOfVectors;i++)
            curve->data->data()[i] = ptr->data()[i];
        delete ptr;
        ptr = nullptr;
    }
    else if(curve->dataType.indexOf("INT32") != -1){
        curve->sizeofType = 4;
        uint dataSize = dataBlock->numberOfVectors*(curve->size/curve->sizeofType);
        QVector<int> *ptr = new QVector<int>(dataSize);
        memcpy(ptr->data(),bodyBlock->data() + indexBeginData + offset,dataSizeInBytes);
        curve->data = new QVector<qreal>(dataSize);
        for(uint i = 0; i < dataBlock->numberOfVectors;i++)
            curve->data->data()[i] = ptr->data()[i];
        delete ptr;
        ptr = nullptr;
    }
    else if(curve->dataType.indexOf("UINT16") != -1){
        curve->sizeofType = 2;
        uint dataSize = dataBlock->numberOfVectors*(curve->size/curve->sizeofType);
        QVector<ushort> *ptr = new QVector<ushort>(dataSize);
        memcpy(ptr->data(),bodyBlock->data() + indexBeginData + offset,dataSizeInBytes);
        curve->data = new QVector<qreal>(dataSize);
        for(uint i = 0; i < dataBlock->numberOfVectors;i++)
            curve->data->data()[i] = ptr->data()[i];
        delete ptr;
        ptr = nullptr;
    }
    else if(curve->dataType.indexOf("INT16") != -1){
        curve->sizeofType = 2;
        uint dataSize = dataBlock->numberOfVectors*(curve->size/curve->sizeofType);
        QVector<short> *ptr = new QVector<short>(dataSize);
        memcpy(ptr->data(),bodyBlock->data() + indexBeginData + offset,dataSizeInBytes);
        curve->data = new QVector<qreal>(dataSize);
        for(uint i = 0; i < dataBlock->numberOfVectors;i++)
            curve->data->data()[i] = ptr->data()[i];
        delete ptr;
        ptr = nullptr;
    }
    else if(curve->dataType.indexOf("FLOAT32") != -1){
        curve->sizeofType = 4;
        uint dataSize = dataBlock->numberOfVectors*(curve->size/curve->sizeofType);
        QVector<float> *ptr = new QVector<float>(dataSize);
        memcpy(ptr->data(),bodyBlock->data() + indexBeginData + offset,dataSizeInBytes);
        curve->data = new QVector<qreal>(dataSize);
        for(uint i = 0; i < dataSize;i++)
            curve->data->data()[i] = ptr->data()[i];
        delete ptr;
        ptr = nullptr;
    }
}
void ParserGFM::parserDataBlock(QByteArray *bodyBlock,BlockGFM *block){
    block->data = new DataBlock();
    DataBlock *dataBlock = reinterpret_cast<DataBlock *>(block->data);
    QByteArray endHeader = "</PARAMETERS>",beginHeader = "<PARAMETERS",
            beginPlugin = "<PLUGINS>", endPlugins = "</PLUGINS>";
    QTextCodec *codec1 = QTextCodec::codecForMib(1015);
    int beginHeaderIndex = bodyBlock->indexOf(codec1->fromUnicode(beginHeader).mid(4));
    int endHeaderIndex = bodyBlock->indexOf(codec1->fromUnicode(endHeader).mid(4));
    QByteArray header = bodyBlock->mid(beginHeaderIndex - 2,endHeaderIndex - beginHeaderIndex + endHeader.size() * 2);
    int beginPluginsIndex = bodyBlock->indexOf(codec1->fromUnicode(beginPlugin).mid(4),endHeaderIndex + endHeader.size() * 2);
    int endPluginsIndex = bodyBlock->indexOf(codec1->fromUnicode(endPlugins).mid(4), endHeaderIndex + endHeader.size() * 2);
    int indexBeginData = 0;
    if(beginPluginsIndex == -1){
        indexBeginData = endHeaderIndex+endHeader.size()*2+6;
        dataBlock->numberOfVectors = *reinterpret_cast<uint*>(bodyBlock->mid(endHeaderIndex+endHeader.size()*2+2,4).data());
    }
    else{
        indexBeginData = endPluginsIndex + endPlugins.size()*2+6; 
        dataBlock->plugins = codec1->toUnicode(bodyBlock->mid(beginPluginsIndex - 2,endPluginsIndex - beginPluginsIndex + endPlugins.size() * 2));
        dataBlock->numberOfVectors = *reinterpret_cast<uint*>(bodyBlock->mid(endPluginsIndex+endPlugins.size()*2+2,4).data());
    }
    QByteArray nameStartMark = "NAME=\"",moduleMnemEndMarc = "\"/>";
    int indexBeginName = header.indexOf(codec1->fromUnicode(nameStartMark).mid(4)) + sizeof(nameStartMark)*2 + 2;
    int indexEndName = header.indexOf(".",indexBeginName);
    dataBlock->nameRecord = codec1->toUnicode(header.mid(indexBeginName,indexEndName - indexBeginName));
    int indexEndmoduleMnem = header.indexOf(codec1->fromUnicode(moduleMnemEndMarc).mid(4),indexEndName);
    dataBlock->moduleMnemonics = codec1->toUnicode(header.mid(indexEndName+2,indexEndmoduleMnem - indexEndName - 4));
    dataBlock->curves = new QList<DataBlockCurve>();
    parserDataBlockHeader(&header,indexEndmoduleMnem,dataBlock->curves);

    for (auto curve = dataBlock->curves->begin();curve < dataBlock->curves->end();curve++){
        curve->data = nullptr;
        dataToQreal(curve,dataBlock,bodyBlock,indexBeginData);
    }
}
void ParserGFM::parserUnknownBlock(QByteArray *bodyBlock,BlockGFM *block){
    block->data = new UnknownBlock();
    UnknownBlock * header = reinterpret_cast<UnknownBlock *>(block->data);
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
        if(block.name == "[HEADER]"){
            parserHeaderBlock(&value.bodyBlock,&block);
        }
        else if(block.name == "[TOOL_INFO]")
            parserToolInfoBlock(&value.bodyBlock,&block);
        else if(block.name == "[DATA_BLOCK]"){
            parserDataBlock(&value.bodyBlock,&block);
        }
        else
            parserUnknownBlock(&value.bodyBlock,&block);
        m_gfmBlocks->push_back(block);

    }
    delete blocks;
    //delete gfmBlocksList;

}
QList<BlockGFM> *ParserGFM::getGFMBlocks(){
    return m_gfmBlocks?m_gfmBlocks:nullptr;
}
ParserGFM::~ParserGFM(){
    delete this->m_gfmBlocks;
    this->m_gfmBlocks = nullptr;
}
