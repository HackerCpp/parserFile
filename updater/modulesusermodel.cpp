#include "modulesusermodel.h"


ModulesUserModel::ModulesUserModel()
    : m_modules(nullptr)
{
    m_headerList << tr("Modules") << tr("Installed")
                 << tr("New version");
}



QModelIndex ModulesUserModel::index(int row, int column, const QModelIndex &parent)const{
   if(!m_modules || !m_modules->size())
       return QModelIndex();
   if(!parent.isValid()){
       return createIndex(row, column, m_modules->operator[](row));
   }
   else
     return QModelIndex();

}

QModelIndex ModulesUserModel::parent(const QModelIndex &child)const{
    if( !m_modules || !m_modules->size())
        return QModelIndex();
    if (!child.isValid()){
        return QModelIndex();
    }
    return QModelIndex();
}

int ModulesUserModel::rowCount(const QModelIndex &parent )const{
    if(!m_modules || !m_modules->size())
        return 0;

    if (!parent.isValid()){ // количество корневых элементов
        return m_modules->size();
    }
    return 0;
}

int ModulesUserModel::columnCount(const QModelIndex &parent )const{
    return 3;
}

QVariant ModulesUserModel::data(const QModelIndex &index, int role )const{
    if (!index.isValid())
            return QVariant();
    int f_column = index.column();
    if (role == Qt::DisplayRole){
        if (!index.isValid()){
            return QVariant();
        }
        if (dynamic_cast<Module*>(static_cast<QObject*>(index.internalPointer()))){
            Module *f_module = static_cast<Module *>(index.internalPointer());
            if(!f_column)
                return f_module->m_name;
            if(f_column == 1)
                return f_module->m_currentVersion->version();
            if(f_column == 2)
                return f_module->latestVersion();
        }
    }
    else if(role == Qt::CheckStateRole){
        if (!index.isValid()){
            return QVariant();
        }
        if (dynamic_cast<Module*>(static_cast<QObject*>(index.internalPointer()))){
            Module *f_module = static_cast<Module *>(index.internalPointer());
            if(!f_column)
                return f_module->m_isInstalled;
        }
    }
    return QVariant();
}

bool ModulesUserModel::setData(const QModelIndex &index, const QVariant &value, int role){
    if (!index.isValid())
        return false;
    int f_column = index.column();
    if(role == Qt::CheckStateRole){
        if (!index.isValid()){
            return false;
        }
        if (dynamic_cast<Module*>(static_cast<QObject*>(index.internalPointer()))){
            Module *f_module = static_cast<Module *>(index.internalPointer());
            if(!f_column)
                return f_module->m_isInstalled = value.toBool();
        }
    }
}

Qt::ItemFlags ModulesUserModel::flags(const QModelIndex &index) const {
    if (!index.isValid())
        return Qt::NoItemFlags;
    int f_column = index.column();
    if(!f_column)
        return Qt::ItemIsEnabled  | Qt::ItemIsUserCheckable ;
    else
        return Qt::ItemIsEnabled;
}

QVariant ModulesUserModel::headerData(int section, Qt::Orientation orientation, int role)const{
    if (role != Qt::DisplayRole)
       return QVariant();
    if (orientation == Qt::Horizontal && section < m_headerList.size()){
        return m_headerList[section];
    }
    return QVariant();
}
