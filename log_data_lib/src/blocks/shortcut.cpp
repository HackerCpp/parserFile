#include "shortcut.h"
#include <QDebug>

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
    m_device = m_name.mid(m_name.indexOf(".") + 1);
    m_devName = m_device.mid(0,m_device.indexOf("["));
    m_devNum = m_device.mid(m_device.indexOf("[") + 1);
    m_devNum.chop(1);
}

QString ShortCut::nameWithoutNumber() const{
    return m_nameWithoutNumber;
}

QString ShortCut::ref() const{
    return m_ref;
}

QString ShortCut::name() const{
    return m_name;
}

QString ShortCut::dateTime() const{
    return m_name.mid(0,m_name.indexOf("."));
}

QString ShortCut::device() const{
    return m_device;
}

QString ShortCut::deviceName()const{
    return m_devName;
}

QString ShortCut::deviceNum()const{
    return m_devNum;
}
