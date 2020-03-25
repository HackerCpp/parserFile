#ifndef LINEITEM_H
#define LINEITEM_H
#include "aitem.h"



class  LineItem : public AItem{
QString m_color;
unsigned int m_widthLine;
bool m_isDashes;

QString m_paintMode;
public:

LineItem();
~LineItem();

void setColor(QString color, bool isDashes);
void setPaintMode(QString paintMode);
void setWidth(unsigned int width);

QString color();
QString paintMode();
bool isDashes();
unsigned int widthLine();

};
#endif // LINEITEM_H
