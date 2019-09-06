#ifndef MODEL38K_H
#define MODEL38K_H

#include "inc/parsers/parser38k.h"
#include <QAbstractListModel>
#include <QSortFilterProxyModel>
#include <QCoreApplication>
#include <QHBoxLayout>
#include <QComboBox>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

class SaveCSVModal : public QWidget{
    Q_OBJECT
    QHBoxLayout *horBoxLayout;
    QVBoxLayout * vBoxLayoutType;
    QVBoxLayout * vBoxLayoutSeparator;
    QLabel *labelType;
    QLabel *labelSeparator;
    QComboBox *comboBox;
    QLineEdit *lineEdit;
    QPushButton *btnOk;
    QPushButton *btnCansel;
    QList<PacketModulesData38k> * m_data;
    QVector<QString> modArray = {"GKT","SHM","AG","MP","AMDS","GKTSHM","P04","P02","GVK","NNKt","GGP"};
public:
    SaveCSVModal(QList<PacketModulesData38k> * data);
    ~SaveCSVModal();
public slots:
    void saveFile();
    void cansel();

};


class Model38k : public QAbstractListModel{

    Q_OBJECT

    QString headerArray[12] = {"MOD ADDR(0)","DATA STAT(1)","SIZE OLL(2)","SIZE DATA(3)",
                              "TOTAL PARTS(4)","CURRENT PART(5)",
                              "COM STAT(6)","COM COUNTER(7)","COM CRC(8)","COM CODE(9)",
                              "REQ TIME(10)","DATA(11)"};
    QList<PacketModulesData38k> *modulesData;
    Parser38kModules *parserModules;
    int size;
public:
    Model38k(QList<PacketModulesData38k> *modulesData);
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const ;
    int columnCount(const QModelIndex &parent = QModelIndex()) const ;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
    void setData(PacketModulesData38k pack);
    void startParsingMdules();
    void saveFile();
    QList<PacketModulesData38k> *getData(){return modulesData;}
    ~Model38k();
public slots:
    void stopParsingMdules();

};

#endif // MODEL38K_H
