#include "atrack.h"
#include <QDebug>

ATrack::ATrack(){
    m_items = new QList<AItem *>;
}

void ATrack::setLogarithm(qreal log_base,qreal dec_count, qreal dec_start,qreal dec_end){
    m_logarithm.logarithmBase = log_base;
    m_logarithm.decadeCount = dec_count;
    m_logarithm.decadeStart = dec_start;
    m_logarithm.decadeEnd = dec_end;
}

void ATrack::setItem(AItem *items){
    if(m_items)
        m_items->push_back(items);
    else
        qDebug() << "не удалось вставить кривые, нулевой указатель";
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
