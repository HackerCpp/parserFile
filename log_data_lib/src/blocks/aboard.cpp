#include "aboard.h"
#include <QDebug>
#include "iteminfocreater.h"

ABoard::ABoard(){
    m_tracks = new QList<ATrack*>;
    m_items = new QMap<QString, AItem*>;
}

ABoard::ABoard(const ABoard &object){
    m_tracks = new QList<ATrack*>;
    m_items = new QMap<QString, AItem*>;
    m_name = object.m_name;
    foreach(auto item,object.m_items->values()){
        m_items->insert(m_items->key(item),item);
    }
    foreach(auto track,*object.m_tracks){
        m_tracks->push_back(new ATrack(*track));
    }
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
