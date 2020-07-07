#include "modelonewave.h"
#include <QDebug>

ModelOneWave::ModelOneWave()
{

    m_listVaweInfo = new QList<OneWaveInfo>;
    m_headerList << "Visible" << "Name" << "Color" << "Amp. Max"
                 << "Amp. Min" << "Band" << "Frequency" << "Amplitude";
    m_listVaweInfo->push_back(OneWaveInfo{new QLineSeries,false,"Difference","#000000",0,0,0,0,0});

}


QVariant ModelOneWave::data(const QModelIndex &index, int role )const{

    if (!index.isValid())
        return QVariant();
    if (index.row() >= m_listVaweInfo->size())
        return QVariant();
    int column = index.column();
    if (role == Qt::DisplayRole){
    switch (column){
        case 0:
           return m_listVaweInfo->at(index.row()).isVisible;
        case 1:
            return m_listVaweInfo->at(index.row()).name;
        case 2:
           return m_listVaweInfo->at(index.row()).color;
        case 3:
           return m_listVaweInfo->at(index.row()).amplitudeMaximum;
        case 4:
           return m_listVaweInfo->at(index.row()).amplitudeMinimum;
        case 5:
           return m_listVaweInfo->at(index.row()).currentBand;
        case 6:
           return m_listVaweInfo->at(index.row()).currentFrequency;
        case 7:
           return m_listVaweInfo->at(index.row()).currentAmplitude;

        default:
            return QVariant();
      }
    }
    else if(role == Qt::ForegroundRole){
           return QVariant();//this->m_items->at(index.row())->color();
    }
    else if(role == Qt::FontRole){
           return QVariant();//QFont("Times", 12, QFont::Bold);
    }
    else
        return QVariant();
}

int ModelOneWave::rowCount(const QModelIndex &parent)const{
    Q_UNUSED(parent)
    return m_listVaweInfo->size();
}

int ModelOneWave::columnCount(const QModelIndex &parent) const {
    Q_UNUSED(parent)
    return 8;
}

QVariant ModelOneWave::headerData(int section, Qt::Orientation orientation, int role) const {

    if (role != Qt::DisplayRole)
       return QVariant();
    if (orientation == Qt::Horizontal && section < m_headerList.size()){
        return m_headerList[section];
    }
    else if(orientation == Qt::Vertical)
        return section;
    return QVariant();
}

Qt::ItemFlags ModelOneWave::flags(const QModelIndex &index) const {
    if (!index.isValid())
        return false;
    if (index.row() >= m_listVaweInfo->size())
        return false;
    int column = index.column();
    switch (column){
        case 0:{
            return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemNeverHasChildren | Qt::ItemIsEditable;
        }
        case 2:{
           return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemNeverHasChildren | Qt::ItemIsEditable;
        }
        default:
            return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemNeverHasChildren;
    }
}

bool ModelOneWave::setData(const QModelIndex &index, const QVariant &value, int role){
    if (!index.isValid())
        return false;
    if (index.row() >= m_listVaweInfo->size())
        return false;
    int column = index.column();
    if (role == Qt::EditRole){
        switch (column){
            case 0:{
               m_listVaweInfo->operator[](index.row()).isVisible = value.toBool();
               if(m_listVaweInfo->operator[](index.row()).isVisible)
                    m_listVaweInfo->operator[](index.row()).lineSeries->show();
               else
                    m_listVaweInfo->operator[](index.row()).lineSeries->hide();
               return true;
            }
            case 2:{
               m_listVaweInfo->operator[](index.row()).color = value.toString();
               QPen f_pen(m_listVaweInfo->operator[](index.row()).color);
               f_pen.setWidth(2);
               m_listVaweInfo->operator[](index.row()).lineSeries->setPen(f_pen);
               return true;
            }
            default:
                return false;
        }
    }
    else
        return false;
}

void ModelOneWave::insertWaveInfo(OneWaveInfo waveInfo){
    if(m_listVaweInfo){
       beginInsertRows(QModelIndex(),m_listVaweInfo->size(), m_listVaweInfo->size());
       m_listVaweInfo->push_front(waveInfo);
       endInsertRows();
    }
}

void ModelOneWave::changeCurentPosition(QPointF pointPosition){
    //foreach(auto vaweInfo,*m_listVaweInfo){//vaweInfo копированием потому что не указатель
    for(int i = 0; i < m_listVaweInfo->size() - 1; ++i){
        int f_band = 0;
        foreach(auto series,m_listVaweInfo->operator[](i).lineSeries->points()){
            if(series.x() >= pointPosition.x()){
                m_listVaweInfo->operator[](i).currentAmplitude = series.y();
                m_listVaweInfo->operator[](i).currentBand = f_band;
                m_listVaweInfo->operator[](i).currentFrequency = series.x();
                break;
            }
            ++f_band;
        }
    }
    qreal f_amplOne = 0,f_amplTwo = 0;
    bool f_amplitudeSearchFlag = false;
    foreach(auto vaweInfo,*m_listVaweInfo){
        if(vaweInfo.isVisible && !f_amplitudeSearchFlag){
            f_amplOne = vaweInfo.currentAmplitude;
            f_amplitudeSearchFlag = true;
        }
        else if(vaweInfo.isVisible){
            m_listVaweInfo->operator[](m_listVaweInfo->size() - 1).currentAmplitude = (vaweInfo.currentAmplitude - f_amplOne);
            break;
        }
    }

    emit dataChanged(index(0,3),index(m_listVaweInfo->size(),8));
}
