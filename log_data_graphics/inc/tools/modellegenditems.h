#ifndef MODELLEGENDITEMS_H
#define MODELLEGENDITEMS_H
#include <QAbstractListModel>
#include "agraphicitem.h"

class ModelLegendItems : public QAbstractListModel
{
    Q_OBJECT
    QList<AGraphicItem *> *m_items;
    QVector<AGraphicItem *> m_visibleItems;
    QStringList m_headerList;
    QPointF m_beginPoint, m_currentPoint;


public:
    ModelLegendItems(QList<AGraphicItem *> *items);
    ~ModelLegendItems()override;

    void updateVisibleItems();
    void setBeginPoint(QPointF beginPoint);
    void setCurrentPoint(QPointF currentPoint);

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;
};

#endif // MODELLEGENDITEMS_H
