#include "desc.h"

void parserParameters(QByteArray parameters,QHash<QString,QString> *hash){
    for(int pos = 0;pos < parameters.size();){
        int f_indexEqually = parameters.indexOf("=",pos);
        if(f_indexEqually == -1)
            return;
        QString index = parameters.mid(pos,f_indexEqually - pos);
        int f_indexEndParam = parameters.indexOf("\"",f_indexEqually + 3);
        if(f_indexEndParam == -1)
            return;
        QString value = parameters.mid(f_indexEqually + 2,f_indexEndParam - f_indexEqually - 2);
        pos = f_indexEqually + value.size() + 4;
        hash->insert(index,value);
    }
}

Desc::Desc(QByteArray desc){
    m_parameters = new QHash<QString,QString>;
    m_calibration = new QHash<QString,QString>;
    if(desc.isEmpty())
        return;
    int f_indexBeginDesc = desc.indexOf("<desc ") + QString("<desc ").size();
    if(f_indexBeginDesc - QString("<desc ").size() == -1)
        return;
    int f_indexEndDesc = desc.indexOf(">",f_indexBeginDesc);
    QByteArray f_parameters = desc.mid(f_indexBeginDesc,f_indexEndDesc - f_indexBeginDesc);
    QByteArray f_calibration;
    int f_indexBeginCalib = desc.indexOf("<calibration ",f_indexEndDesc) + QString("<calibration ").size();
    if(f_indexBeginCalib - QString("<calibration ").size() != -1){
        int f_indexEndCalib = desc.indexOf("/>",f_indexBeginCalib);
        f_calibration = desc.mid(f_indexBeginCalib,f_indexEndCalib - f_indexBeginCalib);
    }
    if(!f_parameters.isEmpty())
        parserParameters(f_parameters,m_parameters);
    if(!f_calibration.isEmpty())
        parserParameters(f_calibration,m_calibration);

}
QString Desc::param(QString index){
    return m_parameters->value(index);
}
QString Desc::calib(QString index){
    return m_calibration->value(index);
}
QByteArray Desc::forSave(){
    QByteArray f_byteArray;
    QString f_string = "<desc";
    for(auto i = m_parameters->begin(); i != m_parameters->end();i++) {
        QString f_str = " %1=\"%2\"";
        f_str = f_str.arg(*dynamic_cast<const QString*>(&i.key())).arg(i.value());
        f_string.append(f_str);
    }
    if(!m_calibration->isEmpty()){
        f_string.append("><calibration");
        for(auto i = m_calibration->begin(); i != m_calibration->end();i++) {
            QString f_str = " %1=\"%2\"";
            f_str = f_str.arg(*dynamic_cast<const QString*>(&i.key())).arg(i.value());
            f_string.append(f_str);
        }
        f_string.append("/></desc>");
    }
    else
        f_string.append("/>");
    f_byteArray = f_string.toLocal8Bit();
    return f_byteArray;
}
