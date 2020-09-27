#ifndef MODULESMODEL_H
#define MODULESMODEL_H
#include <QAbstractItemModel>
#include "module.h"

class ModulesModel : public QAbstractItemModel
{
    QVector<Module*> *m_modules;
public:
    ModulesModel();

    QModelIndex index(int row, int column, const QModelIndex &parent) const override;
    QModelIndex parent(const QModelIndex &child) const override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    void setModules(QVector<Module*> *modules){QAbstractItemModel::beginResetModel();m_modules = modules;QAbstractItemModel::endResetModel();}
    void update(){QAbstractItemModel::beginResetModel();QAbstractItemModel::endResetModel();}
};

#endif // MODULESMODEL_H
