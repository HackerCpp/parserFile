#include "modelcurveeditor.h"


ModelCurveEditor::ModelCurveEditor(AGraphicItem *graphicItem){
    m_vector = new QVector<qreal>();
    m_curve = graphicItem->curve();
    if(!m_curve)
        return;
    m_time = m_curve->time();
    m_depth = m_curve->depth();
    for(uint i = 0;i < m_curve->size(); ++i){
        m_vector->push_back(m_curve->data(i));
    }
}

ModelCurveEditor::~ModelCurveEditor(){
    if(m_vector){delete m_vector;m_vector = nullptr;}
}

QVariant ModelCurveEditor::data(const QModelIndex &index, int role) const {
    if (!index.isValid())
        return QVariant();
    if (index.row() >= m_time->size())
        return QVariant();
    int column = index.column();
    if(column > m_curve->sizeOffset() + 1)
        return QVariant();
    if (role == Qt::DisplayRole){
    switch (column){
        case 0:
           return m_time->data(index.row()) /600000;
        case 1:
           return m_depth->data(index.row()) / 1000;
        default:
            return m_vector->data()[(column - 1) * index.row()];
      }

    }
    else if(role == Qt::FontRole){
           return QFont("Times", 12, QFont::Bold);
    }
    else
        return QVariant();
}

int ModelCurveEditor::rowCount(const QModelIndex &parent) const {
    return m_time->size();
}

int ModelCurveEditor::columnCount(const QModelIndex &parent) const{
    return 2 + m_curve->sizeOffset();
}

QVariant ModelCurveEditor::headerData(int section, Qt::Orientation orientation, int role) const{
    if (role != Qt::DisplayRole)
       return QVariant();
    if (orientation == Qt::Horizontal){
        switch (section) {
        case 0:{
            return tr("Time(min)");
        }
        case 1:{
            return tr("Depth(m)");
        }
        default:{
            return tr("Offset") + QString::number(section - 2);
        }
        }
    }
    return QVariant();
}

Qt::ItemFlags ModelCurveEditor::flags(const QModelIndex &index) const {
    return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemNeverHasChildren | Qt::ItemIsEditable;
}

bool ModelCurveEditor::setData(const QModelIndex &index, const QVariant &value, int role ){
    if (!index.isValid())
        return false;
    if (index.row() >= m_time->size())
        return false;
    int column = index.column();
    if(column > m_curve->sizeOffset() + 1)
        return false;
    if (role == Qt::EditRole){
    switch (column){

        case 0:{
           return true;
        }
        case 1:{
           return true;
        }
        default:{
           m_vector->data()[(column - 1) * index.row()] = value.toDouble();
           return true;
        }
     }
    }
    else
        return false;
}

void ModelCurveEditor::apply(){
    for(int i = 0;i < m_curve->size(); ++i){
        m_curve->setData(m_vector->data()[i],i);
    }
}
