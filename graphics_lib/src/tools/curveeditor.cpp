#include "curveeditor.h"


CurveEditor::CurveEditor(AGraphicItem *graphicItem)
{
    m_splitter = new QSplitter();
    m_graphicsEditor = new SFMLItemEditor(nullptr,QPoint(0,0),QSize(100,100));
    m_graphicsEditor->setGraphicItem(graphicItem);
    m_table = new QTableView();
    m_scrollSFML = new QScrollArea;
    //m_scrollSFML->setWidget(m_graphicsEditor);
    m_modelCurveEditor = new ModelCurveEditor(graphicItem);
    m_table->setModel(m_modelCurveEditor);
    m_splitter->addWidget(m_scrollSFML);
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
