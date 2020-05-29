#include "atrack.h"
#include <QDebug>

ATrack::ATrack(){
    m_number = 1;
    m_name = "Track 1";
}

ATrack::ATrack(const ATrack &other){
    m_type = other.m_type;
    m_name = other.m_name;
    m_number = other.m_number;
    m_isGreed = other.m_isGreed;
    m_begin = other.m_begin;
    m_width = other.m_width;
    m_logarithm.logarithmBase = other.m_logarithm.logarithmBase;
    m_logarithm.decadeCount = other.m_logarithm.decadeCount;
    m_logarithm.decadeStart = other.m_logarithm.decadeStart;
    m_logarithm.decadeEnd = other.m_logarithm.decadeEnd;
}

void ATrack::setLogarithm(qreal log_base,qreal dec_count, qreal dec_start,qreal dec_end){
    m_logarithm.logarithmBase = log_base;
    m_logarithm.decadeCount = dec_count;
    m_logarithm.decadeStart = dec_start;
    m_logarithm.decadeEnd = dec_end;
}



qreal ATrack::logarithmBase(){
    return m_logarithm.logarithmBase;
}

qreal ATrack::decadeCount(){
    return m_logarithm.decadeCount;
}

qreal ATrack::decadeStart(){
    return m_logarithm.decadeStart;
}

qreal ATrack::decadeEnd(){
    return m_logarithm.decadeEnd;
}
