#include "gfmconverter.h"


GfmConverter::GfmConverter()
{

    m_rbtnLas = new QRadioButton(tr("Las"));
    m_rbtnLis = new QRadioButton(tr("Lis"));

    m_btnGroup->addButton(m_rbtnLas);
    m_btnGroup->addButton(m_rbtnLis);

    fillWithButtons();
}

GfmConverter::~GfmConverter(){

}

void GfmConverter::convert(){
    if(m_rbtnLis->isChecked()){
        m_gtkThread.convert_gfm_to_lis(m_fileName);
    }
    else if(m_rbtnLas->isChecked()){
        m_gtkThread.convert_gfm_to_las(m_fileName);
    }
}
