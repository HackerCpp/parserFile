#include "aboard.h"
#include <QDebug>

ABoard::ABoard(){
    m_tracks = new QList<ATrack*>;
    m_items = new QMap<QString, AItem*>;
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

QList<ATrack*> *ABoard::tracks(){
    return m_tracks;
}
void ABoard::setItem(QString name, AItem *items)
{
    if(m_items)
        m_items->insert(name,items);
    else
        qDebug() << "не удалось вставить кривые, нулевой указатель";
}
QMap<QString,AItem*> *ABoard::items()
{
    return m_items;
}

QString ABoard::name()
{
    return m_name;
}
