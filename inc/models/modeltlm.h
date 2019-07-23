#ifndef MODELTLM_H
#define MODELTLM_H

#include <QAbstractItemModel>
#include "inc/parsers/parsertlm.h"

struct Data{
    QString name;
    Data* par;
    Data* child;
};


class ModelTlm : public  QAbstractItemModel{

    QList<Data> *m_tlmBlocks;

public:
    ModelTlm(QObject *parent = Q_NULLPTR);
    virtual QModelIndex index(int row, int column, const QModelIndex &parent) const;
    virtual QModelIndex parent(const QModelIndex &child) const;
    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const;
    virtual int columnCount(const QModelIndex &parent = QModelIndex()) const;
    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
};

#endif // MODELTLM_H
