#include "datamodel.h"
#include <QFont>
#include <QColor>
#include "formsblock.h"
#include "headerblock.h"


DataModel::DataModel(){
    m_logDataVector = new QVector<QSharedPointer<ILogData> >;


}

DataModel::~DataModel(){
    if(m_logDataVector){delete m_logDataVector; m_logDataVector = nullptr;}
}

void DataModel::addLogData(QSharedPointer<ILogData> logData){
    if(m_logDataVector){
       beginInsertRows(QModelIndex(),m_logDataVector->size(), m_logDataVector->size());
       m_logDataVector->push_back(logData);
       endInsertRows();
    }
}

void DataModel::removeLogData(QSharedPointer<ILogData> logData){
    m_logDataVector->removeOne(logData);
    update();
}

void DataModel::update(){
    if(m_logDataVector){
       beginInsertRows(QModelIndex(),m_logDataVector->size(), m_logDataVector->size());
       endInsertRows();
    }
}

QModelIndex DataModel::index(int row, int column, const QModelIndex &parent)const{
    if(m_logDataVector->size() == 0)
        return QModelIndex();
    if (!hasIndex(row, column, parent)){
        return QModelIndex();
    }
    if (!parent.isValid()){ // запрашивают индексы корневых узлов
        return createIndex(row, column, m_logDataVector->at(row).data());
    }
    else if (dynamic_cast<ILogData*>(static_cast<QObject*>(parent.internalPointer()))){
        ILogData *f_logData = static_cast<ILogData *>(parent.internalPointer());
        return createIndex(row,column,f_logData->blocks()->at(row));
    }
    else if(dynamic_cast<IBlock*>(static_cast<QObject*>(parent.internalPointer()))){
        IBlock *f_block = static_cast<IBlock *>(parent.internalPointer());
        IBlock::TypeBlock type = f_block->name();
        switch(type){
            case IBlock::DATA_BLOCK:{
                DataBlock *f_dataBlock = dynamic_cast<DataBlock *>(f_block);
                if(f_dataBlock)
                    return createIndex(row,column,f_dataBlock->curves()->at(row));
                break;
            }
            case IBlock::FORMS_BLOCK:{
                FormsBlock *f_formsBlock = dynamic_cast<FormsBlock *>(f_block);
                if(f_formsBlock)
                    return createIndex(row,column,f_formsBlock->boards()->at(row));
                break;
            }
            case IBlock::HEADER_BLOCK:{
                HearedBlock *f_headerBlock = dynamic_cast<HearedBlock *>(f_block);
                if(f_headerBlock){
                    return createIndex(row,column,f_headerBlock->infoHeader()->at(row).data());
                }
                break;
            }
            default:{
                return QModelIndex();
            }
        }
    }
}

QModelIndex DataModel::parent(const QModelIndex &child)const{
    if(m_logDataVector->size() == 0)
        return QModelIndex();
    if (!child.isValid()){
        return QModelIndex();
    }
    else if (dynamic_cast<ILogData*>(static_cast<QObject*>(child.internalPointer()))){
        return QModelIndex();
    }
    else if(dynamic_cast<IBlock*>(static_cast<QObject*>(child.internalPointer()))){
        IBlock *f_block = static_cast<IBlock *>(child.internalPointer());
        foreach(auto logData,*m_logDataVector){
            QList<IBlock*> *m_blocks = logData->blocks();
            foreach(auto block,*m_blocks){
                if(block == f_block){
                    return createIndex(m_logDataVector->indexOf(logData),0,logData.data());
                }
            }
        }
    }
    else if(dynamic_cast<ICurve*>(static_cast<QObject*>(child.internalPointer()))){
        ICurve *f_curve = static_cast<ICurve *>(child.internalPointer());
        foreach(auto logData,*m_logDataVector){
            QList<IBlock*> *f_blocks = logData->blocks();
            foreach(auto block,*f_blocks){
                DataBlock *f_dataBlock = dynamic_cast<DataBlock *>(block);
                if(f_dataBlock){
                    QList<ICurve*> *f_curves = f_dataBlock->curves();
                    foreach(auto curve,*f_curves){
                        if(curve == f_curve){
                            return createIndex(f_blocks->indexOf(block),0,block);
                        }
                    }
                }
            }
        }
    }
    else if(dynamic_cast<IBoard *>(static_cast<QObject*>(child.internalPointer()))){
        IBoard *f_board = static_cast<IBoard *>(child.internalPointer());
        foreach(auto logData,*m_logDataVector){
            QList<IBlock*> *f_blocks = logData->blocks();
            foreach(auto block,*f_blocks){
                FormsBlock *f_formsBlock = dynamic_cast<FormsBlock *>(block);
                if(f_formsBlock){
                    QList<ABoard*> *f_boards = f_formsBlock->boards();
                    foreach(auto board,*f_boards){
                        if(board == f_board){
                            return createIndex(f_blocks->indexOf(block),0,block);
                        }
                    }
                }
            }
        }
    }
    else if(dynamic_cast<HeaderInfo *>((QObject*)child.internalPointer())){
        HeaderInfo *f_headerinfo = dynamic_cast<HeaderInfo *>((QObject*)child.internalPointer());
        foreach(auto logData,*m_logDataVector){
            QList<IBlock*> *f_blocks = logData->blocks();
            foreach(auto block,*f_blocks){
                    HearedBlock *f_formsBlock = dynamic_cast<HearedBlock *>(block);
                    if(f_formsBlock){
                        QList<QSharedPointer<HeaderInfo> > *f_listHeaderInfo = f_formsBlock->infoHeader();
                        foreach(auto headerInfo,*f_listHeaderInfo){
                            if(headerInfo == f_headerinfo)
                                return createIndex(f_blocks->indexOf(block),0,block);
                        }
                    }
            }
        }
    }


    return QModelIndex();
}

