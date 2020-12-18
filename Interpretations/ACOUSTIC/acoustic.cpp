#include "acoustic.h"
#include "curve.h"
#include <QDateTime>

ACOUSTIC::ACOUSTIC(){

}

ACOUSTIC::ACOUSTIC(ILogData *logData){
    m_blockAcu = nullptr;
    m_recordPoint = 0;

    m_mnemonics.insert("T1(mkSec)",2);
    m_mnemonics.insert("T2(mkSec)",2);
    m_mnemonics.insert("DT(mkSec)",2);

    m_mnemonics.insert("A1(ADCU)",3);
    m_mnemonics.insert("A2(ADCU)",3);
    m_mnemonics.insert("A1(DB)",4);
    m_mnemonics.insert("A2(DB)",4);
    m_mnemonics.insert("Alpha(DB/M)",5);

    m_logData = new LogData(*dynamic_cast<LogData *>(logData));
    m_logData->setName("Acoustic template");
    QList<IBlock *> *f_blocks = m_logData->blocks();
    if(!f_blocks || f_blocks->isEmpty())
        return;
    createAcuBoard(f_blocks);
    fillingTheBoard(f_blocks);
    qDebug() << "end";
}



void ACOUSTIC::createAcuBoard(QList<IBlock *> *blocks){
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

    //m_formsBlock->boards()->clear();
    m_acuBoard = new Board();
    m_formsBlock->boards()->push_back(m_acuBoard);
    m_acuBoard->setName("Acoustic");
    m_formsBlock->setActiveName(m_acuBoard->name());
    int f_widthTreck = 40;
    for(int i = 0; i < 6;i++){
        Track *f_track = new Track();
        f_track->setNumber(i);
        f_track->setBegin(i * f_widthTreck);
        f_track->setWidth(f_widthTreck);
        f_track->setIsGreed(true);
        m_acuBoard->setTrack(f_track);
    }
}


void ACOUSTIC::fillingTheBoard(QList<IBlock *> *blocks){
    m_blockAcu = nullptr;
    //Находим блок с акустикой
    foreach(auto block,*blocks){
        if(block->name() == IBlock::DATA_BLOCK){
            DataBlock *f_dataBlock = dynamic_cast<DataBlock *>(block);
            if(!f_dataBlock)
                continue;
            QList<ICurve*> *f_curves = f_dataBlock->curves();
            if(!f_curves || f_curves->isEmpty())
                continue;
            foreach(auto curve,*f_curves){
                if(curve->desc()->param("draw_type") == "ACOUSTIC"){
                    m_recordPoint = curve->recordPoint();
                    m_blockAcu = f_dataBlock;
                    break;
                }
            }
            if(m_blockAcu)
                break;
        }
    }

    if(!m_blockAcu)
        return;
//Создаём кривые
    foreach(auto mnemonic, m_mnemonics.keys()){
        ICurve *f_curve = new Curve<double>(m_blockAcu->numberOfVectors(),1);
        Desc *f_desc = new Desc();
        f_curve->setDesc(f_desc);
        f_curve->desc()->setParam("draw_type","LINE");
        f_curve->setRecordPoint(m_recordPoint);
        f_curve->setShortCut(m_blockAcu->shortCuts()->first());

        f_curve->setTime(m_blockAcu->time());
        f_curve->setDepth(m_blockAcu->depth());

        f_curve->setMnemonic(mnemonic);
        m_blockAcu->setcurve(f_curve);
    }
//Создаём графическое представление и распределяем между треками
    QList<ICurve*> *f_curves = m_blockAcu->curves();
    foreach(auto curve,*f_curves){
        AItem *f_itemInfo = ItemInfoCreater::CreateItemInfo(curve);
        if(!f_itemInfo)
            continue;
        f_itemInfo->setNumberOfTrack(m_mnemonics.value(curve->mnemonic(),0));
        if(!f_itemInfo->numberOfTrack()){
            if(curve->mnemonic().indexOf("2") != -1 && f_itemInfo->type() == ACU)
                f_itemInfo->setNumberOfTrack(1);
        }
        if(f_itemInfo->type() == ACU){
            f_itemInfo->setBegin(true,0,0);
            f_itemInfo->setEnd(true,300,10);
        }
        if(curve->mnemonic().indexOf("T") != -1){
            f_itemInfo->setBegin(true,0,0);
            f_itemInfo->setEnd(true,250,10);
        }
        else if(curve->mnemonic().indexOf("(ADCU)") != -1){
            f_itemInfo->setBegin(true,0,0);
            f_itemInfo->setEnd(true,7000,100);
        }
        else if(curve->mnemonic().indexOf("DB") != -1){
            f_itemInfo->setBegin(true,0,0);
            f_itemInfo->setEnd(true,30,10);
        }
        f_itemInfo->setVisible(AItem::BOARD_GRAPH_VIEW,(m_mnemonics.value(curve->mnemonic(),-1) != -1 || f_itemInfo->type() == ACU));
        QString name = curve->shortCut().nameWithoutNumber() + ':' + curve->mnemonic();
        m_acuBoard->setItem(name,f_itemInfo);
    }

}
