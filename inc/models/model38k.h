#ifndef MODEL38K_H
#define MODEL38K_H

#include "inc/parsers/parser38k.h"
#include <QAbstractListModel>

class Model38k : public QAbstractListModel{
    Q_OBJECT

    QString headerArray[12] = {"MOD ADDR","DATA STAT","SIZE OLL","SIZE DATA",
                              "TOTAL PARTS","CURRENT PART",
                              "COM STAT","COM COUNTER","COM CRC","COM CODE",
                              "REQ TIME","DATA"};
    QList<PacketModulesData38k> *modulesData;
public:
    Model38k(QList<PacketModulesData38k> *modulesData);
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const ;
    int columnCount(const QModelIndex &parent = QModelIndex()) const ;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
};

#endif // MODEL38K_H
