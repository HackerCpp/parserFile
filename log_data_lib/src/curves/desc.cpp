#include "desc.h"

Paraminfo::Paraminfo(QString index,QString value)
    :m_index(index),m_value(value){

}
/*********************************************************************/
void Parameters::init(){
    m_mapParameters = new QMap<QString,QString>;
    m_vectorParameters = new QVector<Paraminfo *>;
}
Parameters::Parameters(QByteArray parameters,Type type)
    : m_type(type){
    init();
    QStringList f_stringList = QString(parameters).split(' ');
    foreach(auto value,f_stringList){
        QStringList param = value.split('=');
        if(param.size() == 2)
            insert(param[0],param[1].remove('"').remove('/'));
    }
}

Parameters::Parameters(Type type)
    : m_type(type){
    init();
}

Parameters::~Parameters(){
    if(m_vectorParameters){
        foreach(auto value,*m_vectorParameters)
            if(value){delete value;value = nullptr;}
        delete m_vectorParameters; m_vectorParameters = nullptr;
    }
}

void Parameters::insert(QString index,QString value){
    if(m_mapParameters->value(index,"noIndex") != "noIndex"){
        m_mapParameters->remove(index);
        //foreach(auto paramInfo,*m_vectorParameters){
        for(int i = 0; i < m_vectorParameters->size(); ++i){
            if(m_vectorParameters->operator[](i)->index() == index){
                m_vectorParameters->operator[](i)->setValue(value);
                break;
            }
        }
        m_mapParameters->insert(index,value);
    }
    else{
        m_mapParameters->insert(index,value);
        m_vectorParameters->push_back(new Paraminfo(index,value));
    }

}


/*********************************************************************************/

Desc::Desc(QByteArray desc)
    : m_parameters(nullptr),m_calibration(nullptr){
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
        m_parameters = new Parameters(f_parameters,Parameters::PARAM);
    else
        m_parameters = new Parameters(Parameters::PARAM);

    if(!f_calibration.isEmpty())
        m_calibration = new Parameters(f_calibration,Parameters::CALIB);
    else
        m_calibration = new Parameters(Parameters::CALIB);

}

Desc::Desc(){
    m_parameters = new Parameters(Parameters::PARAM);
    m_calibration = new Parameters(Parameters::CALIB);
}

Desc::~Desc(){
    if(m_parameters){delete m_parameters; m_parameters = nullptr;}
    if(m_calibration){delete m_calibration; m_calibration = nullptr;}
}

void Desc::setParam(QString index,QString value){
    if(m_parameters)
        m_parameters->insert(index,value);
}

void Desc::setCalib(QString index,QString value){
    if(m_calibration)
        m_calibration->insert(index,value);
}

QString Desc::param(QString index){
    return m_parameters->value(index);
}

QString Desc::calib(QString index){
    return m_calibration->value(index);
}

