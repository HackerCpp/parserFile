#include "igraphiceditor.h"



AGraphicEditor::AGraphicEditor(QMap<QString,ICurve*> *curves,FormsBlock *forms)
    :m_curves(curves),m_forms(forms){

}

AGraphicEditor::~AGraphicEditor(){

}

