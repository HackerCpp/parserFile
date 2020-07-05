#include "drawingthroughadisk.h"
#include <QFile>
#include <QUuid>
#include <QDebug>

DrawingThroughADisk::DrawingThroughADisk(){

    m_uid = QUuid().createUuid().toString();
    m_isEndThread = m_isRedraw = false;
    m_curentDrawPersent = 0;
    m_lengthOverlay = 500;
    connect(this,&QThread::finished,this,&DrawingThroughADisk::endThreadHandler);
}

DrawingThroughADisk::~DrawingThroughADisk(){
    if(isRunning())
        terminate();
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


