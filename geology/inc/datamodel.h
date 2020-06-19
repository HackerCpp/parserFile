#ifndef DATAMODEL_H
#define DATAMODEL_H
#include <QAbstractItemModel>
#include "ilogdata.h"
#include <QList>
#include "datablock.h"



class DataModel : public  QAbstractItemModel
{

    QVector<QSharedPointer<ILogData> > *m_logDataVector;
    ILogData *m_curentLogData;

public:
    DataModel();
    ~DataModel() override;

    void addLogData(QSharedPointer<ILogData> logData);
    void removeLogData(QSharedPointer<ILogData> logData);
    QVector<QSharedPointer<ILogData> > *logDataVector(){return m_logDataVector;}
    void update();

    QModelIndex index(int row, int column, const QModelIndex &parent) const override;
    QModelIndex parent(const QModelIndex &child) const override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    bool deleteBlock(IBlock *block);

    void setCurentLogData(ILogData *logData){m_curentLogData = logData;}
    ILogData *curentLogData(){return m_curentLogData;}
};

#endif // DATAMODEL_H
