#include "graphiceditor.h"
#include "logdata.h"
#include "datablock.h"
#include "formsblock.h"


GraphicEditor::GraphicEditor(QSharedPointer<ILogData> logData,QWidget *parent)
    : QTabWidget(parent),AGraphicEditor(logData){
    this->setStyleSheet("QGraphicsView{background-color:white;}");
    addCurves(m_logData);
    addForms(m_logData);


}
void GraphicEditor::addCurves(QSharedPointer<ILogData> logData)
{


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
void GraphicEditor::addForms(QSharedPointer<ILogData> logData){

    QList<ABoard*> *f_boards = nullptr;

    foreach(auto block,*logData->blocks()){
        if(block->name() == IBlock::FORMS_BLOCK){
            FormsBlock *formBlock = dynamic_cast<FormsBlock*>(block);

            m_forms = formBlock;

           f_boards = m_forms->boards();
            if(!f_boards){
                qDebug() << "FormsBlock Вернул нулевой указатель на борды";
                return;
            }

        }
     }

    if(f_boards)
    {
        foreach(auto boardInfo,*f_boards){
            AGraphicBoard *f_grBoard = new VerticalBoard(boardInfo,m_curves);
            addTab(f_grBoard,boardInfo->name());
        }
    }

    AGraphicBoard *f_board = dynamic_cast<AGraphicBoard *>(currentWidget());
    m_curentBoard = f_board;

    addTab(new QWidget(),"+");
    connect(this,&QTabWidget::currentChanged,this,&GraphicEditor::changeBoard);

}
GraphicEditor::~GraphicEditor(){

}

void GraphicEditor::setDrawTime(){
    for(int i = 0; i < count();++i){
        AGraphicBoard * editor = dynamic_cast<AGraphicBoard *>(widget(i));
        if(editor)
            editor->setDrawTime();
    }
}

void GraphicEditor::setDrawDepth(){
    for(int i = 0; i < count();++i){
        AGraphicBoard * editor = dynamic_cast<AGraphicBoard *>(widget(i));
        if(editor)
            editor->setDrawDepth();
    }
}

void GraphicEditor::setFormatTime(AGraphicBoard::FormatTime format){
    for(int i = 0; i < count();++i){
        AGraphicBoard * editor = dynamic_cast<AGraphicBoard *>(widget(i));
        if(editor)
            editor->setFormatTime(format);
    }
}
void GraphicEditor::setFormatDepth(AGraphicBoard::FormatDepth format){
    for(int i = 0; i < count();++i){
        AGraphicBoard * editor = dynamic_cast<AGraphicBoard *>(widget(i));
        if(editor)
            editor->setFormatDepth(format);
    }
}

void GraphicEditor::setLengthPicture(AGraphicBoard::LengthPicture format){
    for(int i = 0; i < count();++i){
        AGraphicBoard * editor = dynamic_cast<AGraphicBoard *>(widget(i));
        if(editor)
            editor->setLengthPicture(format);
    }
}

void GraphicEditor::setFormatPicture(QImage::Format format){
    for(int i = 0; i < count();++i){
        AGraphicBoard * editor = dynamic_cast<AGraphicBoard *>(widget(i));
        if(editor)
            editor->setFormatPicture(format);
    }
}

void GraphicEditor::newBoard(){
    ABoard* f_newBoard = new ABoard();
    f_newBoard->setName("noName");
    ATrack * f_track = new ATrack();
    f_track->setNumber(1);
    f_track->setType(Types::LINEAR);
    f_track->setBegin(0);
    f_track->setWidth(80);
    f_track->setIsGreed(true);
    f_newBoard->setTrack(f_track);
    m_forms->boards()->push_back(f_newBoard);
    AGraphicBoard *f_grBoard = new VerticalBoard(f_newBoard,m_curves);
    m_curentBoard = f_grBoard;
    insertTab(count() - 1,f_grBoard,f_newBoard->name());
    setCurrentWidget(m_curentBoard);
    m_curentBoard->insertNewTrack(1,InsertPossition::LEFT);
}

void GraphicEditor::changeBoard(int index){
    if(tabText(index) == "+"){
        newBoard();
        return;
    }
    for(int i = 0; i < count();++i){
        AGraphicBoard *f_board = dynamic_cast<AGraphicBoard *>(widget(i));
        if(f_board)
            f_board->activate(false);
    }

    AGraphicBoard *f_board = dynamic_cast<AGraphicBoard *>(widget(index));
    if(f_board){
        m_curentBoard = f_board;
        m_curentBoard->activate(true);
    }
}
void GraphicEditor::refresh(){

    if(m_curves){

        m_curves->clear();
    }

    addCurves(m_logData);
    addForms(m_logData);
}
