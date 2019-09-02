#ifndef CSV_H
#define CSV_H

#include "QList"
#include "inc/parsers/parser38k.h"

class CSV{
    QString path;
public:
    CSV(QList<QString> header,QList<QList<QString>> data);
    CSV(QList<PacketModulesData38k> *modulesData38k,ushort type);
};

#endif // CSV_H
