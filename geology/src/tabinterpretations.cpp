#include "tabinterpretations.h"
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QLibrary>
#include "customdelegates.h"
#include <QButtonGroup>
#include <QCheckBox>
#include <QDebug>
#include <QApplication>
#include <QFileDialog>


ModelForTabInterpretation::ModelForTabInterpretation(QList<Interpretation*> *listInterpretation)
    :m_listInterpretation(listInterpretation)
{

    m_headerList << tr("Active") << tr("Name") << tr("Version");
}


ModelForTabInterpretation::~ModelForTabInterpretation(){

}

QVariant ModelForTabInterpretation::data(const QModelIndex &index, int role )const{
    if(!m_listInterpretation)
        return  QVariant();
    if (!index.isValid())
        return QVariant();

    if (index.row() >= m_listInterpretation->size())
        return QVariant();

    int column = index.column();

    if (role == Qt::DisplayRole){
        switch (column){
            case 0:
               return m_listInterpretation->at(index.row())->isActive;
            case 1:
               return m_listInterpretation->at(index.row())->name;
            case 2:
               return m_listInterpretation->at(index.row())->version;
            default:
                return QVariant();
        }
    }
    return QVariant();
}

int ModelForTabInterpretation::rowCount(const QModelIndex &parent)const{
    Q_UNUSED(parent)
    return m_listInterpretation->size();
}

int ModelForTabInterpretation::columnCount(const QModelIndex &parent) const {
    Q_UNUSED(parent)
    return 3;
}

QVariant ModelForTabInterpretation::headerData(int section, Qt::Orientation orientation, int role) const {

    if (role != Qt::DisplayRole)
       return QVariant();
    if (orientation == Qt::Horizontal && section < m_headerList.size()){
        return m_headerList[section];
    }
    else if(orientation == Qt::Vertical)
        return section;
    return QVariant();
}

Qt::ItemFlags ModelForTabInterpretation::flags(const QModelIndex &index) const {
    if (!index.isValid())
        return Qt::NoItemFlags;
    if (index.row() >= m_listInterpretation->size())
        return Qt::NoItemFlags;
    int column = index.column();
    switch (column){
         case 0:{
            return Qt::ItemIsEnabled | Qt::ItemNeverHasChildren | Qt::ItemIsEditable;
         }
         default:
             return 0;
      }
}

bool ModelForTabInterpretation::setData(const QModelIndex &index, const QVariant &value, int role){
    if (!index.isValid())
        return false;
    if (index.row() >= m_listInterpretation->size())
        return false;
    int column = index.column();
    if (role == Qt::EditRole){
    switch (column){
        case 0:{
            if(value.toBool()){
                foreach(auto value,*m_listInterpretation)
                    value->isActive = false;
            }
            m_listInterpretation->operator[](index.row())->isActive = value.toBool();
            return true;
        }
        default:
            return false;
     }
    }
    else
        return false;
}

QString ModelForTabInterpretation::getActiveFilePath(){
    foreach(auto value,*m_listInterpretation){
        if(value->isActive)
            return value->absoluteFilePath;
    }
    return nullptr;
}
/***********************************************************************************************/

QString TabInterpretations::getAbsolutePath(QFileInfoList fileInfolist){
    show();
    if(m_btnApply)
        m_btnApply->hide();
    setWindowModality(Qt::ApplicationModal);
    QString f_returnPath = nullptr;
    m_isClose = m_isApply = false;
    setWindowModality(Qt::ApplicationModal);
    QList<Interpretation*> *f_listInterpretation = new QList<Interpretation*>();
    foreach(auto file,fileInfolist){
        QString f_path = file.absoluteFilePath();
        QLibrary  lib(f_path);
        lib.load();
        typedef QString (*FString)();
        FString version = (FString)(lib.resolve("version"));
        FString name = (FString)(lib.resolve("name"));
        if(version && name)
            f_listInterpretation->push_back(new Interpretation{false,name(),version(),f_path});
    }
    ModelForTabInterpretation *f_model = new ModelForTabInterpretation(f_listInterpretation);
    QTableView *f_tableView = new QTableView();
    f_tableView->setItemDelegateForColumn(0,new CheckBoxDelegate());
    f_tableView->setModel(f_model);
    m_scroll->setWidget(f_tableView);
    while(!m_isClose){
        QCoreApplication::processEvents ();
    }
    if(m_isApply){
        return f_model->getActiveFilePath();
    }
    else
        return f_returnPath;
}

TabInterpretations::~TabInterpretations(){
}

void TabInterpretations::closeEvent(QCloseEvent *event){
    m_isClose = true;
}

void TabInterpretations::cansel(){
     m_isClose = true;
}

void TabInterpretations::apply(){
    m_isApply = m_isClose = true;
}
