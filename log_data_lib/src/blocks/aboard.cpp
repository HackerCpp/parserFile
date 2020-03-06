#include "aboard.h"
#include <QDebug>

ABoard::ABoard(){
    m_tracks = new QList<ATrack*>;
}

ABoard::~ABoard(){

}

void ABoard::setName(QString name){
    m_name = name;
}

void ABoard::setTrack(ATrack *track){
    if(m_tracks)
        m_tracks->push_back(track);
    else
        qDebug() << "не удалось вставить трэк, нулевой указатель";
}
