#include "igraphiceditor.h"
#include "datablock.h"


AGraphicEditor::AGraphicEditor(QSharedPointer<ILogData> logData){


    m_curves = new QMap<QString,ICurve*>;
    foreach(auto block,*logData->blocks()){
         if(block->name() == IBlock::DATA_BLOCK){
           DataBlock *dataBlock = dynamic_cast<DataBlock*>(block);
           if(dataBlock){
               QList<ICurve*> *curves = dataBlock->curves();
               if(!curves){
                   qDebug() << "В Дата блоке нет кривых для формирования дерева поиска";
                   continue;
               }

               foreach(auto curve,*curves){
                   if(!curve){
                       qDebug() << "Нулевая кривая в блоке";
                       continue;
                   }
                   if(!curve->shortCut().name().isEmpty()){
                       QString name = curve->shortCut().nameWithoutNumber() + ':' + curve->mnemonic();
                       m_curves->insert(name,curve);
                   }
               }
           }
        }
    }
}

AGraphicEditor::~AGraphicEditor(){

}

