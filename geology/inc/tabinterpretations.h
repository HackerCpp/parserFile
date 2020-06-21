#ifndef TABINTERPRETATIONS_H
#define TABINTERPRETATIONS_H

#include "basesettingswindow.h"
#include <QDir>
#include <QAbstractListModel>

struct Interpretation{
    bool isActive;
    QString name;
    QString version;
    QString absoluteFilePath;

};

class ModelForTabInterpretation : public QAbstractListModel
{
    QList<Interpretation*> *m_listInterpretation;
    QStringList m_headerList;

public:
    ModelForTabInterpretation(QList<Interpretation*> *m_listInterpretation);
    ~ModelForTabInterpretation();

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;

    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole)override;

    QString getActiveFilePath();
};
/*********************************************************************************************************/
class TabInterpretations : public BaseSettingsWindow
{
    bool m_isClose;
    bool m_isApply;
public:
    TabInterpretations(){}
    TabInterpretations(QFileInfoList fileInfolist);
    ~TabInterpretations(){}
    QString getAbsolutePath(QFileInfoList fileInfolist);
public slots:
    void cansel()override;
    void apply()override;
};

#endif // TABINTERPRETATIONS_H
