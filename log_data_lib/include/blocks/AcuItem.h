#ifndef ACUITEM_H
#define ACUITEM_H
#include "aitem.h"


class AcuItem : public AItem{
    QString m_brushColor;
    QString m_transparentColor;
    QList<MulticolorItem> *m_multicolor;
    unsigned int  m_showMode;
    int m_levelCount;
public:

    AcuItem();
    AcuItem(const AcuItem &other);
    ~AcuItem();

    void setBrushColor(QString brushColor){m_brushColor = brushColor;}
    void setTransparentColor(QString transparentColor){m_transparentColor = transparentColor;}
    void setMulticolor(MulticolorItem multicolor);
    void setShowMode(unsigned int showMode);
    void setLevelCount(int levelCount);



    QString bruchColor();
    QString transparentColor();
    unsigned  int showMode();
    int levelCount();
    QList<MulticolorItem> *multiColor();

};


#endif // ACUITEM_H
