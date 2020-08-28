#include "acousticsEditor/acousticsEditor.h"
#include <QDragEnterEvent>
#include "vlineItem.h"
//#include "pythoneditor.h"
//#include "interpreterpython.h"

AcousticsEditor::AcousticsEditor(VAcuItem *acuItem){
    m_dataCountingOriginal = new DataCountingAcoustics;
    m_dataCountingExperimental = new DataCountingAcoustics;

    //m_pythonInterpreter = new InterpreterPython();
    if(acuItem->curve()->mnemonic().indexOf("2") != -1){
        m_dataCountingOriginal->setAcuItemTwo(acuItem);
        m_dataCountingExperimental->setAcuItemTwo(new VAcuItem(*acuItem));
    }
    else{
        m_dataCountingOriginal->setAcuItemOne(acuItem);
        m_dataCountingExperimental->setAcuItemOne(new VAcuItem(*acuItem));
    }


    m_pyNameList << "acu1" << "acu2" << "t1" << "t2" << "delta_t"
                 << "a1_adcu" << "a2_adcu" << "a1_db" << "a2_db" << "alpha_db_m";
    for(int i = 0; i < DataCountingAcoustics::MAXIMUM; ++i){
        AGraphicItem *f_item = m_dataCountingExperimental->item((DataCountingAcoustics::AcuTypeItem)i);
        if(!f_item)
            continue;
        //m_pythonInterpreter->addObject(m_pyNameList[i],f_item->curve());
    }

    //m_pyEditor = new PythonEditor(m_pythonInterpreter);
    //m_pyEditor->setWindowFlags(Qt::Window | Qt::WindowMinimizeButtonHint | Qt::WindowMaximizeButtonHint | Qt::CustomizeWindowHint);
    //m_pyEditor->show();
    m_mainVLayout = QPointer<QVBoxLayout>(new QVBoxLayout);
    m_splitter = QPointer<QSplitter>(new QSplitter(Qt::Horizontal));
    m_setOfCurves = QPointer<SetOfCurves>(new SetOfCurves(m_dataCountingOriginal));
    m_displayAcoustics = QPointer<DisplayingAcoustics>(new DisplayingAcoustics(m_dataCountingExperimental));

    m_splitter->addWidget(m_setOfCurves);
    m_splitter->addWidget(m_displayAcoustics);

    m_panel = new QWidget(this);
    m_panelLayout = QPointer<QHBoxLayout>(new QHBoxLayout);
    m_btnCalculate = new QPushButton(tr("Calculate"),this);
    m_btnСancel = new QPushButton(tr("Cansel"),this);

    m_panelLayout->addStretch(100);
    m_panelLayout->addWidget(m_btnCalculate);
    m_panelLayout->addWidget(m_btnСancel);
    m_panelLayout->addStretch(100);

    m_panel->setLayout(m_panelLayout);

    m_mainVLayout->addWidget(m_panel);
    m_mainVLayout->addWidget(m_splitter);
    this->setLayout(m_mainVLayout);

    connect(m_btnCalculate,&QPushButton::released,this,&AcousticsEditor::calculate);
    connect(m_btnСancel,&QPushButton::released,this,&AcousticsEditor::cancelCalculate);
    connect(m_setOfCurves,&SetOfCurves::dataUpdated,this,&AcousticsEditor::dataChange);
}

AcousticsEditor::~AcousticsEditor(){
    if(m_dataCountingExperimental){
        QVector<AGraphicItem *>f_items = m_dataCountingExperimental->items();
        foreach(auto item,f_items){
            if(item){delete item;item = nullptr;}
        }
        delete m_dataCountingExperimental; m_dataCountingExperimental = nullptr;
    }
    if(m_dataCountingOriginal){delete m_dataCountingOriginal;m_dataCountingOriginal = nullptr;}
}

void copyCurve(ICurve *src, ICurve *dst){
    if(!src || !dst){
        qDebug() << "src Curve ||dst Curve = nullptr  copyCurve() acousticsEditor.cpp";
        return;
    }
    if(src->size() != dst->size()){
        qDebug() << "src->size() != dst->size() copyCurve() acousticsEditor.cpp";
        return;
    }
    for(uint i = 0;i < dst->size();++i){
        dst->setData(src->data(i),i);
    }
}

