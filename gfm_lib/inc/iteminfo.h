#ifndef ITEMINFO_H
#define ITEMINFO_H
#include <QDomNode>
#include <QColor>


class ItemInfo{
    QDomNode *m_xmlItemInfo;
    QDomNode *m_style;
public:
    ItemInfo(QDomNode *xmlItemInfo);
    QString name();
    QColor color();
    int widthLine();
    ~ItemInfo();
};

#endif // ITEMINFO_H
