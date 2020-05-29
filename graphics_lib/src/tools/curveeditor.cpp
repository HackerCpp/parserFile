#include "curveeditor.h"


CurveEditor::CurveEditor(AGraphicItem *graphicItem){
    m_splitter = new QSplitter();
    m_table = new QTableView();
    m_modelCurveEditor = new ModelCurveEditor(graphicItem);
    m_table->setModel(m_modelCurveEditor);
    m_splitter->addWidget(m_table);

    m_scroll->setWidget(m_splitter);
    setWindowTitle(graphicItem->itemInfo()->name());
}

CurveEditor::~CurveEditor(){
    if(m_modelCurveEditor){delete m_modelCurveEditor;m_modelCurveEditor = nullptr;}
    if(m_table){delete m_table;m_table = nullptr;}
}

void CurveEditor::apply(){
    if(m_modelCurveEditor)
        m_modelCurveEditor->apply();
    emit changeSettings();
}
