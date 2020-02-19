#include "formsblockgfm.h"


FormsBlockGFM::FormsBlockGFM() :
    m_zipForms(nullptr){
}

void FormsBlockGFM::parser(QByteArray *bodyBlock){
    m_zipForms = new QByteArray(*bodyBlock);
}

QByteArray FormsBlockGFM::zipForms(){
    return *m_zipForms;
}

QByteArray FormsBlockGFM::getForSave(){
    QByteArray blockForWrite;
    int f_nameSize = m_name.size() * 2;
    blockForWrite.append(reinterpret_cast<char*>(&f_nameSize),2);       //Размер названия блока
    blockForWrite.append(m_codec->fromUnicode(m_name).mid(2));
    QByteArray f_data = zipForms();
    int f_dataBlockSize = zipForms().size() + 8;
    if(f_dataBlockSize % 2){
        ++f_dataBlockSize;
        f_data.append('0');
    }
    blockForWrite.append(reinterpret_cast<char*>(&f_dataBlockSize),4);
    blockForWrite.append(m_codec->fromUnicode("\r\n").mid(2));
    blockForWrite.append(f_data);
    blockForWrite.append(m_codec->fromUnicode("\r\n").mid(2));
    return blockForWrite;
}

FormsBlockGFM::~FormsBlockGFM(){
    if(m_zipForms)
        delete m_zipForms;
    m_zipForms = nullptr;
}
