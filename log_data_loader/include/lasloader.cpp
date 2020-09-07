#include "lasloader.h"
#include <QDebug>
#include <QTime>
#include <QFile>
#include <QTextCodec>
#include <datablock.h>
#include <curve.h>

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
        QByteArray f_bodyBlock = f_block.mid(f_block.indexOf("\n") + 1);
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

void LasLoader::parser20(const QList<BlockLas> &blocksLas){
    DataBlock *f_dataBlock = dynamic_cast<DataBlock *>(IBlock::blockCreater(IBlock::DATA_BLOCK));
    createCurves20(f_dataBlock,blocksLas);
    fillCurves20(f_dataBlock,blocksLas);
    f_dataBlock->setNumberOfVectors(f_dataBlock->curves()->first()->size());
    m_blocks->push_back(f_dataBlock);
}

void LasLoader::findCurve(ICurve *curve,const QString &curveLine){
    int f_indexEndMnemonic = curveLine.indexOf(" ",curveLine.indexOf("."));
    curve->setMnemonic(curveLine.mid(0,f_indexEndMnemonic).replace(" ","").replace(".","(") + ")");
}

void LasLoader::createCurves20(DataBlock *dataBlock,const QList<BlockLas> &blocksLas){
    ShortCut f_shortcut;
    QDateTime f_dateTime;
    f_shortcut.setRef("1");
    QString f_dt = f_dateTime.currentDateTime().toString("dd.MM.yyyy_hh:mm:ss.z").replace(":","-").replace(".","_");
    f_dt = f_dt.left(f_dt.size() - 4);
    f_shortcut.setName(f_dt + "." + "LAS[]");
    ShortCut f_timeDepth;
    f_timeDepth.setRef("");
    dataBlock->addShortCut(f_shortcut);
    if(!dataBlock)
        return;
    ICurve *f_depth,*f_time;
    f_depth = f_time = nullptr;
    foreach(auto blockLas,blocksLas){
        if(blockLas.typeBlockLas == C){
            QStringList resultStrings = QString(blockLas.bodyBlockLas).split('\n');

            foreach(auto string,resultStrings){
                if(string.mid(0,1) == "#" || string.isEmpty())
                    continue;
                ICurve * f_curve = new Curve<qreal>();
                Desc *f_desc = new Desc();
                f_curve->setDesc(f_desc);

                f_curve->setShortCut(dataBlock->shortCuts()->first());
                findCurve(f_curve,string);
                if(f_curve->mnemonic().indexOf("DEPT") != -1){
                    f_curve->desc()->setParam("draw_type","DEPTH");
                    f_curve->setShortCut(f_timeDepth);
                    f_depth = f_curve;
                }
                else if(f_curve->mnemonic() == "TIME"){
                    f_curve->desc()->setParam("draw_type","TIME");
                    f_curve->setShortCut(f_timeDepth);
                    f_time = f_curve;
                }
                else
                    f_curve->desc()->setParam("draw_type","LINE");
                dataBlock->setcurve(f_curve);
                dataBlock->setMainTime(f_time);
                dataBlock->setMainDepth(f_depth);
            }
        }
    }
    foreach(auto curve,*dataBlock->curves()){
        curve->setDepth(f_depth);
        curve->setTime(f_time);
    }

}

void LasLoader::fillCurves20(DataBlock *dataBlock,const QList<BlockLas> &blocksLas){
    QList<double> f_dataDouble;
    foreach(auto blockLas,blocksLas){
        if(blockLas.typeBlockLas == A){
            QString f_data = blockLas.bodyBlockLas.replace("\n"," ").replace("\r"," ");
            QStringList f_dataList = f_data.split(' ');
            bool ok = false;
            foreach(auto data,f_dataList){
                if(data.isEmpty())
                    continue;
                qreal number = data.toDouble(&ok);
                if(ok){
                   f_dataDouble.push_back(number);
                }
            }
        }
    }
    QList<ICurve *> *f_curves = dataBlock->curves();
    int f_curveSize = f_curves->size();
    for(int index = 0; index < f_dataDouble.size(); ++index){
        f_curves->operator[](index % f_curveSize)->setData(f_dataDouble.at(index));
    }
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
        parser20(*blocksList);
    else if(f_version.indexOf("1.2") != -1)
        parser20(*blocksList);

    qDebug() << "end load las : " << time.msecsTo( QTime::currentTime() ) << "mS";
    m_isReady = true;
    emit ready();

}





