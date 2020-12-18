#include "curveeditor.h"
#include "vspectritem.h"
#include "spectrreader.h"
#include "acousticsEditor/acousticsEditor.h"



CurveEditor::CurveEditor(AGraphicItem *graphicItem,QWidget *parent)
    :BaseSettingsWindow(parent), m_curveReader(nullptr){
    m_splitter = new QSplitter();
    m_scroll->setWidget(m_splitter);

    setWindowTitle(graphicItem->itemInfo()->name());

    if(dynamic_cast<VSpectrItem *>(graphicItem)){
        m_curveReader = new SpectrReader(dynamic_cast<VSpectrItem *>(graphicItem));
        m_splitter->addWidget(m_curveReader);
    }
    else if(dynamic_cast<VAcuItem *>(graphicItem)){
        //m_curveReader = new AcousticsEditor(dynamic_cast<VAcuItem *>(graphicItem));
        //m_splitter->addWidget(m_curveReader);
    }

    setWindowFlags(windowFlags() & ~Qt::WindowStaysOnTopHint);
}

CurveEditor::~CurveEditor(){
    if(m_curveReader){delete m_curveReader;m_curveReader = nullptr;}
    if(m_splitter){delete m_splitter;m_splitter = nullptr;}

}

void CurveEditor::apply(){
    if(m_curveReader)
        m_curveReader->apply();
}
