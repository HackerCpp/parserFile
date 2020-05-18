#ifndef DATAMODEL_H
#define DATAMODEL_H
#include <QAbstractItemModel>
#include "ilogdata.h"
#include <QList>
#include "datablock.h"



class DataModel : public  QAbstractItemModel
{
    QVector<DataBlock*> *m_dataBlocks;
    QVector<QSharedPointer<ILogData> > *m_logDataVector;

public:
    DataModel();
    ~DataModel() override;

    void addLogData(QSharedPointer<ILogData> logData);

    QModelIndex index(int row, int column, const QModelIndex &parent) const override;
    QModelIndex parent(const QModelIndex &child) const override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
};

#endif // DATAMODEL_H
