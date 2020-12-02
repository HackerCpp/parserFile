#include "lissaver.h"
#include <QDebug>
#include <QDateTime>

#include <QFileDialog>
#include <gfmsaver.h>
#include <QFileInfo>
#include <QDir>

LisSaver::LisSaver()
{
    m_fileName = "";
    m_fileGFM = nullptr;
    m_process =  new QProcess();
    connect(m_process,SIGNAL(finished(int)),
                  this,SLOT(endProcess(int)));
    connect(m_process,SIGNAL(readyReadStandardOutput()),
                  this,SLOT(readyRead()));
}

LisSaver::~LisSaver(){

}

bool LisSaver::save(){
    m_isReady = false;
    if(!m_blocks){
        qDebug() << "Нечего сохранять,добавьте данные";
    }
    QDateTime date;
    QString stringDate = date.currentDateTime().toString("dd_MM_yyyy_hh_mm");
    m_fileName = QFileDialog::getSaveFileName(nullptr,tr("Save file as "),stringDate,"LIS(*.lis)");

    m_fileGFM = new QFile("work\\tmp\\" + QFileInfo(m_fileName).fileName().replace(".lis",".gfm").replace(".LIS",".gfm"));
    GFMSaver m_saver;
    m_saver.setBlocks(m_blocks);
    QString  f_filePath = QFileInfo(*m_fileGFM).absoluteFilePath();
    m_saver.save(f_filePath);
    while(!m_saver.isReady()){}
    if(!m_fileGFM->exists())
        return false;

    QStringList f_arguments;
    f_arguments << QTextCodec::codecForName("UTF-8")->fromUnicode(f_filePath) << QTextCodec::codecForName("UTF-8")->fromUnicode("lis");
    m_process->start("./converter/ConverterGTK.exe",f_arguments);
    if(m_process->waitForStarted()){
        qDebug() << "process started" << "./converter/Converter.exe" << f_filePath << "  " << "lis";
    }
    return true;
}

bool LisSaver::isReady(){
    return m_isReady;
}

void LisSaver::endProcess(int){
    QFileInfo f_fileInfoGFM(*m_fileGFM);
    QDir f_dir = f_fileInfoGFM.absoluteDir();
    QStringList f_files = f_dir.entryList();
    QFile *f_file = nullptr;
    foreach(auto file,f_files){
        if(file.indexOf(f_fileInfoGFM.fileName().remove(".gfm")) != -1 && file.indexOf(".lis") != -1){
            f_file = new QFile(f_dir.path() + "/" +file);
            break;
        }
    }
    m_fileGFM->remove();
    if(!f_file){
        m_isReady = true;
        emit ready("");
        return;
    }
    f_file->rename(m_fileName);

    qDebug() << m_process->readAll();
    m_isReady = true;
    emit ready(m_fileName);
}

void LisSaver::readyRead(){
    qDebug() << m_process->readAll();
}
