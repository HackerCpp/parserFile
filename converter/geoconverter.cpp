#include "geoconverter.h"
#include <QLibrary>
#include <QDebug>
#include <gtkthread.h>

GeoConverter::GeoConverter()
{
    m_rbtnGfm = new QRadioButton(tr("GFM"));
    m_btnGroup->addButton(m_rbtnGfm);

    fillWithButtons();
}

GeoConverter::~GeoConverter(){

}

void GeoConverter::convert(){
    if(m_rbtnGfm->isChecked()){
        m_gtkThread.convert_geo_to_gfm(m_fileName);
    }

}
