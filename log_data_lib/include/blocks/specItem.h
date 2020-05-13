#ifndef SPECITEM_H
#define SPECITEM_H

#endif // SPECITEM_H
#include "aitem.h"

class SpecItem : public AItem{
    QString m_brushColor;
    QString m_transparentColor;
    QList<MulticolorItem> *m_multicolor;
    unsigned int  m_showMode;
    int m_levelCount;
public:

    SpecItem();
    ~SpecItem();

    void setColor (QString bruchColor, QString transparentColor);
    void setMulticolor(MulticolorItem multicolor);
    void setShowMode(unsigned int showMode);
    void setLevelCount(int levelCount);



    QString bruchColor();
    QString transparentColor();
    unsigned  int showMode();
    int levelCount();
    QList<MulticolorItem> *multiColor();

};
