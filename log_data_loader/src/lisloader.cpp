#include "lisloader.h"
#include <QFile>
#include <QDebug>
#include <QTextCodec>
#include <QFileInfo>


LisLoader::LisLoader(QString path):
    m_path(path),m_process(nullptr),m_gfmLoader(nullptr)
{
    m_process =  new QProcess();
    connect(m_process,SIGNAL(finished(int)),
                  this,SLOT(endProcess(int)));
    connect(m_process,SIGNAL(readyReadStandardOutput()),
                  this,SLOT(readyRead()));

}

LisLoader::~LisLoader(){

}

bool LisLoader::download(){
    m_isReady = false;
    QStringList f_arguments;
    f_arguments << QTextCodec::codecForName("UTF-8")->fromUnicode(m_path) << QTextCodec::codecForName("UTF-8")->fromUnicode("gfm");
    m_process->start("./converter/ConverterGTK.exe",f_arguments);
    if(m_process->waitForStarted()){
        qDebug() << "process started" << "./converter/Converter.exe" << m_path;
    }
    return true;
}

void LisLoader::run(){

}

void LisLoader::endProcess(int exitCode){
    qDebug() << m_process->readAll() << exitCode;
    QFileInfo f_fileInfo(m_path);
    QString f_fileNameGFM = f_fileInfo.fileName().replace(".lis",".gfm");
    QFile f_fileGFM("work/tmp/" + f_fileNameGFM);
    if(!f_fileGFM.exists()){
        m_blocks = nullptr;
        return;
    }
    qDebug() << QFileInfo(f_fileGFM).absoluteFilePath();
    m_gfmLoader = new GFMLoader(QFileInfo(f_fileGFM).absoluteFilePath());
    m_gfmLoader->setBlocks(m_blocks);
    m_gfmLoader->download();
    while(!m_gfmLoader->isReady()){}
    if(f_fileGFM.remove())
        qDebug() << QFileInfo(f_fileGFM).absoluteFilePath() << " deleted!";
    else
        qDebug() << QFileInfo(f_fileGFM).absoluteFilePath() << " not deleted!";
    m_isReady = true;
    emit ready();
}

void LisLoader::readyRead(){
    qDebug() << m_process->readAll();
}
