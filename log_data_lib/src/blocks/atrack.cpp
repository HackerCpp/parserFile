#include "atrack.h"
#include <QDebug>

ATrack::ATrack(){
    m_number = 1;
    m_name = "Track 1";
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
