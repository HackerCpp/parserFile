
#include"aitems.h"
#include <QList>
AItems::AItems()
{

}

void AItems::Setline(QString name,QString visible)
{
    m_name=name;
    m_visible = visible;
}
void AItems::SetPeintMode(QString mode)
{
    m_mode = mode;
}
void AItems::SetStyle(QString color, float datashes)
{
    m_color=color;
    m_datashes = datashes;

}

void AItems::SetEndAcu(QString step_scale, QString unit)
{
    step_scale = step_scale.replace(",",".");
    if(unit=="CM")
    {
        m_end.step_scale = step_scale.toFloat()*10;
    }
    else
    {
        m_end.step_scale = step_scale.toFloat();
    }
}

void AItems :: SetColorMultiColor( float bound,QString color){

    colorMultiColor.append(color);
    boundMultiColor.append(bound);

}

void AItems:: SetBruchColor(QString bruchColor)
{
    m_brushColor = bruchColor;
}


void AItems :: SetMultiColorCount(int multiColorCount)
{
    m_multiColorCount = multiColorCount;
}
 void AItems:: SetTransparentColor(QString transparentColor)
 {
     m_transparentColor = transparentColor;
 }
void AItems::SetShowMode(float show_mode)
{
   m_show_mode = show_mode;
}
void AItems :: SetWidth(QString value, QString unit)
{
    value = value.replace(",",".");
    m_value = value.toFloat();
}
void AItems::SetBegin(float set_begin_value,float begin_value)
{
    m_begin.setBeginValue = set_begin_value;
    m_begin.beginValue = begin_value;
}
void AItems::SetZeroOfset(QString value, QString unit)
{

    value = value.replace(",",".");
    if(unit=="CM")
    {
        m_zero.value = value.toFloat()*10;
    }
    else
    {
       m_zero.value = value.toFloat();
    }
}
void AItems::SetEnd(float set_end_value,float end_value)
{
   m_end.setEndValue = set_end_value;
   m_end.endValue = end_value;

}
void AItems::SetValueScale(QString value, QString unit)
{

    value = value.replace(",",".");
    if(unit=="CM")
    {
        m_value_scale.value = value.toFloat()*10;
    }
    else
    {
         m_value_scale.value = value.toFloat();
    }
}
void AItems :: SetTrueAcu(bool acu)
{
    m_acu = acu;
}
void AItems :: SetTrueMark(bool mark)
{
    m_mark = mark;
}
void AItems :: SetTrueLine(bool line)
{
    m_line = line;
}
void AItems::SetMultiScale(float is_multi_scale,float gleamCount, float gleamScale)
{
    m_multi_scale.isMultiScale = is_multi_scale;
    m_multi_scale.gleamCount = gleamCount;
    m_multi_scale.gleamScale = gleamScale;
}
QString AItems :: getLineName()
{
    return m_name;
}
QString AItems :: getColorMultiColor(int i)
{
    return colorMultiColor[i];
}
float AItems :: getBoundMultiColor(int i)
{
    return boundMultiColor[i];
}
