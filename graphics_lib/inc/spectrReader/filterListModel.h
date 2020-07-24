#ifndef FILTER_MODEL_H
#define FILTER_MODEL_H
#include <QAbstractListModel>
#include "agraphicitem.h"

struct FilterInfo{
    QString name;
    qreal left;
    qreal right;
    qreal up;
    qreal down;
    qreal param1;
    qreal param2;
    qreal param3;
    QString path;
};

class FilterListModel : public QAbstractListModel{
    Q_OBJECT
    QVector<FilterInfo > *m_vectorFilters;
    QStringList m_headerList;
    public:
    FilterListModel();
    ~FilterListModel()override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;

    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole)override;

    void insertFilter(FilterInfo newFilter);
    void removeFilter(int index);
    QVector<FilterInfo > *filters(){return m_vectorFilters;}

};

#endif
