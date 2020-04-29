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
    QString ref();
    QString name();
    QString nameWithoutNumber();
    QString dateTime();
    QString device();
};

#endif // SHORTCUT_H
