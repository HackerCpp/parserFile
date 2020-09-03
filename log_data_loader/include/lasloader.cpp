#include "lasloader.h"
#include <QDebug>
#include <QTime>
#include <QFile>
#include <QTextCodec>
#include <datablock.h>

LasLoader::LasLoader(QString path)
    : m_path(path){
    m_codec = QTextCodec::codecForName("UTF-8");
    m_hashTypes.insert("~V",V);
    m_hashTypes.insert("~W",W);
    m_hashTypes.insert("~C",C);
    m_hashTypes.insert("~P",P);
    m_hashTypes.insert("~O",O);
    m_hashTypes.insert("~A",A);
}

LasLoader::~LasLoader(){

}

bool LasLoader::download(){
    start();
    return true;
}

void LasLoader::findBlocks(const QByteArray &data,QList<BlockLas> *blocksLas){
    QString f_beginBlock = "~";
    int f_indexEndBlock = 0;
    bool f_isEnd = false;
    while(!f_isEnd){
        int f_indexBeginBlock = data.indexOf(f_beginBlock,f_indexEndBlock);
        if(f_indexBeginBlock == -1)
            return;

        f_indexEndBlock = data.indexOf(f_beginBlock,f_indexBeginBlock + 2);
        QByteArray f_block;
        if(f_indexEndBlock == -1){
            f_block = data.mid(f_indexBeginBlock);
            f_isEnd = true;
        }
        else{
            f_block = data.mid(f_indexBeginBlock,f_indexEndBlock - f_indexBeginBlock);
            QString f_typeBlock = f_block.mid(0,2);
        }
        QString f_typeBlock = f_block.mid(0,2);
        QByteArray f_bodyBlock = f_block.mid(f_block.indexOf("\n") + 2);
        blocksLas->push_back(BlockLas{m_hashTypes.value(f_typeBlock),f_bodyBlock});
    };

}

QString LasLoader::version(QList<BlockLas> *blocksLas){
    QByteArray *f_blockVersion;
    foreach(auto blockLas, *blocksLas){
        if(blockLas.typeBlockLas == V){
            f_blockVersion = &blockLas.bodyBlockLas;
            break;
        }
    }
    int f_indexBeginVersion = f_blockVersion->indexOf("VERS.") + 5;
    int f_indexEndVersion = f_blockVersion->indexOf(":",f_indexBeginVersion);
    QString f_version = f_blockVersion->mid(f_indexBeginVersion,f_indexEndVersion - f_indexBeginVersion).replace(" ","");
    return f_version;
}

void LasLoader::parser20(QList<BlockLas> *blocksLas){
    createCurves20(blocksLas);
}

void LasLoader::createCurves20(QList<BlockLas> *blocksLas){
    IBlock *f_block = IBlock::blockCreater(IBlock::DATA_BLOCK);



    m_blocks->push_back(f_block);
}

void LasLoader::run(){
    m_isReady = false;
    QTime time = QTime::currentTime();
    qDebug() << "begin load las";
    QFile file(m_path);
    file.open(QIODevice::ReadOnly);
    QByteArray byteArrayFile = file.readAll();
    file.close();
    QList<BlockLas> *blocksList = new QList<BlockLas>;
    findBlocks(byteArrayFile,blocksList);
    byteArrayFile.resize(0);
    QString f_version = version(blocksList);
    if(f_version == "2.0")
        parser20(blocksList);

}





