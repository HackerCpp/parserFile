#include "module.h"
#include <QMessageBox>



bool Module::isOneMoreTwo(QString versionOne,QString versionTwo){
    QStringList f_listOne = versionOne.split(".");
    QStringList f_listTwo = versionTwo.split(".");
    if(f_listOne.size() > f_listTwo.size())
        return true;
    else if(f_listOne.size() < f_listTwo.size())
        return false;
    for(int i = 0; i < f_listOne.size(); i++){
        if(f_listOne[i].toInt() > f_listTwo[i].toInt())
            return true;
    }
    return false;
}


QString Module::latestVersion(){
    if(!m_versions->size())
        return "";
    if(m_versions->size() == 1)
        return m_versions->operator[](0)->version();
    int i = 0;
    for(int j = 1; j < m_versions->size();++j){
        if(isOneMoreTwo(m_versions->operator[](j)->version(),m_versions->operator[](i)->version())){
          i = j;
        }
    }

    return m_versions->operator[](i)->version();
}

QString Module::nextVersion(){
    QString f_currentMaximumVersion = latestVersion();
    QStringList f_versions = f_currentMaximumVersion.split(".");
    QStringList f_newVersions = f_versions;
    for(int i = f_versions.size() - 1;i >= 0;--i){
        if(f_versions[i].toInt() >= 99 && i != 0){
            f_newVersions[i] = "0";
        }
        else{
            f_newVersions[i] = QString::number(f_versions[i].toInt() + 1);
            break;
        }
    }
    QString f_newVersion;
    foreach(auto version,f_newVersions){
        f_newVersion += "." + version;
    }
    f_newVersion = f_newVersion.mid(1);
    return f_newVersion;
}
