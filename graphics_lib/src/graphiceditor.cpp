#include "graphiceditor.h"
#include "logdata.h"
#include "datablock.h"
#include "formsblock.h"


GraphicEditor::GraphicEditor(QSharedPointer<ILogData> logData,QWidget *parent)
    : QTabWidget(parent),AGraphicEditor(logData){
    this->setStyleSheet("QGraphicsView{background-color:white;}");
    m_curves = new QMap<QString,ICurve*>;
    m_curentDrawType = 0;
    m_curentFormatTime = AGraphicBoard::MIN_SM_1;
    m_curentFormatdepth = AGraphicBoard::F1_100;
    m_curentLenghPicture = AGraphicBoard::MIN;
    m_curentImageFormat = QImage::Format_RGB16;
    addCurves();
    addForms();
}

void GraphicEditor::addCurves(){
    if(!m_curves)
        return;

    foreach(auto block,*m_logData->blocks()){
         if(block->name() == IBlock::DATA_BLOCK){
           DataBlock *f_dataBlock = dynamic_cast<DataBlock*>(block.data());
           if(f_dataBlock){
               QList<ICurve*> *f_curves = f_dataBlock->curves();
               if(!f_curves){
                   qDebug() << "В Дата блоке нет кривых для формирования дерева поиска";
                   continue;
               }

               foreach(auto curve,*f_curves){
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

void GraphicEditor::addForms(){
    if(!m_curves)
        return;
    QList<ABoard*> *f_boards = nullptr;

    foreach(auto block,*m_logData->blocks()){
        if(block->name() == IBlock::FORMS_BLOCK){
            m_forms = dynamic_cast<FormsBlock *>(block.data());
            f_boards = m_forms->boards();
            if(!f_boards){
                qDebug() << "FormsBlock Вернул нулевой указатель на борды";
                return;
            }

        }
     }
    if(f_boards){
        foreach(auto boardInfo,*f_boards){
            AGraphicBoard *f_grBoard = new VerticalBoard(boardInfo,m_curves);
            addTab(f_grBoard,boardInfo->name());
        }
    }

    AGraphicBoard *f_board = dynamic_cast<AGraphicBoard *>(currentWidget());
    m_curentBoard = f_board;

    addTab(new QWidget(),"+");
    connect(this,&QTabWidget::currentChanged,this,&GraphicEditor::changeBoard);

    setDrawType(m_curentDrawType);
    setFormatTime(m_curentFormatTime);
    setFormatDepth(m_curentFormatdepth);
    setLengthPicture(m_curentLenghPicture);
    setFormatPicture(m_curentImageFormat);
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

void GraphicEditor::setDrawType(int drawType){
    m_curentDrawType = drawType;
    drawType ? setDrawDepth() : setDrawTime();
}

void GraphicEditor::setFormatTime(AGraphicBoard::FormatTime format){
    m_curentFormatTime = format;
    for(int i = 0; i < count();++i){
        AGraphicBoard *editor = dynamic_cast<AGraphicBoard *>(widget(i));
        if(editor){
            editor->setFormatTime(format);
        }
    }
}
void GraphicEditor::setFormatDepth(AGraphicBoard::FormatDepth format){
    m_curentFormatdepth = format;
    for(int i = 0; i < count();++i){
        AGraphicBoard * editor = dynamic_cast<AGraphicBoard *>(widget(i));
        if(editor)
            editor->setFormatDepth(format);
    }
}

void GraphicEditor::setLengthPicture(AGraphicBoard::LengthPicture format){
    m_curentLenghPicture = format;
    for(int i = 0; i < count();++i){
        AGraphicBoard * editor = dynamic_cast<AGraphicBoard *>(widget(i));
        if(editor)
            editor->setLengthPicture(format);
    }
}

void GraphicEditor::setFormatPicture(QImage::Format format){
    m_curentImageFormat = format;
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

    f_grBoard->setFormatTime(m_curentFormatTime);
    f_grBoard->setFormatDepth(m_curentFormatdepth);
    m_curentDrawType ? f_grBoard->setDrawDepth() : f_grBoard->setDrawTime();
    f_grBoard->setFormatPicture(m_curentImageFormat);
    f_grBoard->setLengthPicture(m_curentLenghPicture);
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
    int f_count = count() - 1;
    for(int index = f_count; index >=0;index--){
        AGraphicBoard *f_board = dynamic_cast<AGraphicBoard *>(widget(index));
        if(f_board){
            delete f_board;
            f_board == nullptr;
        }
        else{
            delete widget(index);
        }
        removeTab(index);
    }

    addCurves();
    addForms();
}
