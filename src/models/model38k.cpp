#include "inc/models/model38k.h"
#include "inc/fileCreation/csv.h"
#include <QMessageBox>

SaveCSVModal::SaveCSVModal(QList<PacketModulesData38k> * data):m_data(data){
     horBoxLayout = new QHBoxLayout;
     vBoxLayoutType = new QVBoxLayout;
     vBoxLayoutSeparator = new QVBoxLayout;
     labelType = new QLabel("module type:");
     labelSeparator = new QLabel("separator:");
     comboBox = new QComboBox;
     lineEdit = new QLineEdit;
     lineEdit->setText(",");
     btnOk = new QPushButton("OK");
     btnCansel = new QPushButton("Cancel");
     vBoxLayoutType->addWidget(labelType);
     vBoxLayoutType->addWidget(comboBox);
     vBoxLayoutType->addWidget(btnOk);
     vBoxLayoutSeparator->addWidget(labelSeparator);
     vBoxLayoutSeparator->addWidget(lineEdit);
     vBoxLayoutSeparator->addWidget(btnCansel);
     horBoxLayout->addLayout(vBoxLayoutType);
     horBoxLayout->addLayout(vBoxLayoutSeparator);
     this->setLayout(horBoxLayout);
     QList<QString> modList;
     bool added = true;
     foreach(PacketModulesData38k data,*m_data){
         if(!data.dataStruct)
             continue;
         foreach(QString module,modList)
            if(this->modArray[data.dataStruct->type] == module){
                added = false;
                continue;
            }
         if(added){
             modList << this->modArray[data.dataStruct->type];
         }
         added = true;
     }
     this->comboBox->addItems(modList);
     connect(this->btnOk, SIGNAL(clicked(bool)), this, SLOT(saveFile(void)));
     connect(this->btnCansel, SIGNAL(clicked(bool)), this, SLOT(cansel(void)));

}

void SaveCSVModal::saveFile(){
    int index = 0;
    index = this->modArray.indexOf(this->comboBox->currentText());
    CSV *saveFile = new CSV(this->m_data,index,this->lineEdit->text());
    delete this;
}
void SaveCSVModal::cansel(){
    this->~SaveCSVModal();
}
SaveCSVModal::~SaveCSVModal(){
    delete labelType;
    delete labelSeparator;
    delete comboBox;
    delete lineEdit;
    delete btnOk;
    delete btnCansel;
    delete vBoxLayoutType;
    delete vBoxLayoutSeparator;
    delete horBoxLayout;
}

Model38k::Model38k(QList<PacketModulesData38k> *modulesData){
    this->modulesData = new QList<PacketModulesData38k>;
    parserModules = nullptr;
    size = 0;
    if(modulesData == nullptr)
        return;

    for (auto modData = modulesData->begin();modData < modulesData->end();modData++){
        this->modulesData->push_back(*modData);
    }
    size = modulesData->size();
}

QVariant Model38k::data(const QModelIndex &index, int role ) const{
    if (role != Qt::DisplayRole)
        return QVariant();
    if (!index.isValid())
        return QVariant();
    if (index.row() >= size)
        return QVariant();
    int column = index.column();
    switch (column){
         case 0:
             return this->modulesData->at(index.row()).header.moduleAddress;
         case 1:
             return this->modulesData->at(index.row()).header.data_state;
         case 2:
             return this->modulesData->at(index.row()).header.totalSize;
         case 3:
             return this->modulesData->at(index.row()).header.totalDataSize;
         case 4:
             return modulesData->at(index.row()).header.totalParts;
         case 5:
             return modulesData->at(index.row()).header.currentPartNo;
         case 6:
            return modulesData->at(index.row()).header.lastCommandState;
        case 7:
            return modulesData->at(index.row()).header.commandCounter;
        case 8:
            return modulesData->at(index.row()).header.lastCommandCrc;
        case 9:
            return modulesData->at(index.row()).header.lastCommandCode;
        case 10:
            return modulesData->at(index.row()).header.requestTime;
         default:
             return QVariant();
      }
}

int Model38k::rowCount(const QModelIndex &parent) const {
    return size;
}

int Model38k::columnCount(const QModelIndex &parent) const {
    return 11;
}

QVariant Model38k::headerData(int section, Qt::Orientation orientation, int role) const{
    if (role != Qt::DisplayRole)
       return QVariant();
    if (orientation == Qt::Horizontal){
        return headerArray[section];
    }
    else if(orientation == Qt::Vertical)
        return section;
    return QVariant();
}

Qt::ItemFlags Model38k::flags(const QModelIndex &index) const{
    return Qt :: ItemIsEnabled | Qt :: ItemIsSelectable | Qt :: ItemNeverHasChildren;
}

 void Model38k::setData(PacketModulesData38k pack){
    beginInsertRows(QModelIndex(),size, size);
    this->modulesData->push_back(pack);
    size++;
    endInsertRows();
}
 void Model38k::startParsingMdules(){
     parserModules = new Parser38kModules(this->modulesData);
     connect(parserModules, SIGNAL(finished(void)), this, SLOT(stopParsingMdules(void)));
     parserModules->start();
 }
 void Model38k::stopParsingMdules(){
     if(parserModules)
        parserModules->stop();
     parserModules = nullptr;
 }
 void Model38k::saveFile(){
     if(parserModules){
        QMessageBox::warning(nullptr,"Обратите внимание", "Дождитесь полного разбора файла",QMessageBox::Ok);
        return;
     }
     SaveCSVModal *mod = new SaveCSVModal(this->modulesData);
     mod->show();
 }
Model38k::~Model38k(){
    if(parserModules)
        parserModules->stop();
    parserModules = nullptr;
    for(auto value = modulesData->begin();value < modulesData->end();value++)
        if(value->dataStruct){
            if(value->dataStruct->type == SHM){
                DataSHM1 *s = reinterpret_cast<DataSHM1*>(value->dataStruct);
                if(s->Wave_1int)
                    delete s->Wave_1int;
                if(s->Wave_1float)
                    delete s->Wave_1float;
                delete s;
            }
            else if(!value->dataStruct->type)
                delete reinterpret_cast<DataGKT*>(value->dataStruct);
            else if(value->dataStruct->type == AG)
                delete reinterpret_cast<DataAG*>(value->dataStruct);
            else
                 delete value->dataStruct;
        }

    delete this->modulesData;
    this->modulesData = nullptr;
}


