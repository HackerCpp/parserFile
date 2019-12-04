#ifndef MODELTLM_H
#define MODELTLM_H

#include <QAbstractItemModel>
#include "inc/parsers/parsertlm.h"
#include <QVector>

struct TlmBlockData;
struct ParentsTlm{
    bool par = 0;
};
struct TlmPackData : public ParentsTlm{
    TlmPack data;
    TlmBlockData* parent = nullptr;
};
struct TlmBlockData : public ParentsTlm{
    QString name;
    QString bom;
    QVector<TlmPackData> *dataArray;
};

class ModelTlm : public  QAbstractItemModel{
    QString headerArray[7] = {"ID","STATUS","LENGTH","TIME","DEVICE","INF","DATA"};
    QVector<TlmBlockData> *m_tlmBlocks;
public:
    ModelTlm(QList<BlockTlm> *tlmBlocks,QObject *parent = Q_NULLPTR);
    QModelIndex index(int row, int column, const QModelIndex &parent) const;
    QModelIndex parent(const QModelIndex &child) const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
};

#endif // MODELTLM_H
