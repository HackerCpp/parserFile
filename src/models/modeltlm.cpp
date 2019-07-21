#include "inc/models/modeltlm.h"

ModelTlm::ModelTlm(QList<BlockTlm> &tlmBlocks)
    :m_tlmBlocks(tlmBlocks){

    this->model = new QStandardItemModel(m_tlmBlocks.size(),100);
    for(int row = 0; row < m_tlmBlocks.size();row++){
        QModelIndex indexName = model->index(row,0);
        QModelIndex indexBoom = model->index(row,99);
        model->setData(indexName,tlmBlocks.at(row).name);
        model->setData(indexBoom,tlmBlocks.at(row).boom);
        model->insertRows(0,m_tlmBlocks.at(row).tlmPuckList.size(),indexName);
        model->insertColumns(0,5,indexName);
        for(int r = 0; r < m_tlmBlocks.at(row).tlmPuckList.size();r++){
            model->setData(model->index(r,0,indexName),m_tlmBlocks.at(row).tlmPuckList.at(r).state);
            model->setData(model->index(r,1,indexName),m_tlmBlocks.at(row).tlmPuckList.at(r).length);
            model->setData(model->index(r,2,indexName),m_tlmBlocks.at(row).tlmPuckList.at(r).dataPucket.time);
            model->setData(model->index(r,3,indexName),m_tlmBlocks.at(row).tlmPuckList.at(r).dataPucket.dev_type);
            model->setData(model->index(r,4,indexName),m_tlmBlocks.at(row).tlmPuckList.at(r).dataPucket.inf_type);
            model->setData(model->index(r,5,indexName),m_tlmBlocks.at(row).tlmPuckList.at(r).dataPucket.data);
        }
    }
}


QStandardItemModel *ModelTlm::getTlmModel(){
    return this->model;
}

