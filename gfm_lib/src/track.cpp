#include "track.h"

Track::Track(QDomNode *xmlTracks){
    m_xmlTracks = xmlTracks;
    //qDebug() << m_xmlTracks->attributes().namedItem("name").nodeValue();
    QDomNode track = m_xmlTracks->firstChild();
    while (false == track.isNull()){
        QString tag = track.nodeName();
        if(tag == "begin" || tag == "width" || tag == "logarithm"){

        }
        else{
        }
        track = track.nextSibling();
    }
    left();
    width();
}

int Track::left(){
    QDomNode track = m_xmlTracks->firstChild();
    while (false == track.isNull()){
        if(track.nodeName() == "begin"){
           QString value = track.attributes().namedItem("value").nodeValue();
           QString unit = track.attributes().namedItem("unit").nodeValue();
           if(unit == "CM")
               return value.replace(',','.').toInt() * 10;
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
                return value.replace(',','.').toInt() * 10;
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
