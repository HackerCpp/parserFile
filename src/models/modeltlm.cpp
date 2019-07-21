#include "inc/models/modeltlm.h"

ModelTlm::ModelTlm(QList<BlockTlm> &tlmBlocks)
    :m_tlmBlocks(tlmBlocks){
    int count;
    this->model = new QStandardItemModel(m_tlmBlocks.size(),7);
    for(int row = 0; row < m_tlmBlocks.size();row++){
        QModelIndex indexName = model->index(row,0);
        QModelIndex indexBoom = model->index(row,1);
        QModelIndex indexPuck;
        model->setData(indexName,tlmBlocks.at(row).name);
        model->setData(indexBoom,tlmBlocks.at(row).boom);
        model->insertRows(0,m_tlmBlocks.at(row).tlmPuckList.size(),indexName);
        model->insertColumns(0,7,indexName);
        count = 0;
        for(int r = 0; r < m_tlmBlocks.at(row).tlmPuckList.size();r++){
            model->setData(model->index(r,0,indexName),count++);
            model->setData(model->index(r,1,indexName),m_tlmBlocks.at(row).tlmPuckList.at(r).state);
            model->setData(model->index(r,2,indexName),m_tlmBlocks.at(row).tlmPuckList.at(r).length);
            model->setData(model->index(r,3,indexName),m_tlmBlocks.at(row).tlmPuckList.at(r).dataPucket.time);
            model->setData(model->index(r,4,indexName),m_tlmBlocks.at(row).tlmPuckList.at(r).dataPucket.dev_type);
            model->setData(model->index(r,5,indexName),m_tlmBlocks.at(row).tlmPuckList.at(r).dataPucket.inf_type);
            /*indexPuck = model->index(r,0,indexName);
            model->insertRows(0,1,indexPuck);
            model->insertColumns(0,5,indexPuck);
            indexPuck = model->index(0,4,indexPuck);

            model->setData(indexPuck,m_tlmBlocks.at(row).tlmPuckList.at(r).dataPucket.data);*/
            model->setData(model->index(r,6,indexName),m_tlmBlocks.at(row).tlmPuckList.at(r).dataPucket.data);
        }
    }
}


QStandardItemModel *ModelTlm::getTlmModel(){
    return this->model;
}

