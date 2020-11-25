#include "drawingthroughadisk.h"
#include <QFile>
#include <QUuid>
#include <QDebug>

DrawingThroughADisk::DrawingThroughADisk(){
    m_saversMoment = false;
    m_uid = QUuid().createUuid().toString();
    m_isEndThread = m_isRedraw = false;
    m_curentDrawPersent = 0;
    m_lengthOverlay = 500;
    connect(this,&QThread::finished,this,&DrawingThroughADisk::endThreadHandler);
}

DrawingThroughADisk::~DrawingThroughADisk(){
    m_saversMoment = false;
    disconnect();
    blockSignals(true);
    if(isRunning()){
        m_isRedraw = false;
        m_isEndThread = true;
        wait();
    }
    foreach(auto path,m_picturePath){
        if(!QFile::exists(path) )
            continue;
        QFile(path).remove();
    }
    m_picturePath.clear();
}

void DrawingThroughADisk::endThreadHandler(){
    if(m_isRedraw){
        m_isRedraw = false;
        loadDrawingParam(m_curentPictureWidth);
        m_isEndThread = false;
        start();
    }
}


