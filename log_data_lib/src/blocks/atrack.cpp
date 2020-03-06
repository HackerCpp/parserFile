#include "atrack.h"

ATrack::ATrack()
{

}

void ATrack::setIsGreed(bool isGreed){
    m_IsGreed = isGreed;
}

void ATrack::setName(QString name){
    m_name = name;
}

void ATrack::setType(QString type){
    if(type == "LINEAR")
        m_type = LINEAR;
}

void ATrack::setType(Type type){
    m_type = type;
}

void ATrack::setLogarothm(int log_base,int dec_count, int dec_start,int dec_end){
    m_logarithm.logarithmBase = log_base;
    m_logarithm.decadeCount = dec_count;
    m_logarithm.decadeStart = dec_start;
    m_logarithm.decadeEnd = dec_end;
}

void ATrack::setBegin(int begin){
    m_begin = begin;
}

void ATrack::setWidth(int width){
    m_width = width;
}

