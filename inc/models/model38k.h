#ifndef MODEL38K_H
#define MODEL38K_H

#include "inc/parsers/parser38k.h"
#include <QAbstractListModel>
#include <QSortFilterProxyModel>
#include <QCoreApplication>

class ProxyModel38k : public QSortFilterProxyModel{
public:
    ProxyModel38k();
    bool filterAcceptsRow(int source_row, const QModelIndex &source_parent) const;
    bool filterAcceptsColumn(int source_column, const QModelIndex &source_parent) const;
};

class Model38k : public QAbstractListModel{
    Q_OBJECT

    QString headerArray[12] = {"MOD ADDR(0)","DATA STAT(1)","SIZE OLL(2)","SIZE DATA(3)",
                              "TOTAL PARTS(4)","CURRENT PART(5)",
                              "COM STAT(6)","COM COUNTER(7)","COM CRC(8)","COM CODE(9)",
                              "REQ TIME(10)","DATA(11)"};
    QList<PacketModulesData38k> *modulesData;
public:
    Model38k(QList<PacketModulesData38k> *modulesData);
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const ;
    int columnCount(const QModelIndex &parent = QModelIndex()) const ;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
    void sort(int column, Qt::SortOrder order = Qt::AscendingOrder);
    void setData(PacketModulesData38k pack);
    ~Model38k();

};

#endif // MODEL38K_H
