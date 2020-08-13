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
        m_mapParameters->insert(index,value);
        m_vectorParameters->push_back(new Paraminfo(index,value));
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
    m_mapParameters->insert(index,value);
    m_vectorParameters->push_back(new Paraminfo(index,value));
}


/*********************************************************************************/

Desc::Desc(QByteArray desc)
    : m_parameters(nullptr),m_calibration(nullptr){
    //m_parameters = new QHash<QString,QString>;
    //m_calibration = new QHash<QString,QString>;
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
        //parserParameters(f_parameters,m_parameters);
        m_parameters = new Parameters(f_parameters,Parameters::PARAM);
    else
        m_parameters = new Parameters(Parameters::PARAM);
    if(!f_calibration.isEmpty())
        //parserParameters(f_calibration,m_calibration);
        m_calibration = new Parameters(f_calibration,Parameters::CALIB);
    else
        m_calibration = new Parameters(Parameters::CALIB);

}

Desc::Desc(){
    //m_parameters = new QHash<QString,QString>;
    //m_calibration = new QHash<QString,QString>;
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

