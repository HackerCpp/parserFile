#include "modelforgraphicsitems.h"
#include "QRadioButton"
#include <QItemDelegate>

ModelForGraphicsItems::ModelForGraphicsItems(QMap<QString,AGraphicItem *> *items)
{
    m_items = new  QVector<AGraphicItem *>;
    int index = 0;
    foreach(auto item,*items){
        m_items->insert(index,item);
        ++index;
    }
    m_headerList << "Visible" << "Data" <<"Device" << "Mnemonic" << "Track number" << "Draw type"<<"Color" << "" << "" << "" << "";
}


ModelForGraphicsItems::~ModelForGraphicsItems(){

}

QVariant ModelForGraphicsItems::data(const QModelIndex &index, int role )const{

    if (!index.isValid())
        return QVariant();
    if (index.row() >= m_items->size())
        return QVariant();
    int column = index.column();
    if (role == Qt::DisplayRole){
    switch (column){
        case 0:
           return m_items->at(index.row())->itemInfo()->visible(AItem::BOARD_GRAPH_VIEW);
        case 1:
           return this->m_items->at(index.row())->curve()->shortCut().dateTime();
        case 2:
           return this->m_items->at(index.row())->curve()->shortCut().device();
        case 3:
           return this->m_items->at(index.row())->curve()->mnemonic();
        case 4:
           return this->m_items->at(index.row())->itemInfo()->numberOfTrack();
        case 5:
           return this->m_items->at(index.row())->curve()->desc()->param("draw_type");
        case 6:
           return this->m_items->at(index.row())->color();
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

int ModelForGraphicsItems::rowCount(const QModelIndex &parent)const{
    Q_UNUSED(parent)
    return m_items->size();
}

int ModelForGraphicsItems::columnCount(const QModelIndex &parent) const {
    Q_UNUSED(parent)
    return 10;
}

QVariant ModelForGraphicsItems::headerData(int section, Qt::Orientation orientation, int role) const {

    if (role != Qt::DisplayRole)
       return QVariant();
    if (orientation == Qt::Horizontal && section < m_headerList.size()){
        return m_headerList[section];
    }
    else if(orientation == Qt::Vertical)
        return section;
    return QVariant();
}

Qt::ItemFlags ModelForGraphicsItems::flags(const QModelIndex &index) const {
    if (!index.isValid())
        return false;
    if (index.row() >= m_items->size())
        return false;
    int column = index.column();
    switch (column){
         case 0:{
            return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemNeverHasChildren | Qt::ItemIsEditable;
         }
        case 4:{
           return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemNeverHasChildren | Qt::ItemIsEditable;
        }
        case 6:{
           return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemNeverHasChildren | Qt::ItemIsEditable;
        }
         default:
             return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemNeverHasChildren;
      }
}

bool ModelForGraphicsItems::setData(const QModelIndex &index, const QVariant &value, int role){
    if (!index.isValid())
        return false;
    if (index.row() >= m_items->size())
        return false;
    int column = index.column();
    if (role == Qt::EditRole){
    switch (column){
        case 0:{
           m_items->at(index.row())->itemInfo()->setVisible(AItem::BOARD_GRAPH_VIEW,value.toBool());
           return true;
        }
        case 4:{
           m_items->at(index.row())->itemInfo()->setNumberOfTrack(value.toString().remove("Track ").toInt());
           return true;
        }
        case 6:{
           m_items->at(index.row())->setColor(value.value<QColor>());
           return true;
        }
        default:
            return false;
     }
    }
    else
        return false;
}
