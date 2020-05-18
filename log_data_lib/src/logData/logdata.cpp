#include "logdata.h"
#include "datablock.h"

LogData::LogData(){
    m_loader = nullptr;
    m_saver = nullptr;
    m_interpreter = nullptr;
    m_blocks = new QList<IBlock*>;
    m_curvesMap = new QMap<QString,ICurve*>;
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
    if(!m_loader->isReady()){
        connect(m_loader,&ILoaderLogData::ready,this,&ILogData::findCurvesMap);
    }
    else
        findCurvesMap();
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

bool LogData::openInterpreter(){
    if(!m_interpreter)
        return false;
    m_interpreter->openConsole();
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
    m_interpreter->setCurves(m_curvesMap);
    return true;
}

QMap<QString,ICurve*> *LogData::curves(){
   return m_curvesMap;
}

QList<IBlock*> *LogData::blocks(){
    return m_blocks;
}

void LogData::findCurvesMap(){
    foreach(auto block,*m_blocks){
        if(block->name() == IBlock::DATA_BLOCK){
           DataBlock *dataBlock = dynamic_cast<DataBlock*>(block);
           if(dataBlock){
               QList<ICurve*> *curves = dataBlock->curves();
               if(!curves){
                   qDebug() << "В Дата блоке нет кривых для формирования дерева поиска";
               }
               if(!m_curvesMap){
                   qDebug() << "Контейнер для кривых не создан";
               }

               foreach(auto curve,*curves){
                   if(!curve){
                       qDebug() << "Нулевая кривая в блоке";
                   }
                   if(!curve->shortCut().name().isEmpty()){
                       QString name = curve->shortCut().nameWithoutNumber() + ':' + curve->mnemonic();
                       m_curvesMap->insert(name,curve);
                   }
               }
           }
        }
    }

    m_isReady = true;
    emit ready();
}
