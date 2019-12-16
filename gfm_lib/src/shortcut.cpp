#include "shortcut.h"

ShortCut::ShortCut(){
    m_ref = nullptr;
    m_name = nullptr;
}

void ShortCut::setRef(QString ref){
    m_ref = ref;
}
void ShortCut::setName(QString name){
    m_name = name;
}
QString ShortCut::getRef(){
    return m_ref;
}
QString ShortCut::getName(){
    return m_name;
}
