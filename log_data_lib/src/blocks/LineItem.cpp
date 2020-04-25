#include "lineItem.h"

LineItem :: LineItem()
{

}
LineItem :: ~LineItem()
{

}
void LineItem::setColor(QString color, bool isDashes)
{
    m_color = color;
    m_isDashes = isDashes;
}
void LineItem::setWidth(unsigned int width)
{
    m_widthLine = width;
}
void LineItem :: setPaintMode(QString paintMode)
{
    m_paintMode = paintMode;
}


QString LineItem :: paintMode()
{
    return m_paintMode;
}

QString LineItem::color()
{
    return m_color;
}
bool LineItem:: isDashes()
{
    return m_isDashes;
}
unsigned int LineItem::widthLine()
{
    return m_widthLine;
}
