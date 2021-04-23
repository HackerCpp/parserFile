#include "loaderviaconvertergtk.h"

LoaderViaConverterGTK::LoaderViaConverterGTK(QString path):
    m_path(path),m_process(nullptr),m_gfmLoader(nullptr)
{
    m_format = "";
    m_process =  std::make_unique<QProcess>();
    connect(m_process.get(),SIGNAL(finished(int)),
                  this,SLOT(endProcess(int)));
    connect(m_process.get(),SIGNAL(readyReadStandardOutput()),
                  this,SLOT(readyRead()));

}




LoaderViaConverterGTK::~LoaderViaConverterGTK(){

}

bool LoaderViaConverterGTK::download(){
    if(m_format.isEmpty())
    m_isReady = false;
    QStringList f_arguments;
    f_arguments << QTextCodec::codecForName("UTF-8")->fromUnicode(m_path) << QTextCodec::codecForName("UTF-8")->fromUnicode("gfm");
    m_process->start("./converter/ConverterGTK.exe",f_arguments);
    if(m_process->waitForStarted()){
        qDebug() << "process started" << "./converter/Converter.exe" << m_path;
    }
    return true;
}

void LoaderViaConverterGTK::run(){

}

void LoaderViaConverterGTK::endProcess(int exitCode){
    qDebug() << m_process->readAll() << exitCode;
    QFileInfo f_fileInfo(m_path);
    QString f_fileNameGFM = f_fileInfo.fileName().replace(m_format,".gfm");
    QFile f_fileGFM("work/tmp/" + f_fileNameGFM);
    if(!f_fileGFM.exists()){
        m_blocks = nullptr;
        return;
    }
    qDebug() << QFileInfo(f_fileGFM).absoluteFilePath();
    m_gfmLoader = std::make_unique<GFMLoader>(QFileInfo(f_fileGFM).absoluteFilePath());
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

void LoaderViaConverterGTK::readyRead(){
    qDebug() << m_process->readAll();
}
