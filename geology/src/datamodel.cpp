#include "datamodel.h"
#include <QFont>
#include <QColor>
#include "formsblock.h"
#include "headerblock.h"
#include "labelblock.h"
#include "QTextEdit"
#include "setlabelsforboard.h"
#include "ldlabel.h"


DataModel::DataModel(){
    m_logDataVector = new QVector<shared_ptr<ILogData> >;
    m_curentLogData = nullptr;
}

DataModel::~DataModel(){
    if(m_logDataVector){delete m_logDataVector; m_logDataVector = nullptr;}
}

void DataModel::addLogData(std::shared_ptr<ILogData> logData){
    m_curentLogData = logData.get();
    if(m_logDataVector){
       beginInsertRows(QModelIndex(),m_logDataVector->size(), m_logDataVector->size());
       m_logDataVector->push_back(logData);
       endInsertRows();
    }
}

void DataModel::removeLogData(shared_ptr<ILogData> logData){
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
        return createIndex(row, column, m_logDataVector->at(row).get());
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
            case IBlock::LABELS_BLOCK:{
                LabelBlock *f_labelsBlock = dynamic_cast<LabelBlock *>(f_block);
                if(f_labelsBlock){
                    return createIndex(row,column,f_labelsBlock->labels()->at(row));
                }
                break;
            }
            default:{
                return QModelIndex();
            }
        }
    }
    else if(dynamic_cast<ICurve*>(static_cast<QObject*>(parent.internalPointer()))){
        ICurve *f_curve = static_cast<ICurve *>(parent.internalPointer());
        if(f_curve){
            return createIndex(row,column,f_curve->desc());
        }
    }
    else if(dynamic_cast<Desc*>(static_cast<QObject*>(parent.internalPointer()))){
        Desc *f_desc = static_cast<Desc *>(parent.internalPointer());
        if(f_desc){
            if(!row)
                return createIndex(row,column,f_desc->parameters());
            else if(row == 1)
                return createIndex(row,column,f_desc->calibrations());
        }
    }
    else if(dynamic_cast<Parameters*>(static_cast<QObject*>(parent.internalPointer()))){
        Parameters *f_parameters = static_cast<Parameters *>(parent.internalPointer());
        if(f_parameters){
            Paraminfo *f_paramInfo = f_parameters->vectorParameters()->at(row);
            return createIndex(row,column,f_paramInfo);
        }
    }
    else if(dynamic_cast<SetLabelsForBoard*>(static_cast<QObject*>(parent.internalPointer()))){
        SetLabelsForBoard *f_setLabels = static_cast<SetLabelsForBoard *>(parent.internalPointer());
        if(f_setLabels){
            LDLabel *f_label = f_setLabels->labels()->at(row);
            return createIndex(row,column,f_label);
        }
    }
    return QModelIndex();
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
            QList<IBlock *> *f_blocks = logData->blocks();
            foreach(auto block,*f_blocks){
                if(block == f_block){
                    return createIndex(m_logDataVector->indexOf(logData),0,logData.get());
                }
            }
        }
    }
    else if(dynamic_cast<ICurve*>(static_cast<QObject*>(child.internalPointer()))){
        ICurve *f_curve = static_cast<ICurve *>(child.internalPointer());
        foreach(auto logData,*m_logDataVector){
            QList<IBlock *> *f_blocks = logData->blocks();
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
            QList<IBlock *> *f_blocks = logData->blocks();
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
            QList<IBlock *> *f_blocks = logData->blocks();
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
    else if(dynamic_cast<Desc *>((QObject*)child.internalPointer())){
        Desc *f_desc = dynamic_cast<Desc *>((QObject*)child.internalPointer());
        if(!f_desc)
            return QModelIndex();
        foreach(auto logData,*m_logDataVector){
            QList<IBlock *> *f_blocks = logData->blocks();
            foreach(auto block,*f_blocks){
                    DataBlock *f_dataBlock = dynamic_cast<DataBlock *>(block);
                    if(f_dataBlock){
                        QList<ICurve *> *f_curves = f_dataBlock->curves();
                        foreach(auto curve,*f_curves){
                            if(f_desc == curve->desc()){
                                return createIndex(f_curves->indexOf(curve),0,curve);
                            }
                        }
                    }
            }
        }
    }
    else if(dynamic_cast<Parameters *>((QObject*)child.internalPointer())){
        Parameters *f_parameters = dynamic_cast<Parameters *>((QObject*)child.internalPointer());
        if(!f_parameters)
            return QModelIndex();
        foreach(auto logData,*m_logDataVector){
            QList<IBlock *> *f_blocks = logData->blocks();
            foreach(auto block,*f_blocks){
                    DataBlock *f_dataBlock = dynamic_cast<DataBlock *>(block);
                    if(f_dataBlock){
                        QList<ICurve *> *f_curves = f_dataBlock->curves();
                        foreach(auto curve,*f_curves){
                            if(f_parameters == curve->desc()->parameters() || f_parameters == curve->desc()->calibrations()){
                                return createIndex(f_curves->indexOf(curve),0,curve->desc());
                            }
                        }
                    }
            }
        }
    }
    else if(dynamic_cast<Paraminfo *>((QObject*)child.internalPointer())){
        Paraminfo *f_paramInfo = dynamic_cast<Paraminfo *>((QObject*)child.internalPointer());
        if(!f_paramInfo)
            return QModelIndex();
        foreach(auto logData,*m_logDataVector){
            QList<IBlock *> *f_blocks = logData->blocks();
            foreach(auto block,*f_blocks){
                DataBlock *f_dataBlock = dynamic_cast<DataBlock *>(block);
                if(f_dataBlock){
                    QList<ICurve *> *f_curves = f_dataBlock->curves();
                    foreach(auto curve,*f_curves){
                        foreach(auto paramInfo,*curve->desc()->parameters()->vectorParameters() ){
                            if(f_paramInfo == paramInfo){
                                return createIndex(curve->desc()->parameters()->vectorParameters()->indexOf(paramInfo),0,curve->desc()->parameters());
                            }
                        }
                        foreach(auto paramInfo,*curve->desc()->calibrations()->vectorParameters()){
                            if(f_paramInfo == paramInfo){
                                return createIndex(curve->desc()->calibrations()->vectorParameters()->indexOf(paramInfo),0,curve->desc()->calibrations());
                            }
                        }

                    }
                }
            }
        }
    }
    else if(dynamic_cast<SetLabelsForBoard *>((QObject*)child.internalPointer())){
        //SetLabelsForBoard *f_setLabel = dynamic_cast<SetLabelsForBoard *>((QObject*)child.internalPointer());
        foreach(auto logData,*m_logDataVector){
            QList<IBlock *> *f_blocks = logData->blocks();
            foreach(auto block,*f_blocks){
                LabelBlock *f_labelBlock = dynamic_cast<LabelBlock *>(block);
                if(f_labelBlock){
                    return createIndex(f_blocks->indexOf(block),0,block);
                }
            }
        }
    }
    else if(dynamic_cast<LDLabel *>((QObject*)child.internalPointer())){
        LDLabel *f_label = dynamic_cast<LDLabel *>((QObject*)child.internalPointer());
        foreach(auto logData,*m_logDataVector){
            QList<IBlock *> *f_blocks = logData->blocks();
            foreach(auto block,*f_blocks){
                LabelBlock *f_labelBlock = dynamic_cast<LabelBlock *>(block);
                if(f_labelBlock){
                    SetLabelsForBoard *f_setLabel = f_labelBlock->labels(f_label->boardName());
                    return createIndex(f_labelBlock->labels()->indexOf(f_setLabel),0,f_setLabel);
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
                    QList<IBlock *> *f_blocks = logData->blocks();
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
            case IBlock::LABELS_BLOCK:{
                LabelBlock *f_LabelBlock = dynamic_cast<LabelBlock *>(f_block);
                if(f_LabelBlock){
                    return f_LabelBlock->labels()->size();
                }
                break;
            }
            default:{
                return 0;
            }
        }
    }
    else if(dynamic_cast<ICurve*>(static_cast<QObject*>(parent.internalPointer()))){
        return 1;
    }
    else if(dynamic_cast<Desc*>(static_cast<QObject*>(parent.internalPointer()))){
        return 2;
    }
    else if(dynamic_cast<Parameters*>(static_cast<QObject*>(parent.internalPointer()))){
        Parameters *f_parameters = dynamic_cast<Parameters*>(static_cast<QObject*>(parent.internalPointer()));
        if(!f_parameters)
            return 0;
        return f_parameters->vectorParameters()->size();
    }
    else if(dynamic_cast<SetLabelsForBoard*>(static_cast<QObject*>(parent.internalPointer()))){
        SetLabelsForBoard *f_setLabels = dynamic_cast<SetLabelsForBoard*>(static_cast<QObject*>(parent.internalPointer()));
        if(!f_setLabels)
            return 0;
        return f_setLabels->labels()->size();
    }
    return 0;
}

int DataModel::columnCount(const QModelIndex &parent )const{
    Q_UNUSED(parent)
    return 1;
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
                case IBlock::LABELS_BLOCK:{
                    return "LABELS";
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
            HeaderInfo *f_header = dynamic_cast<HeaderInfo *>(static_cast<QObject*>(index.internalPointer()));
            QTextEdit f_textEdit;
            f_textEdit.setHtml(f_header->name() + ":" + f_header->body());
            return  f_textEdit.toPlainText().replace(",","\n").replace("#(null)","the number is not known");
        }
        else if(dynamic_cast<Desc*>(static_cast<QObject*>(index.internalPointer()))){
            return "DESC";
        }
        else if(dynamic_cast<Parameters*>(static_cast<QObject*>(index.internalPointer()))){
            Parameters *f_parameters = dynamic_cast<Parameters *>(static_cast<QObject*>(index.internalPointer()));
            if(!f_parameters)
                return QModelIndex();
            if(f_parameters->type() == Parameters::PARAM)
                return tr("Parameters");
            else if(f_parameters->type() == Parameters::CALIB)
                return tr("Calibrations");
            else
                return QModelIndex();
        }
        else if(dynamic_cast<Paraminfo*>(static_cast<QObject*>(index.internalPointer()))){
            Paraminfo *f_paramInfo = dynamic_cast<Paraminfo *>(static_cast<QObject*>(index.internalPointer()));
            if(!f_paramInfo)
               return QModelIndex();
            return f_paramInfo->index() + " : " + f_paramInfo->value();
        }
        else if(dynamic_cast<SetLabelsForBoard *>((QObject*)index.internalPointer())){
            SetLabelsForBoard *f_setLabels = dynamic_cast<SetLabelsForBoard *>(static_cast<QObject*>(index.internalPointer()));
            return f_setLabels->nameBoard() + "(" + QString::number(f_setLabels->labels()->size()) + ")";
        }
        else if(dynamic_cast<LDLabel *>((QObject*)index.internalPointer())){
            LDLabel *f_label = dynamic_cast<LDLabel *>(static_cast<QObject*>(index.internalPointer()));
            return f_label->text();
        }

    }
    else if(role == Qt::ForegroundRole){
           //return QColor(Qt::black);
        return QVariant();
    }
    else if(role == Qt::ToolTipRole){
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
        else if(dynamic_cast<ICurve *>(static_cast<QObject*>(index.internalPointer()))){
            ICurve *f_curve = static_cast<ICurve *>(index.internalPointer());
            QString f_toolTip = "Mnemonic : " + f_curve->mnemonic() + "\n"
                    + "Record point : " + QString::number(f_curve->recordPoint()) + "\n"
                    + "Minimum : " + QString::number(f_curve->minimum()) + "\n"
                    + "Maximum : " + QString::number(f_curve->maximum()) + "\n";
            return f_toolTip;
        }
        else if(dynamic_cast<IBlock*>(static_cast<QObject*>(index.internalPointer()))){
            IBlock *f_block = static_cast<IBlock *>(index.internalPointer());
            IBlock::TypeBlock f_type = f_block->name();
            switch(f_type){
                case IBlock::DATA_BLOCK:{
                    DataBlock *f_dataBlock = dynamic_cast<DataBlock *>(f_block);
                    QList<ICurve *> *f_curves = f_dataBlock->curves();
                    QString f_toolTip;
                    foreach(auto curve,*f_curves){
                        f_toolTip += curve->mnemonic() + "\n";
                    }
                    return f_toolTip;
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
        else
            return QVariant();
    }
    else if(role == Qt::BackgroundRole){
        return QVariant();
    }
    else if(role == Qt::CheckStateRole){
        if (dynamic_cast<ILogData*>(static_cast<QObject*>(index.internalPointer()))){
            ILogData *f_logData = static_cast<ILogData *>(index.internalPointer());
            if(f_logData == m_curentLogData)
                return Qt::Checked;
            else
                return Qt::Unchecked;
        }
        return QVariant();
    }

    return QVariant();
}

Qt::ItemFlags DataModel::flags(const QModelIndex &index) const {
    if (!index.isValid())
        return Qt::NoItemFlags;
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
    Q_UNUSED(section)Q_UNUSED(orientation)Q_UNUSED(role)
    return QVariant();
}

bool DataModel::deleteBlock(IBlock *block){
    if(!block)
        return false;
    foreach(auto logData,*m_logDataVector){
        QList<IBlock *> *f_blocks = logData->blocks();
        if(!f_blocks)
            continue;
        if(f_blocks->removeOne(block)){
            update();
            return true;
        }
    }
    return false;
}
