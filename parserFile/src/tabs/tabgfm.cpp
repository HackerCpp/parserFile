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

    m_comboFormatTime.insertItem(0,"0.1 сек/см");
    m_comboFormatTime.insertItem(1,"1 сек/см");
    m_comboFormatTime.insertItem(2,"5 сек/см");
    m_comboFormatTime.insertItem(3,"10 сек/см");
    m_comboFormatTime.insertItem(4,"30 сек/см");
    m_comboFormatTime.insertItem(5,"1 мин/см");
    m_comboFormatTime.insertItem(6,"5 мин/см");
    m_comboFormatTime.insertItem(7,"10 мин/см");
    m_comboFormatTime.insertItem(8,"30 мин/см");
    m_comboFormatDepth.insertItem(0,"1:10");
    m_comboFormatDepth.insertItem(1,"1:50");
    m_comboFormatDepth.insertItem(2,"1:100");
    m_comboFormatDepth.insertItem(3,"1:200");
    m_comboFormatDepth.insertItem(4,"1:500");
    m_comboFormatDepth.insertItem(5,"1:1000");
    m_comboFormatDepth.insertItem(6,"1:2000");
    m_comboFormatDepth.insertItem(7,"1:5000");
    m_comboFormatDepth.insertItem(8,"1:10000");
    m_comboPictureLength.insertItem(0,"MIN Picture");
    m_comboPictureLength.insertItem(1,"AVR Picture");
    m_comboPictureLength.insertItem(2,"MAX Picture");
    m_comboPictureFormat.insertItem(0,"Format_RGB16");
    m_comboPictureFormat.insertItem(1,"Format_RGB32");
    m_comboPictureFormat.insertItem(2,"Format_Mono");
    m_comboPictureFormat.insertItem(3,"Format_ARGB4444_Premultiplied");
    m_comboPictureFormat.insertItem(4,"Format_RGBA64");
    m_comboPictureFormat.insertItem(5,"Format_Grayscale8");
    m_comboPictureFormat.insertItem(6,"Format_Grayscale16");



    m_comboBox.insertItem(0,"Время");
    m_comboBox.insertItem(1,"Глубина");
    m_barHLayout->addWidget(&m_comboBox);
    m_barHLayout->addWidget(&m_comboFormatTime);
    m_barHLayout->addWidget(&m_comboFormatDepth);
    m_barHLayout->addWidget(&m_comboPictureLength);
    m_barHLayout->addWidget(&m_comboPictureFormat);
    m_barHLayout->addStretch(100);
    m_toolBar->setLayout(m_barHLayout);

    m_mainVerticalLayout->addWidget(m_toolBar);

    setLayout(m_mainVerticalLayout);
    connect(&m_comboBox,static_cast<void(QComboBox::*)(int)>(&QComboBox::currentIndexChanged),this,&TabGFM::changeDrawType);
    connect(&m_comboFormatTime,static_cast<void(QComboBox::*)(int)>(&QComboBox::currentIndexChanged),this,&TabGFM::changeFormatTime);
    connect(&m_comboFormatDepth,static_cast<void(QComboBox::*)(int)>(&QComboBox::currentIndexChanged),this,&TabGFM::changeFormatDepth);
    connect(&m_comboPictureLength,static_cast<void(QComboBox::*)(int)>(&QComboBox::currentIndexChanged),this,&TabGFM::changePictureHeight);
    connect(&m_comboPictureFormat,static_cast<void(QComboBox::*)(int)>(&QComboBox::currentIndexChanged),this,&TabGFM::changePictureFormat);
}
void TabGFM::changeDrawType(int index){
    if(!m_graphicEditor)
        return;
    if(index){
        m_graphicEditor->setDrawDepth();
        m_comboFormatTime.hide();
        m_comboFormatDepth.show();
    }
    else{
        m_graphicEditor->setDrawTime();
        m_comboFormatTime.show();
        m_comboFormatDepth.hide();
    }
}

void TabGFM::changeFormatTime(int index){
    if(!m_graphicEditor)
        return;
    AGraphicBoard::FormatTime f_format = static_cast<AGraphicBoard::FormatTime>(index);
    m_graphicEditor->setFormatTime(f_format);
}

void TabGFM::changeFormatDepth(int index){
    if(!m_graphicEditor)
        return;
    AGraphicBoard::FormatDepth f_format = static_cast<AGraphicBoard::FormatDepth>(index);
    m_graphicEditor->setFormatDepth(f_format);
}

void TabGFM::changePictureHeight(int index){
    if(!m_graphicEditor)
        return;
    AGraphicBoard::LengthPicture f_format = static_cast<AGraphicBoard::LengthPicture>(index);
    m_graphicEditor->setLengthPicture(f_format);
}

void TabGFM::changePictureFormat(int index){
    if(!m_graphicEditor)
        return;
    QImage::Format f_format;
    switch (index){
    case 0:{
        f_format = QImage::Format_RGB16;
        break;
    }
    case 1:{
        f_format = QImage::Format_RGB32;
        break;
    }
    case 2:{
        f_format = QImage::Format_Mono;
        break;
    }
    case 3:{
        f_format = QImage::Format_ARGB4444_Premultiplied;
        break;
    }
    case 4:{
        f_format = QImage::Format_RGBA64;
        break;
    }
    case 5:{
        f_format = QImage::Format_Grayscale8;
        break;
    }
    case 6:{
        f_format = QImage::Format_Grayscale16;
        break;
    }

    }
    m_graphicEditor->setFormatPicture(f_format);
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
    m_comboBox.currentIndexChanged(m_comboBox.currentIndex());
    if(!m_comboBox.currentIndex()){
        m_comboFormatTime.show();
        m_comboFormatDepth.hide();
    }
    else{
        m_comboFormatTime.hide();
        m_comboFormatDepth.show();
    }
    //m_logData->setInterpreter(interpreter);
    //m_logData->openInterpreter();
}

void TabGFM::saveGFM(){

    ISaverLogData * gfmSaver = new GFMSaver();
    m_logData->setSaver(gfmSaver);
    m_logData->save();
    //m_gfm->saveFile(fileName);
}

TabGFM::~TabGFM(){
    /*if(m_gfm){
        delete m_gfm;
        m_gfm = nullptr;
    }*/
}
