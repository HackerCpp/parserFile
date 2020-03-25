#include "aitem.h"

AItem::AItem()
{

}
AItem::~AItem()
{

}
bool AItem :: isBeginValue()
{
    return m_begin.is_beginValue;
}
qreal AItem :: zeroOffset()
{
    return m_begin.zeroOffset;
}

qreal AItem :: beginValue()
{
    return m_begin.beginValue;
}
bool AItem :: isEndValue()
{
    return m_end.is_endValue;
}
qreal AItem :: endValue()
{
    return m_end.is_endValue;
}
qreal AItem :: scale()
{
    return m_end.scale;
}
QString AItem :: name()
{
    return m_name;
}
QString AItem :: visible()
{
    return m_visible;
}

bool AItem :: isMultiScale()
{
    return m_multiScale.is_multiscale;
}
qreal AItem :: glemCount()
{
    return m_multiScale.gleamCount;
}

TypeItem AItem :: Type()
{
    return m_type;
}


qreal AItem :: glemScale()
{
   return m_multiScale.gleamScale;
}


void AItem :: setBegin(bool isBegin,qreal begin,qreal zeroOffset)
{
    m_begin.is_beginValue = isBegin;
    m_begin.beginValue = begin;
    m_begin.zeroOffset = zeroOffset;
}
void AItem :: setEnd(bool isEnd,qreal end,qreal scale)
{
    m_end.is_endValue = isEnd;
    m_end.endValue = end;
    m_end.scale = scale;
}
void AItem :: setMultiScale(bool isMultiScale,qreal gleamCount,qreal gleamScale)
{
    m_multiScale.is_multiscale = isMultiScale;
    m_multiScale.gleamCount = gleamCount;
    m_multiScale.gleamScale = gleamScale;
}

void AItem :: setName(QString name, QString visible)
{
    m_name = name;
    m_visible = visible;
}
void AItem ::setTypeItem(TypeItem type)
{
    m_type = type;
}






