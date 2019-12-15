#include "gfm.h"
#include <QFile>
#include <QDataStream>
#include <QDebug>
#include "headerblockgfm.h"
#include "toolinfoblockgfm.h"
#include "unknownblockgfm.h"
#include "datablockgfm.h"
#include "formsblockgfm.h"
#include <QDateTime>

struct BlockByte{
    int sizeNameBlock;
    QString nameBlock;
    uint sizeBodyBlock;
    QByteArray bodyBlock;
};
void findBlocksByteFFFE(QByteArray byteArrayFile,QList<BlockByte> *blocksList,int position){
    int indexBeginBlock = byteArrayFile.indexOf("[",position);
    int indexEndBlock = byteArrayFile.indexOf("]",position) + 1;
    if(indexBeginBlock == -1 || indexEndBlock == -1)
        return;
    int sizeNameBlock = *byteArrayFile.mid(indexBeginBlock - 2,2).data();
    if(sizeNameBlock != (indexEndBlock - indexBeginBlock + 1))
        findBlocksByteFFFE(byteArrayFile,blocksList,indexEndBlock+1);
    else{
        BlockByte block;
        uint sizeDataBlock = *reinterpret_cast<uint*>(byteArrayFile.mid(indexEndBlock + 1, 4).data());
        block.sizeNameBlock = sizeNameBlock;
        block.nameBlock = byteArrayFile.mid(indexBeginBlock,sizeNameBlock).toHex();
        block.nameBlock = QByteArray::fromHex(block.nameBlock.remove("00").toLocal8Bit());
        block.sizeBodyBlock = sizeDataBlock;
        if(sizeDataBlock > INT_MAX/2){
            block.bodyBlock = byteArrayFile.mid(indexEndBlock+9);
            blocksList->push_back(block);
            return;
        }
        else{
            block.bodyBlock = byteArrayFile.mid(indexEndBlock + 9,static_cast<int>(sizeDataBlock - 8));
        }
        blocksList->push_back(block);
        findBlocksByteFFFE(byteArrayFile,blocksList,indexEndBlock + 9 + static_cast<int>(sizeDataBlock - 8));
    }
}

void GFM::run(){
    QTime time = QTime::currentTime();
    QFile file(m_path);
    file.open(QIODevice::ReadOnly);
    QByteArray byteArrayFile = file.readAll();
    file.close();
    this->m_bom = byteArrayFile.mid(0,2).toHex();
    QList<BlockByte> *blocksList = new QList<BlockByte>;
    if(this->m_bom == "fffe"){
         findBlocksByteFFFE(byteArrayFile,blocksList,0);
    }
    if(blocksList->isEmpty())
        return;
    foreach(BlockByte value,*blocksList){
        AbstractBlockGFM *block = nullptr;
        QString name = value.nameBlock;
        if(name == "[HEADER]")
            block = new HeaderBlockGFM;
        else if(name == "[TOOL_INFO]")
            block = new ToolInfoBlockGFM;
        else if(name == "[FORMS]")
            block = new FormsBlockGFM;
        else if(name == "[DATA_BLOCK]")
            block = new DataBlockGFM;
        else
            block = new UnknownBlockGFM;
        if(block == nullptr)
            continue;
        block->setName(name);
        block->parser(&value.bodyBlock);
        m_listBlocksGFM->push_back(block);
        value.bodyBlock.clear();
    }
    delete blocksList;
    byteArrayFile.clear();
    foreach(auto block,*m_listBlocksGFM){
        if(block->getName() == "[DATA_BLOCK]"){
           DataBlockGFM * dataBlock = dynamic_cast<DataBlockGFM *>(block);
           if(dataBlock){
               foreach(auto curve,*dataBlock->getCurves()){
                   if(!curve->getShortCut().getName().isEmpty()){
                       m_curves->push_back(curve);
                   }
               }
           }
        }
        else if(block->getName() == "[FORMS]"){
           FormsBlockGFM * formsBlock = dynamic_cast<FormsBlockGFM *>(block);
           if(formsBlock){
               while(!formsBlock->isReady()){}
           }
        }
    }
    qDebug() << time.msecsTo( QTime::currentTime() );
    m_isReady = true;
}
Forms *GFM::getForms(){
    foreach(auto block,*m_listBlocksGFM){
        if(block->getName() == "[FORMS]"){
            FormsBlockGFM * formsBlock = dynamic_cast<FormsBlockGFM *>(block);
            if(formsBlock)
                return formsBlock->forms();
            break;
        }
    }
    return nullptr;
}
QList<AbstractBlockGFM*> *GFM::getBlocks(){
    return m_listBlocksGFM;
}

QList<DataBlockGFM*> *GFM::getDataBlocks(){
    QList<DataBlockGFM*> *dataBlocks = new QList<DataBlockGFM*>;
    foreach(auto block,*m_listBlocksGFM){
        DataBlockGFM* dataBlock = dynamic_cast<DataBlockGFM*>(block);
        if(dataBlock)
            dataBlocks->push_back(dataBlock);
    }
    return dataBlocks;
}



GFM::GFM(QString path):m_path(path){
    m_isReady = false;
    m_listBlocksGFM = new QList<AbstractBlockGFM*>;
    m_curves = new QList<Curve*>;
    m_codec = QTextCodec::codecForMib(1015);
    start();
}

bool GFM::isReady(){
    return m_isReady;
}

void GFM::saveFile(QString fileName){
    QFile *fileGFM = new QFile(fileName);
    fileGFM->open(QIODevice::WriteOnly);// | QIODevice::Append);
    QTextStream striamFFFE(fileGFM);
    fileGFM->write(m_codec->fromUnicode("GFM"));
    fileGFM->write(m_codec->fromUnicode("\r\n").mid(2));
    foreach(AbstractBlockGFM *block,*m_listBlocksGFM){
        fileGFM->write(block->getForSave());
    }
    fileGFM->close();
    delete fileGFM;
    fileGFM = nullptr;
}
GFM::~GFM(){
    foreach(auto value,*m_listBlocksGFM){
        if(value){
            delete value;
            value = nullptr;
        }
    }
    delete m_listBlocksGFM;
    m_listBlocksGFM = nullptr;
}
