#include "inc/models/model38k.h"

ProxyModel38k::ProxyModel38k(){

}

bool ProxyModel38k::filterAcceptsRow(int source_row, const QModelIndex &source_parent) const{
    QModelIndex index = sourceModel()->index(source_row, filterKeyColumn(), source_parent);
    if(sourceModel()->data(index).toString().contains(filterRegExp()))
        return true;
    return false;
}

bool ProxyModel38k::filterAcceptsColumn(int source_column, const QModelIndex &source_parent) const{

}





Model38k::Model38k(QList<PacketModulesData38k> *modulesData){
    this->modulesData = new QList<PacketModulesData38k>;
    if(modulesData == nullptr)
        return;

    for (auto modData = modulesData->begin();modData < modulesData->end();modData++){
        this->modulesData->push_back(*modData);
    }
}

QVariant Model38k::data(const QModelIndex &index, int role ) const{
    if (role != Qt::DisplayRole)
        return QVariant();
    if (!index.isValid())
        return QVariant();
    if (index.row() >= this->modulesData->size())
        return QVariant();
    int column = index.column();
    switch (column){
         case 0:
             return this->modulesData->at(index.row()).header.moduleAddress;
         case 1:
             return this->modulesData->at(index.row()).header.data_state;
         case 2:
             return this->modulesData->at(index.row()).header.totalSize;
         case 3:
             return this->modulesData->at(index.row()).header.totalDataSize;
         case 4:
             return modulesData->at(index.row()).header.totalParts;
         case 5:
             return modulesData->at(index.row()).header.currentPartNo;
         case 6:
            return modulesData->at(index.row()).header.lastCommandState;
        case 7:
            return modulesData->at(index.row()).header.commandCounter;
        case 8:
            return modulesData->at(index.row()).header.lastCommandCrc;
        case 9:
            return modulesData->at(index.row()).header.lastCommandCode;
        case 10:
            return modulesData->at(index.row()).header.requestTime;
        case 11:
            return modulesData->at(index.row()).data;
         default:
             return QVariant();
      }
}

int Model38k::rowCount(const QModelIndex &parent) const {
    int row = this->modulesData->size();
    return row;
}

int Model38k::columnCount(const QModelIndex &parent) const {
    return 12;
}

QVariant Model38k::headerData(int section, Qt::Orientation orientation, int role) const{
    if (role != Qt::DisplayRole)
       return QVariant();
    if (orientation == Qt::Horizontal){
        return headerArray[section];
    }
    else if(orientation == Qt::Vertical)
        return section;
    return QVariant();
}

Qt::ItemFlags Model38k::flags(const QModelIndex &index) const{
    return Qt :: ItemIsEnabled | Qt :: ItemIsSelectable | Qt :: ItemNeverHasChildren;
}

void Model38k::sort(int column, Qt::SortOrder order){
    if(column == 0 && order == Qt::AscendingOrder ){

    }
}

 void Model38k::setData(PacketModulesData38k pack){
    beginInsertRows(QModelIndex(), modulesData->size(), modulesData->size());
    this->modulesData->push_back(pack);
    endInsertRows();
}

Model38k::~Model38k(){
    delete this->modulesData;
    this->modulesData = nullptr;
}


