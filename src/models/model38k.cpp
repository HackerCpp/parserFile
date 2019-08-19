#include "inc/models/model38k.h"


Model38k::Model38k(QList<PacketModulesData38k> *modulesData){
    this->modulesData = new QList<PacketModulesData38k>;
    parserModules = nullptr;
    size = 0;
    if(modulesData == nullptr)
        return;

    for (auto modData = modulesData->begin();modData < modulesData->end();modData++){
        this->modulesData->push_back(*modData);
    }
    size = modulesData->size();
}

QVariant Model38k::data(const QModelIndex &index, int role ) const{
    if (role != Qt::DisplayRole)
        return QVariant();
    if (!index.isValid())
        return QVariant();
    if (index.row() >= size)
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
    return size;
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

 void Model38k::setData(PacketModulesData38k pack){
    beginInsertRows(QModelIndex(),size, size);
    this->modulesData->push_back(pack);
    size++;
    endInsertRows();
}
 void Model38k::startParsingMdules(){
     parserModules = new Parser38kModules(this->modulesData);
     connect(parserModules, SIGNAL(finished(void)), this, SLOT(stopParsingMdules(void)));
     parserModules->start();
 }
 void Model38k::stopParsingMdules(){
     if(parserModules)
        parserModules->stop();
     parserModules = nullptr;
 }
Model38k::~Model38k(){
    if(parserModules)
        parserModules->stop();
    parserModules = nullptr;
    delete this->modulesData;
    this->modulesData = nullptr;
}


