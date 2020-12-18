#include "logdata.h"
#include "datablock.h"
#include "ilogdata.h"

LogData::LogData(){
    m_loader = nullptr;
    m_saver = nullptr;
    m_interpreter = nullptr;
    m_blocks = new QList<IBlock *>;
}

LogData::LogData(const LogData &logData){
    if (this == &logData)
        return;
    m_loader = nullptr;
    m_saver = nullptr;
    m_interpreter = nullptr;
    m_blocks = new QList<IBlock *>;
    m_name = logData.m_name;
    foreach(auto block,*logData.m_blocks){
        m_blocks->push_back(IBlock::blockCreater(*block));
    }
    m_isReady = true;
}

LogData &LogData::operator=(const LogData &logData){
    if (this == &logData)
        return *this;
    m_loader = nullptr;
    m_saver = nullptr;
    m_interpreter = nullptr;
    m_blocks = new QList<IBlock *>;
    m_name = logData.m_name;
    foreach(auto block,*logData.m_blocks){
        m_blocks->push_back(IBlock::blockCreater(*block));
    }
    m_isReady = true;
    return *this;
}

LogData::~LogData(){
    if(m_loader){
        delete m_loader;
        m_loader = nullptr;
    }
    if(m_saver){
        delete m_saver;
        m_saver = nullptr;
    }
    if(m_blocks){
        delete m_blocks;
        m_blocks = nullptr;
    }
}

bool LogData::load(){
    m_isReady = false;
    if(!m_loader)
        return false;
    m_loader->download();
    if(!m_loader->isReady())
        connect(m_loader,&ILoaderLogData::ready,this,&ILogData::dataReady);
    else
        dataReady();
    return true;
}

bool LogData::save(){
    if(m_saver){
        qDebug() << "saver";
        m_saver->save();
    }
    else{
        qDebug() << "Не найден сохранятель для лог даты";
        return false;
    }
    return true;
}

bool LogData::openInterpreterConsole(){
    if(!m_interpreter)
        return false;
    m_interpreter->openConsole();
    return true;
}

bool LogData::openInterpreterScript(){
    if(!m_interpreter)
        return false;
    m_interpreter->openScript();
    return true;
}
bool LogData::openInterpreterEditor(){
    if(!m_interpreter)
        return false;
    m_interpreter->openEditor();
    return true;
}

bool LogData::setLoader(ILoaderLogData *loader){
    if(m_loader)
        delete m_loader;
    m_loader = loader;
    m_loader->setBlocks(m_blocks);
    return true;
}

bool LogData::setSaver(ISaverLogData *saver){
    if(m_saver)
        delete m_saver;
    m_saver = saver;
    m_saver->setBlocks(m_blocks);
    return true;
}

bool LogData::setInterpreter(IInterpreterLogData *interpreter){
    if(m_interpreter)
        delete m_interpreter;
    m_interpreter = interpreter;
    m_interpreter->setBlocks(m_blocks);
    return true;
}

QList<IBlock *> *LogData::blocks(){
    return m_blocks;
}

void LogData::dataUpdate(){
    if(m_interpreter)
        m_interpreter->dataUpdate();
}

void LogData::addBlock(IBlock *block){
    m_blocks->push_back(block);
    connect(block,&IBlock::dataUpdate,this,&ILogData::dataUpdate);
    dataUpdate();
}

void LogData::dataReady(){
    foreach(auto block,*m_blocks){
        connect(block,&IBlock::dataUpdate,this,&ILogData::dataUpdate);
    }
    m_isReady = true;
    emit ready();
}
