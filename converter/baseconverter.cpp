#include "baseconverter.h"

BaseConverter::BaseConverter()
{
   m_vLayout = new QVBoxLayout;
   m_btnGroup = new QButtonGroup(this);


   setLayout(m_vLayout);

}

BaseConverter::~BaseConverter(){
    if(m_vLayout){delete m_vLayout; m_vLayout = nullptr;}
}

void BaseConverter::setFileName(QString fileName){
    m_fileName = fileName;
}

void BaseConverter::fillWithButtons(){
    foreach(auto btn,m_btnGroup->buttons()){
        m_vLayout->addWidget(btn);
    }
}
