#include "modellegenditems.h"

ModelLegendItems::ModelLegendItems(QList<AGraphicItem *> *items)
    : m_items(items)
{
    m_headerList << tr("mnemonic") << tr("begin") << tr("end") << tr("begin - end") << tr("maximum") << tr("minimum") << tr("max - min");
    updateVisibleItems();
    m_beginPoint = QPointF(0,0);
    m_currentPoint = QPointF(0,0);
}


ModelLegendItems::~ModelLegendItems(){

}

void ModelLegendItems::updateVisibleItems(){
    if(!m_items){
        return;
    }
    beginResetModel();
    m_visibleItems.clear();
    foreach(auto item,*m_items){
        if(item->is_visible())
            m_visibleItems.push_back(item);
    }
    endResetModel();
}

void ModelLegendItems::setBeginPoint(QPointF beginPoint){
    m_currentPoint = m_beginPoint = beginPoint;

}

void ModelLegendItems::setCurrentPoint(QPointF currentPoint){
    beginResetModel();
    m_currentPoint = currentPoint;
    endResetModel();
}

QVariant ModelLegendItems::data(const QModelIndex &index, int role ) const {
    if (!index.isValid())
        return QVariant();
    if (index.row() >= m_visibleItems.size())
        return QVariant();
    int column = index.column();
    if (role == Qt::DisplayRole){
        switch (column){
            case 0:
               return m_visibleItems.at(index.row())->curve()->mnemonic();
            case 1:
               return m_visibleItems.at(index.row())->valueFromScenePoint(m_beginPoint);
            case 2:
               return m_visibleItems.at(index.row())->valueFromScenePoint(m_currentPoint);
            case 3:
               return m_visibleItems.at(index.row())->valueFromScenePoint(m_beginPoint) - m_visibleItems.at(index.row())->valueFromScenePoint(m_currentPoint);
            case 4:
               return m_visibleItems.at(index.row())->maximumFromScenePoints(m_beginPoint,m_currentPoint);
            case 5:
               return m_visibleItems.at(index.row())->minimumFromScenePoints(m_beginPoint,m_currentPoint);
            case 6:
               return m_visibleItems.at(index.row())->maximumFromScenePoints(m_beginPoint,m_currentPoint) - m_visibleItems.at(index.row())->minimumFromScenePoints(m_beginPoint,m_currentPoint);
            default:
                return QVariant();
        }
    }
    else if(role == Qt::ForegroundRole){
           return this->m_visibleItems.at(index.row())->color();
    }
    else if(role == Qt::BackgroundRole){
           return QColor(255,255,255,240);//this->m_items->at(index.row())->color();
    }
    else if(role == Qt::FontRole){
           return QFont("Times", 15, QFont::Bold);
    }
    else
        return QVariant();
}

int ModelLegendItems::rowCount(const QModelIndex &parent) const {
    if(!m_visibleItems.size())
        return 0;
    return m_visibleItems.size();
}

int ModelLegendItems::columnCount(const QModelIndex &parent) const {
    return m_headerList.size();
}

QVariant ModelLegendItems::headerData(int section, Qt::Orientation orientation, int role) const {
    if (role == Qt::DisplayRole){
       //return QVariant();
        if (orientation == Qt::Horizontal && section < m_headerList.size()){
            return m_headerList[section];
        }
        else if(orientation == Qt::Vertical)
            return section;
    }
    else if(role == Qt::ForegroundRole){
           return QColor(255,255,255,200);
    }
    else if(role == Qt::BackgroundRole){
           return QColor(Qt::black) ;//this->m_items->at(index.row())->color();
    }
    else if(role == Qt::FontRole){
           return QFont("Times", 12, QFont::Bold);
    }
    else
        return QVariant();
}

Qt::ItemFlags ModelLegendItems::flags(const QModelIndex &index) const {
    if (!index.isValid())
        return Qt::NoItemFlags;
    if (index.row() >= m_visibleItems.size())
        return Qt::NoItemFlags;
    return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemNeverHasChildren;
}
