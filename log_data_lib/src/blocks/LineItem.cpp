#include "lineItem.h"

LineItem::LineItem()
{
    m_type = LINE;
    m_color = "#ff" + QString::number((rand() % 200) + 50,16)
                   + QString::number((rand() % 200) + 50,16)
                   + QString::number((rand() % 200) + 50,16);

    m_widthLine = 2;
    m_isDashes = false;
}

LineItem::LineItem(const LineItem &other)
    : AItem(other){
    m_type = LINE;
    m_color = other.m_color;
    m_widthLine = other.m_widthLine;
    m_isDashes = other.m_isDashes;
    m_paintMode = other.m_paintMode;
}

LineItem::~LineItem()
{

}

void LineItem::setColor(QString color, bool isDashes){
    m_color = color;
    m_isDashes = isDashes;
}

void LineItem::setWidth(unsigned int width)
{
    m_widthLine = width;
}
void LineItem::setPaintMode(QString paintMode)
{
    m_paintMode = paintMode;
}


QString LineItem::paintMode()
{
    return m_paintMode;
}

QString LineItem::color()
{
    return m_color;
}

bool LineItem::isDashes()
{
    return m_isDashes;
}
unsigned int LineItem::widthLine()
{
    return m_widthLine;
}
