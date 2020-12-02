#include "converter.h"
#include "gfmconverter.h"
#include "geoconverter.h"
#include "lasconverter.h"
#include <QDebug>
#include "gtkthread.h"


Converter::Converter()
    :m_currentConverter(nullptr)
{
    m_vLayout = new QVBoxLayout();
    m_labelPath = new QLineEdit();
    m_btnConvert = new QPushButton(tr("convert"));
    m_labelPath->setFont(QFont("Times new roman",10,QFont::Bold));
    m_labelPath->setAttribute(Qt::WA_Disabled);
    m_converters.insert(".gfm",new GfmConverter);
    m_converters.insert(".geo",new GeoConverter);
    m_converters.insert(".las",new LasConverter);
    m_converters.insert(".LAS",new LasConverter);

    m_vLayout->addWidget(m_labelPath);
    foreach(auto converter,m_converters){
        m_vLayout->addWidget(converter);
        converter->hide();
    }

    m_vLayout->addStretch(100);
    m_vLayout->addWidget(m_btnConvert);

    setLayout(m_vLayout);
    connect(m_btnConvert,&QPushButton::released,this,&Converter::convert);
}

Converter::~Converter(){

}

void Converter::setFilePath(const QString fileName){
    QString f_file = fileName.split("/").last();
    if(f_file.indexOf('.') == -1)
        return;
    if(m_currentConverter)
        m_currentConverter->hide();
    m_path = fileName;
    m_labelPath->setText(tr("File name: ") + f_file.right(30));
    QString f_type = f_file.mid(f_file.indexOf("."));
    m_currentConverter = m_converters.value(f_type);
    if(m_currentConverter)
        m_currentConverter->show();
}

void Converter::convert(){
    if(m_currentConverter){
        m_currentConverter->setFileName(m_path);
        m_currentConverter->convert();
    }
}
