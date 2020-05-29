#ifndef MARKITEM_H
#define MARKITEM_H
#include "aitem.h"


class markItem : public AItem{
    QString m_color;
    unsigned int m_widthLine;
    bool m_isDashes;
    qreal m_valueScale;
public:
    markItem();
    ~markItem();

    void setColor(QString color, bool isDashes);
    void setWidth(unsigned int width);
    void setValueScale(qreal valueScale);

    qreal valueScale();
    QString color();
    bool isDashes();
    unsigned int widthLine();

};




#endif // MARKITEM_H
