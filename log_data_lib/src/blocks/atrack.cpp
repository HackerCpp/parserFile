#include "atrack.h"
#include <QDebug>
ATrack::ATrack()
{
    m_items = new QList<AItems*>;
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
void ATrack :: setWidthString(QString valueString)
{
    m_widthString = valueString.replace(",",".");
}
void ATrack::setType(Type type){
    m_type = type;
}

QString ATrack ::getType()
{
    if(m_type==LINEAR)
        return "LINEAR";
}

void ATrack::setLogarithm(float log_base,float dec_count, float dec_start,float dec_end){
    m_logarithm.logarithmBase = log_base;
    m_logarithm.decadeCount = dec_count;
    m_logarithm.decadeStart = dec_start;
    m_logarithm.decadeEnd = dec_end;
}
void ATrack::setItems(AItems *items)
{
    if(m_items)
        m_items->push_back(items);
    else
        qDebug() << "не удалось вставить кривые, нулевой указатель";
}
void ATrack::setBegin(QString begin,QString unit){
    begin = begin.replace(",",".");
    if(unit == "CM")
    {
        m_begin = begin.toFloat()*10;
    }
    else
    {
        m_begin = begin.toFloat();
    }

}


QList<AItems*> ATrack:: getItems()
{
    return *m_items;
}

void ATrack::setWidth(QString width,QString unit){

    width = width.replace(",",".");
    if(unit == "CM")
    {
        m_width = width.toFloat()*10;
    }
    else
    {
        m_width = width.toFloat();
    }
}