void AcousticsEditor::apply(){
    for(int i = 0; i < DataCountingAcoustics::MAXIMUM;++i){
        AGraphicItem *src_item = m_dataCountingExperimental->item((DataCountingAcoustics::AcuTypeItem)i);
        AGraphicItem *dst_item = m_dataCountingOriginal->item((DataCountingAcoustics::AcuTypeItem)i);
        if(!src_item || !dst_item)
            continue;
        copyCurve(src_item->curve(), dst_item->curve());
        dst_item->updateParam();
    }
}

void AcousticsEditor::updateDataPython(){
    for(int i = 0; i < DataCountingAcoustics::MAXIMUM;++i){
        AGraphicItem *f_item = m_dataCountingExperimental->item((DataCountingAcoustics::AcuTypeItem)i);
        if(!f_item)
            continue;
        //m_pythonInterpreter->addObject(m_pyNameList[i],f_item->curve());
    }
}

void AcousticsEditor::cancelCalculate(){
    for(int i = 0; i < DataCountingAcoustics::MAXIMUM;++i){
        AGraphicItem *dst_item = m_dataCountingExperimental->item((DataCountingAcoustics::AcuTypeItem)i);
        AGraphicItem *src_item  = m_dataCountingOriginal->item((DataCountingAcoustics::AcuTypeItem)i);
        if(!src_item || !dst_item)
            continue;
        copyCurve(src_item->curve(), dst_item->curve());
        dst_item->updateParam();
    }
}

void AcousticsEditor::calculate(){
    /*m_pythonInterpreter->addVariable("left_band_acu1",m_displayAcoustics->leftAndRightBandAcuOne().first);
    m_pythonInterpreter->addVariable("right_band_acu1",m_displayAcoustics->leftAndRightBandAcuOne().second);
    m_pythonInterpreter->addVariable("left_band_acu2",m_displayAcoustics->leftAndRightBandAcuTwo().first);
    m_pythonInterpreter->addVariable("right_band_acu2",m_displayAcoustics->leftAndRightBandAcuTwo().second);
    m_pythonInterpreter->addVariable("amp_acu1",m_displayAcoustics->ampAcuOne());
    m_pythonInterpreter->addVariable("amp_acu2",m_displayAcoustics->ampAcuTwo());
    m_pythonInterpreter->addVariable("base",m_setOfCurves->base());
    m_pythonInterpreter->executeScriptFromFile("scripts/acousticEditor/calcAcu.py");*/
    for(int i = 0; i < DataCountingAcoustics::MAXIMUM;++i){
        AGraphicItem *src_item = m_dataCountingExperimental->item((DataCountingAcoustics::AcuTypeItem)i);
        if(!src_item )
            continue;
        src_item->updateParam();
    }
}

void AcousticsEditor::dataChange(){
    for(int type = 0; type < DataCountingAcoustics::MAXIMUM; ++type){
        AGraphicItem *f_itemSrc = m_dataCountingOriginal->item(static_cast<DataCountingAcoustics::AcuTypeItem>(type));
        AGraphicItem *f_itemDst = m_dataCountingExperimental->item(static_cast<DataCountingAcoustics::AcuTypeItem>(type));
        if(!f_itemSrc)
            continue;
        if(f_itemDst){
            if(f_itemDst->curve()->mnemonic() == f_itemSrc->curve()->mnemonic())
                continue;
            else
                delete f_itemDst; f_itemDst = nullptr;
        }
        AGraphicItem *f_item = nullptr;
        if(dynamic_cast<VAcuItem*>(f_itemSrc))
            f_item = new VAcuItem(*dynamic_cast<VAcuItem*>(f_itemSrc));
        else if(dynamic_cast<VLineItem*>(f_itemSrc))
            f_item = new VLineItem(*dynamic_cast<VLineItem*>(f_itemSrc));
        if(f_item)
            f_item->updateParam(m_displayAcoustics->width());
        m_dataCountingExperimental->setItem(f_item,static_cast<DataCountingAcoustics::AcuTypeItem>(type));
        //m_pythonInterpreter->addObject(m_pyNameList[type],f_item->curve());
    }
}

