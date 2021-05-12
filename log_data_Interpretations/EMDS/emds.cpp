#include "emds.h"
#include "curve.h"
#include <QDateTime>

void EMDS::createEmdsBoard(QList<IBlock *> *blocks){
    m_formsBlock = nullptr;
    foreach(auto block,*blocks){
        if(block->name() == IBlock::FORMS_BLOCK){
            m_formsBlock = dynamic_cast<FormsBlock *>(block);
            if(m_formsBlock)
                break;
        }
    }
    if(!m_formsBlock){
        m_formsBlock = new FormsBlock();
        blocks->push_front(m_formsBlock);
    }
    m_formsBlock->boards()->clear();
    m_emdsBoard = new Board();
    m_formsBlock->boards()->push_back(m_emdsBoard);
    m_emdsBoard->setName("EMDS");
    int f_widthTreck = 100;
    for(int i = 0; i < 5;i++){
        Track *f_track = new Track();
        f_track->setNumber(i);
        f_track->setBegin(i * f_widthTreck);
        f_track->setWidth(f_widthTreck);
        f_track->setIsGreed(true);
        m_emdsBoard->setTrack(f_track);
    }
}

void EMDS::fillingTheBoard(QList<IBlock *> *blocks){
    m_blockChannels = nullptr;
    //Оставляем только блоки модуля ЕМДС
    foreach(auto block,*blocks){
        if(block->name() == IBlock::DATA_BLOCK){
            DataBlock *f_dataBlock = dynamic_cast<DataBlock *>(block);
            if(!f_dataBlock)
                continue;
            if(f_dataBlock->moduleMnemonic().indexOf("EMDS") == -1){
                blocks->removeOne(block);
            }
        }
    }
    //Находим блок с нужными кривыми
    foreach(auto block,*blocks){
        if(block->name() == IBlock::DATA_BLOCK){
            DataBlock *f_dataBlock = dynamic_cast<DataBlock *>(block);
            if(!f_dataBlock)
                continue;
            QList<ICurve*> *f_curves = f_dataBlock->curves();
            if(!f_curves || f_curves->isEmpty())
                continue;
            foreach(auto curve,*f_curves){
                if(curve->mnemonic().indexOf("A[") != -1 && curve->mnemonic().indexOf("(RAW)") == -1){
                    m_blockChannels = f_dataBlock;
                    break;
                }
            }
            if(m_blockChannels)
                break;
        }
    }
    if(!m_blockChannels)
        return;
    qDebug() << m_blockChannels->numberOfVectors();
    //Создаём спектр
    ICurve *f_curve = new Curve<double>(m_blockChannels->numberOfVectors(),34);
    Desc *f_desc = new Desc();
    f_curve->setDesc(f_desc);

    f_curve->desc()->setParam("draw_type","SPECTRUM");
    f_curve->desc()->setParam("data_step","100(HZ)");
    f_curve->desc()->setParam("data_begin","0(HZ)");
    f_curve->desc()->setParam("val_range","0..4000");
    f_curve->setRecordPoint(m_blockChannels->curves()->last()->recordPoint());
    ShortCut f_shortCut;
    f_shortCut.setName("MID");
    f_shortCut.setRef(m_blockChannels->shortCuts()->first().ref());
    f_curve->setShortCut(f_shortCut);
    f_curve->setTime(m_blockChannels->time());
    f_curve->setDepth(m_blockChannels->depth());
    f_curve->setMnemonic("MID");
    m_blockChannels->setcurve(f_curve);

    QList<ICurve*> *f_curves = m_blockChannels->curves();
    foreach(auto curve,*f_curves){
        AItem *f_itemInfo = ItemInfoCreater::CreateItemInfo(curve);
        if(!f_itemInfo)
            continue;
        f_itemInfo->setVisible(AItem::BOARD_GRAPH_VIEW,true);
        QString name = curve->shortCut().nameWithoutNumber() + ':' + curve->mnemonic();
        m_emdsBoard->setItem(name,f_itemInfo);
        if(curve->mnemonic().indexOf("A[") != -1 && curve->mnemonic().indexOf("(RAW)") == -1){
            int f_index =  curve->mnemonic().mid(curve->mnemonic().indexOf("[") + 1,curve->mnemonic().indexOf("]") - curve->mnemonic().indexOf("[") - 1).toInt();
            //m_channelsA->operator[](f_index) = curve;
            //m_channelsA->push_back(curve);
            m_channelsA->operator[](f_index - 1) = curve;
        }
    }
    for(int i = 0; i < f_curve->depth()->size();++i){
        for(int j = 0;j < m_channelsA->size(); ++j){
            f_curve->setData(m_channelsA->at(j)->data(i),j + (m_channelsA->size() * i));
        }
    }

    /*foreach(auto curve, *m_channelsA){
        if(dynamic_cast<ICurve*>(curve)){
            qDebug() << curve->mnemonic() << curve->data(10);
        }
    }*/
}



EMDS::EMDS()
{
}

EMDS::EMDS(ILogData *logData){
    m_channelsA = new QVector<ICurve *>(34);
    m_blockChannels = nullptr;

    m_logData = new LogData(*dynamic_cast<LogData *>(logData));
    m_logData->setName("EMDS");
    QList<IBlock *> *f_blocks = m_logData->blocks();
    if(!f_blocks || f_blocks->isEmpty())
        return;
    createEmdsBoard(f_blocks);
    fillingTheBoard(f_blocks);
    qDebug() << "end";
}
