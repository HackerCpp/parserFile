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
        //QString str = info.dataString.toHex();
        //qDebug() << QTextCodec::codecForName("Windows-1251")->toUnicode(QByteArray::fromHex(str.remove("00").toLocal8Bit()));
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
        //QString str = info.dataString.toHex();
        //qDebug() << QTextCodec::codecForName("Windows-1251")->toUnicode(QByteArray::fromHex(str.remove("00").toLocal8Bit()));
        header->data.push_back(info);
    }while (indexEndString != -1);
}
void ParserGFM::parserDataBlock(QByteArray *bodyBlock,BlockGFMData *data){
    uint headerSize = bodyBlock->indexOf("< / ");
    //QString str = bodyBlock->mid(0,5000).toHex();
    qDebug() << QString::number(headerSize);
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
        //QString str = info.dataString.toHex();
        //qDebug() << QTextCodec::codecForName("Windows-1251")->toUnicode(QByteArray::fromHex(str.remove("00").toLocal8Bit()));
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
