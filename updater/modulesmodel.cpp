#include "modulesmodel.h"
#include <QDebug>
#include <QColor>

ModulesModel::ModulesModel()
    : m_modules(nullptr)
{


}



QModelIndex ModulesModel::index(int row, int column, const QModelIndex &parent)const{
   if(!m_modules || !m_modules->size())
       return QModelIndex();
   if(!parent.isValid()){
       return createIndex(row, column, m_modules->operator[](row));
   }
   else if (dynamic_cast<Module*>(static_cast<QObject*>(parent.internalPointer()))){
       Module *f_module = static_cast<Module *>(parent.internalPointer());
       return createIndex(row,column,f_module->m_versions->operator[](row));
   }
   else
     return QModelIndex();

}

QModelIndex ModulesModel::parent(const QModelIndex &child)const{
    if( !m_modules || !m_modules->size())
        return QModelIndex();
    if (!child.isValid()){
        return QModelIndex();
    }
    else if(dynamic_cast<VersionInfo*>(static_cast<QObject*>(child.internalPointer()))){
        VersionInfo *f_versions = dynamic_cast<VersionInfo*>(static_cast<QObject*>(child.internalPointer()));
        for(int i = 0; i < m_modules->size();++i){
            for(int j = 0;j < m_modules->operator[](i)->m_versions->size();++j){
                if(m_modules->operator[](i)->m_versions->operator[](j) == f_versions){
                    return createIndex(i,0,m_modules->operator[](i));
                }
            }
        }
    }
    return QModelIndex();
}

int ModulesModel::rowCount(const QModelIndex &parent )const{
    if(!m_modules || !m_modules->size())
        return 0;

    if (!parent.isValid()){ // количество корневых элементов
        return m_modules->size();
    }
    else if (dynamic_cast<VersionInfo*>(static_cast<QObject*>(parent.internalPointer()))){
        //VersionInfo *f_version = dynamic_cast<VersionInfo*>(static_cast<QObject*>(parent.internalPointer()));
        return 0;
    }
    else if (dynamic_cast<Module*>(static_cast<QObject*>(parent.internalPointer()))){
        Module *f_module = static_cast<Module *>(parent.internalPointer());
        return f_module->m_versions->size();
    }

    return 0;
}

int ModulesModel::columnCount(const QModelIndex &parent )const{
    Q_UNUSED(parent)
    return 1;
}

QVariant ModulesModel::data(const QModelIndex &index, int role )const{
    if (!index.isValid())
            return QVariant();
    if (role == Qt::DisplayRole){
        if (dynamic_cast<Module*>(static_cast<QObject*>(index.internalPointer()))){
            Module *f_module = static_cast<Module *>(index.internalPointer());
            return f_module->m_name;
        }
        if (dynamic_cast<VersionInfo*>(static_cast<QObject*>(index.internalPointer()))){
            VersionInfo *f_versioninfo = dynamic_cast<VersionInfo *>(static_cast<QObject*>(index.internalPointer()));
            return f_versioninfo->version();
        }
    }

    return QVariant();
}

Qt::ItemFlags ModulesModel::flags(const QModelIndex &index) const {
    if (!index.isValid())
        return Qt::NoItemFlags;
    return Qt::ItemIsEnabled | Qt::ItemIsSelectable  | Qt::ItemIsEnabled | Qt::ItemIsDragEnabled | Qt::ItemIsDropEnabled ;
}

QVariant ModulesModel::headerData(int section, Qt::Orientation orientation, int role)const{
    Q_UNUSED(section)
    Q_UNUSED(orientation)
    Q_UNUSED(role)
    return QVariant();
}
