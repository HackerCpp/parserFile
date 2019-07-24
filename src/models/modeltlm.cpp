#include "inc/models/modeltlm.h"
#include <QMessageBox>

ModelTlm::ModelTlm(QList<BlockTlm> *tlmBlocks,QObject *parent)
    : QAbstractItemModel(parent){
    this->m_tlmBlocks = new QVector<TlmBlockData>(2);
    for(int blockId = 0;blockId < tlmBlocks->size();blockId++){
        m_tlmBlocks->data()[blockId].dataArray = new QVector<TlmPackData>;
        m_tlmBlocks->data()[blockId].bom = tlmBlocks->at(blockId).boom;
        m_tlmBlocks->data()[blockId].name = tlmBlocks->at(blockId).name;
        m_tlmBlocks->data()[blockId].par = 1;
        for(int packId = 0;packId < tlmBlocks->at(blockId).TlmPackList.size();packId++){
            TlmPackData packData;
            packData.par = 0;
            packData.parent = &m_tlmBlocks->data()[blockId];
            packData.data.state = tlmBlocks->at(blockId).TlmPackList.at(packId).state;
            packData.data.length = tlmBlocks->at(blockId).TlmPackList.at(packId).length;
            packData.data.dataPucket.time = tlmBlocks->at(blockId).TlmPackList.at(packId).dataPucket.time;
            packData.data.dataPucket.dev_type = tlmBlocks->at(blockId).TlmPackList.at(packId).dataPucket.dev_type;
            packData.data.dataPucket.inf_type = tlmBlocks->at(blockId).TlmPackList.at(packId).dataPucket.inf_type;
            packData.data.dataPucket.data = tlmBlocks->at(blockId).TlmPackList.at(packId).dataPucket.data;
            m_tlmBlocks->data()[blockId].dataArray->insert(packId,packData);
        }
    }
}



QModelIndex ModelTlm::index(int row, int column, const QModelIndex &parent) const{
    if (!hasIndex(row, column, parent))
            return QModelIndex();
    if (!parent.isValid()) // запрашивают индексы корневых узлов
        return createIndex(row, column, const_cast<TlmBlockData*>(&m_tlmBlocks->data()[row]));
    TlmBlockData * pack = static_cast<TlmBlockData*>(parent.internalPointer());
    return createIndex(row,column,&pack->dataArray->data()[row]);
}

QModelIndex ModelTlm::parent(const QModelIndex &child) const{
    if (!child.isValid())
        return QModelIndex();
    ParentsTlm *blockInfo = static_cast<ParentsTlm*>(child.internalPointer());
    if(blockInfo->par)
        return QModelIndex();
    TlmPackData* childInfo = static_cast<TlmPackData*>(child.internalPointer());
    TlmBlockData *parentInfo = childInfo->parent;
    if(parentInfo->name == m_tlmBlocks->data()[0].name)
        return createIndex(0,0,parentInfo);
    else
        return createIndex(1,0,parentInfo);
}


int ModelTlm::rowCount(const QModelIndex &parent) const{
    if(!parent.isValid())
        return m_tlmBlocks->size();
    ParentsTlm *blockInfo = static_cast<ParentsTlm*>(parent.internalPointer());
    if(!blockInfo->par)
        return 0;
    TlmBlockData* parentInfo = static_cast<TlmBlockData*>(parent.internalPointer());
        return parentInfo->dataArray->size();
}

int ModelTlm::columnCount(const QModelIndex &parent) const{
    return 7;
}

QVariant ModelTlm::data(const QModelIndex &index, int role) const{
    if (!index.isValid())
        return QVariant();
    int column = index.column();
    if (role != Qt::DisplayRole)
        return QVariant();
    ParentsTlm *blockInfo = static_cast<ParentsTlm*>(index.internalPointer());
    if(blockInfo->par){
         TlmBlockData *blockData = static_cast<TlmBlockData*>(index.internalPointer());
         switch (column){
             case 0:
                  return blockData->name;
             case 1:
                  return blockData->bom;
              default:
                 return QVariant();
         }
    }
    else{
        TlmPackData *blockData = static_cast<TlmPackData*>(index.internalPointer());
        switch (column){
             case 0:
                 return index.row();
             case 1:
                 return QString::number(blockData->data.state);
             case 2:
                 return blockData->data.length;
             case 3:
                 return blockData->data.dataPucket.time;
             case 4:
                 return blockData->data.dataPucket.dev_type;
             case 5:
                 return blockData->data.dataPucket.inf_type;
             case 6:
                 return blockData->data.dataPucket.data;
             default:
                 return QVariant();
          }
     }
}

QVariant ModelTlm::headerData(int section, Qt::Orientation orientation, int role) const{
    if (role != Qt::DisplayRole)
       return QVariant();
    if (orientation == Qt::Horizontal){
        return headerArray[section];
    }
    return QVariant();
}
