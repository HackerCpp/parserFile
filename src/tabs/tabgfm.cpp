#include "inc/tabs/tabgfm.h"
#include "inc/fileCreation/creategfm.h"
#include <QStyle>
#include <QDebug>



TabGFM::TabGFM(QString path,QWidget *parent) : AbstractTab(parent){
    //ParserGFM *pGfm = new ParserGFM(file);
    m_mainHLayout = new QHBoxLayout();
    m_splitter = new QSplitter;
    m_gfm = new GFM(path);
    //m_blocks = pGfm->getGFMBlocks();
    /*foreach(auto gfmBlock,*m_blocks){
        if(gfmBlock.name == "[DATA_BLOCK]"){
            DataBlock *dataBlock = reinterpret_cast<DataBlock *>(gfmBlock.data);
            qDebug() << dataBlock->moduleMnemonics;
            if(dataBlock->moduleMnemonics == "NOISE[30030372]"){
                DataBlockCurve *mainValue = &dataBlock->curves->first();
                QList<DataBlockCurve> *curves = dataBlock->curves;
                ModelGFM *model = new ModelGFM(mainValue,curves);
                this->m_modelGfMScene.push_back(model);
                //break;
            }
        }
    }*/
    /*foreach(auto gfmBlock,*blocks){
        if(gfmBlock.name == "[DATA_BLOCK]"){
            DataBlock *dataBlock = reinterpret_cast<DataBlock *>(gfmBlock.data);
            if(dataBlock->moduleMnemonics == "NOISE[30030373]"){
                DataBlockCurve *mainValue = &dataBlock->curves->operator[](1);
                QList<DataBlockCurve> *curves = dataBlock->curves;
                ModelGFM *model = new ModelGFM(mainValue,curves);
                this->m_modelGfMScene.push_back(model);
                //break;
            }
        }
    }*/
    this->setLayout(m_mainHLayout);
    m_mainHLayout->addWidget(m_splitter);
    for(int i = 0; i < m_modelGfMScene.size();++i){
        OGLGraphicsView * grView = new OGLGraphicsView(this);
        grView->setStyleSheet("background:white");
        grView->setScene(m_modelGfMScene.at(i));
        m_splitter->addWidget(grView);
        grView->setScene(m_modelGfMScene.at(i));
        m_modelGfMScene.at(i)->connectView();
        m_graphicsView.push_back(grView);
    }
}

void TabGFM::saveGFM(){
    CreateGFM gfmFile(m_blocks);
    gfmFile.create();
}
TabGFM::~TabGFM(){
    delete m_gfm;
    m_gfm = nullptr;
}
