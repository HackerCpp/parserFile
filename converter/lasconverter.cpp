#include "lasconverter.h"
#include "gtkthread.h"

LasConverter::LasConverter()
{
    m_rbtnGfm = new QRadioButton(tr("GFM"));
    m_btnGroup->addButton(m_rbtnGfm);

    fillWithButtons();
}

LasConverter::~LasConverter(){

}

void LasConverter::convert(){
    if(m_rbtnGfm->isChecked()){
        m_gtkThread.convert_las_to_gfm(m_fileName);
    }
}
