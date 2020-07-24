#include "curveeditor.h"
#include "vspectritem.h"
#include "spectrreader.h"



CurveEditor::CurveEditor(AGraphicItem *graphicItem,QWidget *parent)
    :BaseSettingsWindow(parent), m_modelCurveEditor(nullptr),m_table(nullptr), m_curveReader(nullptr){
    m_splitter = new QSplitter();
    //m_table = new QTableView();
    //m_modelCurveEditor = new ModelCurveEditor(graphicItem);
    //m_table->setModel(m_modelCurveEditor);
    //m_splitter->addWidget(m_table);

    m_scroll->setWidget(m_splitter);
    setWindowTitle(graphicItem->itemInfo()->name());
    if(dynamic_cast<VSpectrItem *>(graphicItem)){
        m_curveReader = new SpectrReader(dynamic_cast<VSpectrItem *>(graphicItem));
        m_splitter->addWidget(m_curveReader);
    }
    setWindowFlags(windowFlags() & ~Qt::WindowStaysOnTopHint);
}

CurveEditor::~CurveEditor(){
    if(m_modelCurveEditor){delete m_modelCurveEditor;m_modelCurveEditor = nullptr;}
    if(m_curveReader){delete m_curveReader;m_curveReader = nullptr;}
    if(m_table){delete m_table;m_table = nullptr;}
    if(m_splitter){delete m_splitter;m_splitter = nullptr;}

}

void CurveEditor::apply(){
    if(m_curveReader)
        m_curveReader->apply();
    //if(m_modelCurveEditor)
        //m_modelCurveEditor->apply();
    //emit changeSettings();
}
