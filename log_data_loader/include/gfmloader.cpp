#include "gfmloader.h"
#include <QDebug>
#include <QFile>

GFMLoader::GFMLoader(QString path){
    m_path = path;
}

GFMLoader::~GFMLoader(){

}

bool GFMLoader::start(){
    QFile file(m_path);
    file.open(QIODevice::ReadOnly);
    QByteArray byteArrayFile = file.readAll();
    file.close();


    return true;
}

bool GFMLoader::stop(){
    return true;

}

bool GFMLoader::isReady(){
    return true;
}
