#ifndef MODELONEWAVE_H
#define MODELONEWAVE_H
#include <QString>
#include <QList>
#include <QAbstractListModel>
#include <QLineSeries>

using namespace QtCharts;

struct OneWaveInfo{
    QLineSeries *lineSeries;
    bool isVisible;
    QString name;
    QString color;
    qreal amplitudeMaximum;
    qreal amplitudeMinimum;
    qreal currentBand;
    qreal currentFrequency;
    qreal currentAmplitude;
};

class ModelOneWave : public QAbstractListModel
{
    Q_OBJECT
    QList<OneWaveInfo> *m_listVaweInfo;
    QStringList m_headerList;
    QPair<qreal,qreal> m_maximumAndMinimum;
public:
    ModelOneWave();
    ~ModelOneWave()override{}

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role)override;

    void insertWaveInfo(OneWaveInfo waveInfo);
    void changeCurentPosition(QPointF pointPosition);
    qreal delta(){if(m_listVaweInfo && m_listVaweInfo->size()){return m_listVaweInfo->at(m_listVaweInfo->size() - 1).currentAmplitude;}return 0; }
    qreal band(){if(m_listVaweInfo && m_listVaweInfo->size()){return m_listVaweInfo->first().currentBand;}return 0;}
    qreal frequency(){if(m_listVaweInfo && m_listVaweInfo->size()){return m_listVaweInfo->first().currentFrequency;}return 0;}
    qreal maximum(){return m_maximumAndMinimum.first;}
    qreal minimum(){return m_maximumAndMinimum.second;}
    QPair<qreal,qreal> calcMaximumAndMinimum();
};

#endif // MODELONEWAVE_H