int DataModel::rowCount(const QModelIndex &parent )const{
    if(m_logDataVector->size() == 0)
        return 0;

    if (!parent.isValid()){ // количество корневых элементов
        return m_logDataVector->size();
    }
    else if (dynamic_cast<ILogData*>(static_cast<QObject*>(parent.internalPointer()))){
        ILogData *f_logData = static_cast<ILogData *>(parent.internalPointer());
        return f_logData->blocks()->size();
    }
    else if(dynamic_cast<IBlock*>(static_cast<QObject*>(parent.internalPointer()))){
        IBlock *f_block = static_cast<IBlock *>(parent.internalPointer());
        IBlock::TypeBlock type = f_block->name();
        switch(type){
            case IBlock::DATA_BLOCK:{
                DataBlock *f_dataBlock = dynamic_cast<DataBlock *>(f_block);
                if(f_dataBlock)
                    return f_dataBlock->curves()->size();
                break;
            }
            case IBlock::FORMS_BLOCK:{
                FormsBlock *f_formsBlock = dynamic_cast<FormsBlock *>(f_block);
                if(f_formsBlock)
                    return f_formsBlock->boards()->size();
                break;
            }
            case IBlock::HEADER_BLOCK:{
                foreach(auto logData,*m_logDataVector){
                    QList<IBlock*> *f_blocks = logData->blocks();
                    foreach(auto block,*f_blocks){
                        if(block == f_block){
                            HearedBlock *f_headerBlock = dynamic_cast<HearedBlock *>(block);
                            if(f_headerBlock){
                                if(f_headerBlock->infoHeader()){
                                    return f_headerBlock->infoHeader()->size();
                                }
                                else
                                    return 0;
                            }
                        }
                    }
                }
                break;
            }
            default:{
                return 0;
            }
        }
    }
    return 0;
}

int DataModel::columnCount(const QModelIndex &parent )const{
    return 2;
}

QVariant DataModel::data(const QModelIndex &index, int role )const{
    if (!index.isValid())
            return QVariant();
    if (role == Qt::DisplayRole){

        if (!index.isValid()){
            return QVariant();
        }
        if(index.column()){
            if(dynamic_cast<HeaderInfo *>(static_cast<QObject*>(index.internalPointer()))){
                return dynamic_cast<HeaderInfo *>(static_cast<QObject*>(index.internalPointer()))->body();
             }
            else return QVariant();
        }
        if (dynamic_cast<ILogData*>(static_cast<QObject*>(index.internalPointer()))){
            ILogData *f_logData = static_cast<ILogData *>(index.internalPointer());
            return f_logData->name().mid(f_logData->name().indexOf("/") + 1);
        }
        else if(dynamic_cast<IBlock*>(static_cast<QObject*>(index.internalPointer()))){
            IBlock *f_block = static_cast<IBlock *>(index.internalPointer());
            IBlock::TypeBlock f_type = f_block->name();
            switch(f_type){
                case IBlock::DATA_BLOCK:{
                    DataBlock *f_dataBlock = dynamic_cast<DataBlock *>(f_block);
                    return  f_dataBlock->shortCuts()->first().device() + "(" + QString::number(f_dataBlock->numberOfVectors()) + ")";
                }
                case IBlock::FORMS_BLOCK:{
                    return "FORMS";
                }
                case IBlock::TOOLINFO_BLOCK:{
                    return "TOOLINFO";
                }
                case IBlock::HEADER_BLOCK:{
                    return "HEADER";
                }
                default:{
                    return QModelIndex();
                }
            }
        }
        else if(dynamic_cast<ICurve*>(static_cast<QObject*>(index.internalPointer()))){
            ICurve *f_curve = static_cast<ICurve *>(index.internalPointer());
            return f_curve->mnemonic() + "(" + QString::number(f_curve->minimum()) + " : " + QString::number(f_curve->maximum()) + ")";
        }
        else if(dynamic_cast<IBoard*>(static_cast<QObject*>(index.internalPointer()))){
            IBoard *f_board = static_cast<IBoard *>(index.internalPointer());
            return f_board->name();
        }
        else if(dynamic_cast<HeaderInfo *>(static_cast<QObject*>(index.internalPointer()))){
            return dynamic_cast<HeaderInfo *>(static_cast<QObject*>(index.internalPointer()))->name();
        }
    }
    else if(role == Qt::ForegroundRole){
           return QColor(Qt::black);
    }
    else if(role == Qt::BackgroundRole){
           return QColor(Qt::white);
    }
    else if(role == Qt::FontRole){
           return QFont("Times", 12, QFont::Bold);
    }
    else
        return QVariant();
}

Qt::ItemFlags DataModel::flags(const QModelIndex &index) const {
    if (!index.isValid())
        return false;
    int column = index.column();
    switch (column){
         case 0:{
            return Qt::ItemIsEnabled | Qt::ItemIsSelectable  | Qt::ItemIsEnabled | Qt::ItemIsDragEnabled | Qt::ItemIsDropEnabled ;
         }
        case 1:{
           return Qt::ItemIsEnabled | Qt::ItemNeverHasChildren | Qt::ItemIsEditable;
        }
         default:
             return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemNeverHasChildren;
      }
}

QVariant DataModel::headerData(int section, Qt::Orientation orientation, int role)const{
    return QVariant();
}

