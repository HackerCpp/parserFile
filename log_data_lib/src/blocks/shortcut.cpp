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

QString ShortCut::nameWithoutNumber(){
    return m_nameWithoutNumber;
}

QString ShortCut::ref(){
    return m_ref;
}

QString ShortCut::name(){
    return m_name;
}

QString ShortCut::dateTime(){
    return m_name.mid(0,m_name.indexOf("."));
}

QString ShortCut::device(){
    return m_name.mid(m_name.indexOf(".") + 1);
}
