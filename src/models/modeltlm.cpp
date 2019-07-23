#include "inc/models/modeltlm.h"
#include <QMessageBox>

/*ModelTlm::ModelTlm(QObject *parent)
    : QAbstractItemModel(parent){
    m_tlmBlocks = new QList<Data>;
    Data *blockPrev = nullptr;
    for(int i = 0;i < 12;i++){
        Data blo;
        blo.name = "W" + QString::number(i);
        blo.child = nullptr;
        blo.par = nullptr;
        if(!m_tlmBlocks->isEmpty()){
            blockPrev = const_cast<Data*>(&m_tlmBlocks->at(i-1));
            blo.par = blockPrev;
        }
        m_tlmBlocks->push_back(blo);
        if(blockPrev != nullptr){
            blockPrev->child = const_cast<Data*>(&m_tlmBlocks->at(i));
        }
        blockPrev = nullptr;
    }
}



QModelIndex ModelTlm::index(int row, int column, const QModelIndex &parent) const{
    if (!hasIndex(row, column, parent))
            return QModelIndex();

    if (!parent.isValid()) // запрашивают индексы корневых узлов
            return createIndex(row, 0, const_cast<Data*>(&m_tlmBlocks->at(row)));
    Data * puck = static_cast<Data*>(parent.internalPointer());

    if(puck->child != nullptr){
        //QMessageBox::about(nullptr,"Warning", puck->child->name);
        return createIndex(0, 0, const_cast<Data*>(puck->child));
    }
    QMessageBox::about(nullptr,"Warning", "modelndex");
    return QModelIndex();
}

QModelIndex ModelTlm::parent(const QModelIndex &child) const{
    if (!child.isValid()) {
        return QModelIndex();
    }
    Data* childInfo = static_cast<Data*>(child.internalPointer());
    Data* parentInfo = childInfo->par;
    if (parentInfo != nullptr) { // parent запрашивается не у корневого элемента
        return createIndex(0, 0, parentInfo);
    }
    else {
        return QModelIndex();
    }
}

int ModelTlm::rowCount(const QModelIndex &parent) const{
    if(!parent.isValid()){
        return 1;
    }
    else {
        Data* parentInfo = static_cast<Data*>(parent.internalPointer());

        if(parentInfo->child == nullptr ){
            return 0;
        }
        else {
            return 1;
        }
    }

}
int ModelTlm::columnCount(const QModelIndex &parent) const{
    return 1;
}
QVariant ModelTlm::data(const QModelIndex &index, int role) const{
    if (!index.isValid()){
        return QVariant();
    }
    if (role == Qt::DisplayRole){
        Data * puck = static_cast<Data*>(index.internalPointer());
        return puck->name;
    }
    else
        return QVariant();

}*/
ModelTlm::ModelTlm(QList<BlockTlm> *tlmBlocks,QObject *parent)
    : QAbstractItemModel(parent){
    this->m_tlmBlocks = new QVector<TlmBlockData>(2);
    for(int blockId = 0;blockId < tlmBlocks->size();blockId++){
        m_tlmBlocks->data()[blockId].dataArray = new QVector<TlmPackData>;

        for(int packId = 0;packId < tlmBlocks->at(blockId).TlmPackList.size();packId++){
            TlmPackData packData;
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
    QMessageBox::about(nullptr,"Warning", "конец конструктора");
}



QModelIndex ModelTlm::index(int row, int column, const QModelIndex &parent) const{
    if (!hasIndex(row, column, parent))
            return QModelIndex();

    if (!parent.isValid()){ // запрашивают индексы корневых узлов
        QMessageBox::about(nullptr,"Warning", "index parent");
            return createIndex(row, 0, const_cast<TlmBlockData*>(&m_tlmBlocks->data()[row]));
    }
    TlmBlockData * puck = static_cast<TlmBlockData*>(parent.internalPointer());
    QMessageBox::about(nullptr,"Warning", "index child");
    return createIndex(row,column,&puck->dataArray->data()[row]);
}

QModelIndex ModelTlm::parent(const QModelIndex &child) const{
    if (!child.isValid()) {
        return QModelIndex();
    }
    TlmPackData* childInfo = static_cast<TlmPackData*>(child.internalPointer());
    if(childInfo != nullptr){
        TlmBlockData* parentInfo = childInfo->parent;
        QMessageBox::about(nullptr,"Warning", parentInfo->name);
        if (parentInfo != nullptr) { // parent запрашивается не у корневого элемента
            QMessageBox::about(nullptr,"Warning", "парент не у корневого запра");
            if(m_tlmBlocks->data()[0].name == parentInfo->name){
                QMessageBox::about(nullptr,"Warning", "парент не у корневого запра");
                return createIndex(0, 0, parentInfo);
        }
        else {
            QMessageBox::about(nullptr,"Warning", "парент не у корневого запра");
            return createIndex(1, 0, parentInfo);
        }

    }
    else {
        return QModelIndex();
    }
    }
}

int ModelTlm::rowCount(const QModelIndex &parent) const{
    if(!parent.isValid())
        return 2;

        TlmBlockData* parentInfo = static_cast<TlmBlockData*>(parent.internalPointer());

        if(parentInfo != nullptr ){
            QMessageBox::about(nullptr,"warning",QString::number(parentInfo->dataArray->size()));
            return parentInfo->dataArray->size();
        }
        else {
            QMessageBox::about(nullptr,"Warning", "0 строк");
            return 0;
        }

}

int ModelTlm::columnCount(const QModelIndex &parent) const{
    return 1;
}
QVariant ModelTlm::data(const QModelIndex &index, int role) const{
    if (!index.isValid()){
        return QVariant();
    }
    if (role == Qt::DisplayRole){
        //Data * puck = static_cast<Data*>(index.internalPointer());
        return "puck->name";
    }
    else
        return QVariant();

}
