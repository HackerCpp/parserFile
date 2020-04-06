#include "inc/tabs/tabgfm.h"

#include <QDebug>
#include <QDateTime>
#include <QFileDialog>
#include "gfmloader.h"
#include "gfmsaver.h"
#include "graphiceditor.h"
#include "interpreterpython.h"


TabGFM::TabGFM(QString path,QWidget *parent) : AbstractTab(parent){
    m_logData = ILogData::createLogData();
    ILoaderLogData * gfmLoader = new GFMLoader(path);
    m_logData->setLoader(gfmLoader);
    m_logData->load();
    if(!m_logData->isReady()){
        connect(m_logData,&ILogData::ready,this,&TabGFM::dataReady);
    }
    //IInterpreterLogData *interpreter = new InterpreterPython();
    //m_logData->setInterpreter(interpreter);
    //m_logData->openInterpreter();
    m_barHLayout = new QHBoxLayout();
    m_mainVerticalLayout = new QVBoxLayout();
    m_graphicEditor = nullptr;
    m_toolBar = new QWidget();
    m_comboBox = new QComboBox();
    m_comboBox->insertItem(0,"Время");
    m_comboBox->insertItem(1,"Глубина");
    m_comboBox->setMaximumSize(100,40);
    m_barHLayout->addWidget(m_comboBox);
    m_barHLayout->addStretch(100);
    m_toolBar->setLayout(m_barHLayout);
    //while(!m_gfm->isReady()){}
    //m_forms = new AbstractForms(m_gfm->zipForms(),m_gfm->curves());
    m_mainVerticalLayout->addWidget(m_toolBar);

    setLayout(m_mainVerticalLayout);
    connect(m_comboBox,static_cast<void(QComboBox::*)(int)>(&QComboBox::currentIndexChanged),this,&TabGFM::changeDrawType);
}
void TabGFM::changeDrawType(int index){
    if(!m_graphicEditor)
        return;
    if(index)
        m_graphicEditor->setDrawDepth();
    else
        m_graphicEditor->setDrawTime();
}

void TabGFM::dataReady(){
    //IInterpreterLogData *interpreter = new InterpreterPython();
    FormsBlock *forms = nullptr;
    QList<IBlock*> *blocks = m_logData->blocks();
    foreach(auto block,*blocks){
        if(block->name() == IBlock::FORMS_BLOCK){
            forms = dynamic_cast<FormsBlock*>(block);
            if(!forms){
                qDebug() << "Forms найдены, но динамически не переводятся";
            }
            break;
        }

    }
    m_graphicEditor = new GraphicEditor(m_logData->curves(),forms);
    m_mainVerticalLayout->addWidget(m_graphicEditor);
    m_comboBox->currentIndexChanged(m_comboBox->currentIndex());
    //m_logData->setInterpreter(interpreter);
    //m_logData->openInterpreter();
    ISaverLogData * gfmSaver = new GFMSaver();
    m_logData->setSaver(gfmSaver);
    m_logData->save();
}

void TabGFM::saveGFM(){
    QDateTime date;
    QString stringDate = date.currentDateTime().toString("dd_MM_yyyy_hh_mm");
    QString fileName = QFileDialog::getSaveFileName(nullptr,"Сохранить файл как",stringDate,"GFM(*.gfm)");
    //m_gfm->saveFile(fileName);
}

TabGFM::~TabGFM(){
    /*if(m_gfm){
        delete m_gfm;
        m_gfm = nullptr;
    }*/
}
