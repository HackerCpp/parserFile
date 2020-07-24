#include "filterListModel.h"
#include <QItemDelegate>
#include <QString>

FilterListModel::FilterListModel()
{
    m_vectorFilters = new QVector<FilterInfo >;
    m_headerList << QT_TR_NOOP("Filter name :") << QT_TR_NOOP("left") << QT_TR_NOOP("right") << QT_TR_NOOP("up") << QT_TR_NOOP("down")
                 << QT_TR_NOOP("param1") << QT_TR_NOOP("param2") << QT_TR_NOOP("param3");
}


FilterListModel::~FilterListModel(){

}

QVariant FilterListModel::data(const QModelIndex &index, int role )const{

    if (!index.isValid())
        return QVariant();
    if (index.row() >= m_vectorFilters->size())
        return QVariant();
    int column = index.column();
    if (role == Qt::DisplayRole){
    switch (column){
        case 0:
           return m_vectorFilters->at(index.row()).name;
        case 1:
           return m_vectorFilters->at(index.row()).left;
        case 2:
           return m_vectorFilters->at(index.row()).right;
        case 3:
           return m_vectorFilters->at(index.row()).up;
        case 4:
           return m_vectorFilters->at(index.row()).down;
        case 5:
           return m_vectorFilters->at(index.row()).param1;
        case 6:
           return m_vectorFilters->at(index.row()).param2;
        case 7:
           return m_vectorFilters->at(index.row()).param3;
        default:
            return QVariant();
      }
    }
    else if(role == Qt::ForegroundRole){
           return QVariant();//this->m_items->at(index.row())->color();
    }
    else if(role == Qt::FontRole){
           return QFont("Times", 12, QFont::Bold);
    }
    else
        return QVariant();
}

int FilterListModel::rowCount(const QModelIndex &parent)const{
    Q_UNUSED(parent)
    return m_vectorFilters->size();
}

int FilterListModel::columnCount(const QModelIndex &parent) const {
    Q_UNUSED(parent)
    return m_headerList.size();
}

QVariant FilterListModel::headerData(int section, Qt::Orientation orientation, int role) const {

    if (role != Qt::DisplayRole)
       return QVariant();
    if (orientation == Qt::Horizontal && section < m_headerList.size()){
        return tr(m_headerList[section].toLatin1());
    }
    else if(orientation == Qt::Vertical)
        return section;
    return QVariant();
}

Qt::ItemFlags FilterListModel::flags(const QModelIndex &index) const {
    if (!index.isValid())
        return false;
    if (index.row() >= m_vectorFilters->size())
        return false;
    int column = index.column();
    switch (column){
         case 0:{
            return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemNeverHasChildren;
         }
         default:
             return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemNeverHasChildren | Qt::ItemIsEditable;
      }
}

bool FilterListModel::setData(const QModelIndex &index, const QVariant &value, int role){
    if (!index.isValid())
        return false;
    if (index.row() >= m_vectorFilters->size())
        return false;
    int column = index.column();
    if (role == Qt::EditRole){
        switch (column){
            case 0:{
               m_vectorFilters->operator[](index.row()).name = value.toString();
               return true;
            }
            case 1:{
               m_vectorFilters->operator[](index.row()).left = value.toDouble();
               return true;
            }
            case 2:{
               m_vectorFilters->operator[](index.row()).right = value.toDouble();
               return true;
            }
            case 3:{
               m_vectorFilters->operator[](index.row()).up = value.toDouble();
               return true;
            }
            case 4:{
               m_vectorFilters->operator[](index.row()).down = value.toDouble();
               return true;
            }
            case 5:{
               m_vectorFilters->operator[](index.row()).param1 = value.toDouble();
               return true;
            }
            case 6:{
               m_vectorFilters->operator[](index.row()).param2 = value.toDouble();
               return true;
            }
            case 7:{
               m_vectorFilters->operator[](index.row()).param3 = value.toDouble();
               return true;
            }
            default:
                return false;
        }
    }
    else
        return false;
}

void FilterListModel::insertFilter(FilterInfo newFilter){
    if(m_vectorFilters){
       beginInsertRows(QModelIndex(),m_vectorFilters->size(), m_vectorFilters->size());
       m_vectorFilters->push_back(newFilter);
       endInsertRows();
    }
}

void FilterListModel::removeFilter(int index){
    if(m_vectorFilters){
       beginRemoveRows(QModelIndex(),m_vectorFilters->size() - 1,m_vectorFilters->size() - 1);
       m_vectorFilters->remove(index);
       endRemoveRows();
    }
}


