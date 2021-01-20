#include "geoloader.h"
#include <QFile>
#include <QDebug>
#include <QTextCodec>
#include <QFileInfo>


GeoLoader::GeoLoader(QString path):
    m_path(path),m_process(nullptr),m_gfmLoader(nullptr)
{
    m_process =  new QProcess();
    connect(m_process,SIGNAL(finished(int)),
                  this,SLOT(endProcess(int)));
    connect(m_process,SIGNAL(readyReadStandardOutput()),
                  this,SLOT(readyRead()));
    connect(m_process,&QProcess::readyReadStandardOutput,this,&GeoLoader::readyRead);
    connect(m_process,&QProcess::readyReadStandardError,this,&GeoLoader::readyRead);
}

GeoLoader::~GeoLoader(){

}

bool GeoLoader::download(){
    m_isReady = false;
    m_process->start(QDir().currentPath() + "/converter/ConverterGTK.exe",
    QStringList() << QTextCodec::codecForName("UTF-8")->fromUnicode(m_path)
                  << QTextCodec::codecForName("UTF-8")->fromUnicode("gfm"));

    QFile f_logs("LDLoaderLastMsg.txt");
    f_logs.open(QIODevice::WriteOnly);
    f_logs.close();
    if(m_process->waitForStarted()){
        qDebug() << "process started" << QDir().currentPath() + "/converter/ConverterGTK.exe" << m_path << endl;
    }
    else{
        QFile f_logs("LDgLoader.txt");
        if(f_logs.open(QIODevice::Append)){
            qDebug() << "process no started" << "./converter/Converter.exe" << m_path;
            f_logs.write(("process no started ./converter/Converter.exe " + m_path).toLocal8Bit());
        }
        f_logs.close();
    }
    return true;
}

void GeoLoader::run(){

}

void GeoLoader::endProcess(int exitCode){
    qDebug() << "end porocess" << m_process->readAll() << exitCode << endl;
    QFileInfo f_fileInfo(m_path);
    QString f_fileNameGFM = f_fileInfo.fileName().replace(".geo",".gfm");
    QFile f_fileGFM("work/tmp/" + f_fileNameGFM);
    if(!f_fileGFM.exists()){
        m_blocks = nullptr;
        return;
    }
    m_gfmLoader = new GFMLoader(QFileInfo(f_fileGFM).absoluteFilePath());
    m_gfmLoader->setBlocks(m_blocks);
    m_gfmLoader->download();
    while(!m_gfmLoader->isReady()){}
    if(f_fileGFM.remove())
        qDebug() << QFileInfo(f_fileGFM).absoluteFilePath() << " deleted!" << endl;
    else
        qDebug() << QFileInfo(f_fileGFM).absoluteFilePath() << " not deleted!" << endl;
    m_isReady = true;
    emit ready();
}

void GeoLoader::readyRead(){
    QFile f_logs("LDLoaderLastMsg.txt");
    if(f_logs.open(QIODevice::Append)){
        f_logs.write(m_process->readAll());
    }
    f_logs.close();
    qDebug() <<"readyRed:" << m_process->readAll() << endl;
}
