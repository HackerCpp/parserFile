#include "markItem.h"


markItem :: markItem()
{

}
markItem :: ~markItem()
{

}
void markItem::setColor(QString color, bool isDashes)
{
    m_color = color;
    m_isDashes = isDashes;
}
void markItem::setWidth(unsigned int width)
{
    m_widthLine = width;
}
void markItem::setValueScale(qreal valueScale)
{
    m_valueScale = valueScale;
}


qreal markItem::valueScale()
{
    return m_valueScale;
}
QString markItem::color()
{
    return m_color;
}
bool markItem:: isDashes()
{
    return m_isDashes;
}
unsigned int markItem::widthLine()
{
    return m_widthLine;
}
