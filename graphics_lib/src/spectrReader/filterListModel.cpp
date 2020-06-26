#include "filterListModel.h"
#include <QItemDelegate>

FilterListModel::FilterListModel()
{
    m_vectorFilters = new QVector<QPair<QString, QString> >;
    m_headerList << "Filter set :";
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
           return m_vectorFilters->at(index.row()).first;

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
    return 1;
}

QVariant FilterListModel::headerData(int section, Qt::Orientation orientation, int role) const {

    if (role != Qt::DisplayRole)
       return QVariant();
    if (orientation == Qt::Horizontal && section < m_headerList.size()){
        return m_headerList[section];
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
             return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemNeverHasChildren;
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
               m_vectorFilters->operator[](index.row()).first = value.toString();
               return true;
            }
            default:
                return false;
        }
    }
    else
        return false;
}

void FilterListModel::insertFilter(QPair<QString, QString> newFilter){
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


