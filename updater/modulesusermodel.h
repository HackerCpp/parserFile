#ifndef MODULESUSERMODEL_H
#define MODULESUSERMODEL_H


#include <QAbstractItemModel>
#include "module.h"
#include <QStringList>

class ModulesUserModel : public QAbstractItemModel
{
    QVector<Module*> *m_modules;
    QStringList m_headerList;
public:
    ModulesUserModel();

    QModelIndex index(int row, int column, const QModelIndex &parent) const override;
    QModelIndex parent(const QModelIndex &child) const override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    void setModules(QVector<Module*> *modules){QAbstractItemModel::beginResetModel();m_modules = modules;QAbstractItemModel::endResetModel();}
    void update(){QAbstractItemModel::beginResetModel();QAbstractItemModel::endResetModel();}
};


#endif // MODULESUSERMODEL_H
