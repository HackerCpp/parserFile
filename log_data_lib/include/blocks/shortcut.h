#ifndef SHORTCUT_H
#define SHORTCUT_H
#include <QVariant>

class ShortCut{
    QString m_ref;
    QString m_name;
    QString m_nameWithoutNumber;
public:
    ShortCut();
    void setRef(QString ref);
    void setName(QString name);
    QString Ref();
    QString Name();
    QString NameWithoutNumber();
};

#endif // SHORTCUT_H
