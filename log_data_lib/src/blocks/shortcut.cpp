#include "shortcut.h"

ShortCut::ShortCut(){
    m_ref = nullptr;
    m_name = nullptr;
    m_nameWithoutNumber = nullptr;
}

void ShortCut::setRef(QString ref){
    m_ref = ref;
}
void ShortCut::setName(QString name){
    m_name = name;
    m_nameWithoutNumber = m_name.mid(0,m_name.indexOf("["));
}
QString ShortCut::getNameWithoutNumber(){
    return m_nameWithoutNumber;
}
QString ShortCut::getRef(){
    return m_ref;
}
QString ShortCut::getName(){
    return m_name;
}
