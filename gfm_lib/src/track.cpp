#include "track.h"

Track::Track(QDomNode *xmlTracks){
    m_xmlTracks = xmlTracks;
    m_items = new QList<ItemInfo*>;
    QDomNode item = m_xmlTracks->firstChild();
    while (false == item.isNull()){
        QString tag = item.nodeName();
        if(tag == "begin" || tag == "width" || tag == "logarithm"){

        }
        else{
            m_items->push_back(new ItemInfo(new QDomNode(item)));
        }
        item = item.nextSibling();
    }
}

int Track::left(){
    QDomNode track = m_xmlTracks->firstChild();
    while (false == track.isNull()){
        if(track.nodeName() == "begin"){
           QString value = track.attributes().namedItem("value").nodeValue();
           QString unit = track.attributes().namedItem("unit").nodeValue();
           if(unit == "CM")
               return static_cast<int>(value.replace(',','.').toDouble() * 50);
           else{
               qDebug() << "Новые единицы измерения track.cpp begin" << unit;
               break;
           }
        }
        track = track.nextSibling();
    }
    return 0;
}

int Track::width(){
    QDomNode track = m_xmlTracks->firstChild();
    while (false == track.isNull()){
        if(track.nodeName() == "width"){
            QString value = track.attributes().namedItem("value").nodeValue();
            QString unit = track.attributes().namedItem("unit").nodeValue();
            if(unit == "CM")
                return static_cast<int>(value.replace(',','.').toDouble() * 50);
            else{
                qDebug() << "Новые единицы измерения track.cpp width" << unit;
                break;
            }
        }
        track = track.nextSibling();
    }
    return 0;
}

Track::~Track(){

}
