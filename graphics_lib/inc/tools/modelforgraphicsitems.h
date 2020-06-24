#ifndef MODELFORGRAPHICSITEMS_H
#define MODELFORGRAPHICSITEMS_H
#include "agraphicitem.h"

class ModelForGraphicsItems : public QAbstractListModel
{
    QVector<AGraphicItem *> *m_items;
    QStringList m_headerList;
public:
    ModelForGraphicsItems(QMap<QString,AGraphicItem *> *items);
    ~ModelForGraphicsItems()override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;

    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole)override;
};

#endif // MODELFORGRAPHICSITEMS_H
