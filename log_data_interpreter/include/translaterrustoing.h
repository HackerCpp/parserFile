#ifndef TRANSLATERRUSTOING_H
#define TRANSLATERRUSTOING_H
#include <QString>
#include <QHash>

class TranslaterRusToIng
{
    static QHash<QString,QString> f_dictionary;

    public:

    TranslaterRusToIng();

    QString translate(QString string);
};

#endif // TRANSLATERRUSTOING_H
