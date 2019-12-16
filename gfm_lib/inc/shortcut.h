#ifndef SHORTCUT_H
#define SHORTCUT_H
#include <QVariant>

class ShortCut{
    QString m_ref;
    QString m_name;
public:
    ShortCut();
    void setRef(QString ref);
    void setName(QString name);
    QString getRef();
    QString getName();
};

#endif // SHORTCUT_H
