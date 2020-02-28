#include "logdata.h"

LogData::LogData(){
    m_loader = nullptr;
    m_blocks = new QList<IBlock>;
}

LogData::~LogData(){
    if(m_loader){
        delete m_loader;
        m_loader = nullptr;
    }
    if(m_blocks)
        delete m_blocks;
}

bool LogData::load(){
    if(!m_loader)
        return false;
    m_loader->start();
    return true;
}

bool LogData::save(){
    return true;

}

bool LogData::setLoader(ILoaderLogData *loader){
    if(m_loader)
        delete m_loader;
    m_loader = loader;
    m_loader->setBlocks(m_blocks);
    return true;
}
