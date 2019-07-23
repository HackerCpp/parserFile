#include "inc/models/modeltlm.h"
#include <QMessageBox>

ModelTlm::ModelTlm(QObject *parent)
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

}
