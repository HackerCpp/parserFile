#ifndef MODELCURVEEDITOR_H
#define MODELCURVEEDITOR_H

#include <QAbstractListModel>
#include "agraphicitem.h"

class ModelCurveEditor : public QAbstractListModel{
    Q_OBJECT
    QVector<qreal> *m_vector;
    ICurve *m_curve;
    ICurve *m_time;
    ICurve *m_depth;
public:
    ModelCurveEditor(AGraphicItem *graphicItem);
    ~ModelCurveEditor()override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;

    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole)override;

    void apply();
};

#endif // MODELCURVEEDITOR_H
