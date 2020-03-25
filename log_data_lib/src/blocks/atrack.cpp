#include "atrack.h"
#include <QDebug>

ATrack::ATrack()
{
    m_items = new QList<AItem*>;
}

void ATrack::setIsGreed(bool isGreed){
    m_IsGreed = isGreed;
}

void ATrack::setName(QString name){
    m_name = name;
}

void ATrack::setType(Types type){

        m_type = type;
}

void ATrack::setLogarithm(qreal log_base,qreal dec_count, qreal dec_start,qreal dec_end){
    m_logarithm.logarithmBase = log_base;
    m_logarithm.decadeCount = dec_count;
    m_logarithm.decadeStart = dec_start;
    m_logarithm.decadeEnd = dec_end;
}
void ATrack::setItem(AItem *items)
{
    if(m_items)
        m_items->push_back(items);
    else
        qDebug() << "не удалось вставить кривые, нулевой указатель";
}
void ATrack::setBegin(qreal begin){

        m_begin = begin;
}




void ATrack::setWidth(qreal width){

    m_width = width;

}


Types ATrack :: Type()
{
        return m_type;
}

QList<AItem*> ATrack:: Items()
{
    return *m_items;
}
bool ATrack::IsGreed()
{
    return m_IsGreed;
}
QString ATrack::Name()
{
    return m_name;
}

qreal ATrack::Begin()
{
    return m_begin;
}
qreal ATrack::Width()
{
    return m_width;
}

qreal ATrack::LogarithmBase()
{
    return m_logarithm.logarithmBase;
}
qreal ATrack::DecadeCount()
{
    return m_logarithm.decadeCount;
}
qreal ATrack::DecadeStart()
{
    return m_logarithm.decadeStart;
}
qreal ATrack::DecadeEnd()
{
    return m_logarithm.decadeEnd;
}
