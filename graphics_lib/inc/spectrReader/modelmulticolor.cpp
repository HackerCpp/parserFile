#include "modelmulticolor.h"
#include <QColor>

ModelMulticolor::ModelMulticolor(QList<MulticolorItem> *listMulticolor)
    :m_listMulticolor(nullptr),m_listMulticolorOriginal(listMulticolor)
{
    if(!m_listMulticolorOriginal)
        return;
    m_listMulticolor = new QList<MulticolorItem>;
    foreach(auto multicolor,*m_listMulticolorOriginal){
        m_listMulticolor->push_back(multicolor);
    }
    m_headerList << "Value" << "Color";

}

ModelMulticolor::~ModelMulticolor(){
    if(m_listMulticolor){delete m_listMulticolor;m_listMulticolor = nullptr;}
}


QVariant ModelMulticolor::data(const QModelIndex &index, int role )const{

    if (!index.isValid())
        return QVariant();
    if (index.row() >= m_listMulticolor->size())
        return QVariant();
    int column = index.column();
    if (role == Qt::DisplayRole){
    switch (column){
        case 0:
           return m_listMulticolor->at(index.row()).bound;
        case 1:
            return m_listMulticolor->at(index.row()).value;

        default:
            return QVariant();
      }
    }
    else if(role == Qt::ForegroundRole){
           return QVariant();//this->m_items->at(index.row())->color();
    }
    else if(role == Qt::FontRole){
           return QVariant();//QFont("Times", 12, QFont::Bold);
    }
    else
        return QVariant();
}

int ModelMulticolor::rowCount(const QModelIndex &parent)const{
    Q_UNUSED(parent)
    return m_listMulticolor->size();
}

int ModelMulticolor::columnCount(const QModelIndex &parent) const {
    Q_UNUSED(parent)
    return 2;
}

QVariant ModelMulticolor::headerData(int section, Qt::Orientation orientation, int role) const {

    if (role != Qt::DisplayRole)
       return QVariant();
    if (orientation == Qt::Horizontal && section < m_headerList.size()){
        return m_headerList[section];
    }
    else if(orientation == Qt::Vertical)
        return section;
    return QVariant();
}

Qt::ItemFlags ModelMulticolor::flags(const QModelIndex &index) const {
    if (!index.isValid())
        return false;
    if (index.row() >= m_listMulticolor->size())
        return false;
    int column = index.column();
    switch (column){
        case 0:{
            return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemNeverHasChildren | Qt::ItemIsEditable;
        }
        case 1:{
           return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemNeverHasChildren | Qt::ItemIsEditable;
        }
        default:
            return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemNeverHasChildren;
    }
}

bool ModelMulticolor::setData(const QModelIndex &index, const QVariant &value, int role){
    if (!index.isValid())
        return false;
    if (index.row() >= m_listMulticolor->size())
        return false;
    int column = index.column();
    if (role == Qt::EditRole){
        switch (column){
            case 0:{
               m_listMulticolor->operator[](index.row()).bound = value.toDouble();
               return true;
            }
            case 1:{
               m_listMulticolor->operator[](index.row()).value = value.toString();
               return true;
            }
            default:
                return false;
        }
    }
    else
        return false;
}

void ModelMulticolor::apply(){
    if(!m_listMulticolorOriginal || !m_listMulticolor)
        return;
    m_listMulticolorOriginal->clear();
    foreach(auto multicolor,*m_listMulticolor){
        m_listMulticolorOriginal->push_back(multicolor);
    }
}

void ModelMulticolor::insertColor(){
    if(m_listMulticolor){
       beginInsertRows(QModelIndex(),m_listMulticolor->size(), m_listMulticolor->size());
       m_listMulticolor->push_back(MulticolorItem{m_listMulticolor->last().bound,m_listMulticolor->last().value});
       endInsertRows();
    }
}

void ModelMulticolor::removeColor(){
    if(m_listMulticolor->size() <= 3)
        return;
    if(m_listMulticolor){
       beginRemoveRows(QModelIndex(),m_listMulticolor->size() - 1, m_listMulticolor->size() - 1);
       m_listMulticolor->removeLast();
       endRemoveRows();
    }
}

void ModelMulticolor::calculate(){
    if(!m_listMulticolor)
        return;
    if(m_listMulticolor->size() < 2)
        return;
    if(m_listMulticolor->first().bound > m_listMulticolor->last().bound){
        qreal f_bound = m_listMulticolor->first().bound;
        QString f_color = m_listMulticolor->first().value;
        m_listMulticolor->first().bound = m_listMulticolor->last().bound;
        m_listMulticolor->first().value = m_listMulticolor->last().value;
        m_listMulticolor->last().bound = f_bound;
        m_listMulticolor->last().value = f_color;
    }
    QColor f_colorMinimum(m_listMulticolor->first().value);
    QColor f_colorMaximum(m_listMulticolor->last().value);
    qreal f_hueMinimum = f_colorMinimum.hue();
    qreal f_hueMaximum = f_colorMaximum.hue();
    qreal f_minimum = m_listMulticolor->first().bound;
    qreal f_maximum = m_listMulticolor->last().bound;


    qreal f_hueStep = (f_hueMaximum - f_hueMinimum) / qreal(m_listMulticolor->size() - 1);
    qreal f_hueBegin =  QColor(m_listMulticolor->first().value).hue();
    qreal f_step = (f_maximum - f_minimum) / qreal(m_listMulticolor->size() - 1);
    qreal f_beginValue = m_listMulticolor->first().bound;
    f_hueBegin = f_hueBegin < 0 ? 0 : f_hueBegin;
    qDebug() << f_hueStep << (f_hueMaximum - f_hueMinimum);
    for(int i = 1; i < m_listMulticolor->size() - 1; ++i){
        m_listMulticolor->operator[](i).bound = (f_beginValue + (f_step * qreal(i)));
        QColor f_col;
        qreal hue = f_hueBegin + (f_hueStep * qreal(i));
        f_col.setHsvF(hue,1,1,255);
        m_listMulticolor->operator[](i).value = f_col.name();
    }
    emit dataChanged(index(0,0),index(m_listMulticolor->size(),2));
}
