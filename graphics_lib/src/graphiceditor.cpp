#include "graphiceditor.h"
#include "logdata.h"
#include "datablock.h"
#include "formsblock.h"
#include <stdio.h>
#include <customprogressbar.h>


GraphicEditor::GraphicEditor(QSharedPointer<ILogData> logData,DrawSettings *drawSettings,QWidget *parent)
    : QTabWidget(parent),AGraphicEditor(logData),m_drawSettings(drawSettings){
    this->setStyleSheet("QGraphicsView{background-color:white;}");
    m_curves = new QMap<QString,ICurve*>;
    addCurves();
    addForms();
}

void GraphicEditor::addCurves(){
    if(!m_curves)
        return;

    foreach(auto block,*m_logData->blocks()){
         if(block->name() == IBlock::DATA_BLOCK){
           DataBlock *f_dataBlock = dynamic_cast<DataBlock*>(block);
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
    disconnect(this,&QTabWidget::currentChanged,this,&GraphicEditor::changeBoard);
    QList<ABoard*> *f_boards = nullptr;

    foreach(auto block,*m_logData->blocks()){
        if(block->name() == IBlock::FORMS_BLOCK){
            m_forms = dynamic_cast<FormsBlock *>(block);
            f_boards = m_forms->boards();
            if(!f_boards){
                qDebug() << "FormsBlock Вернул нулевой указатель на борды";
                return;
            }
        }
    }
    if(f_boards){
        foreach(auto boardInfo,*f_boards){
            AGraphicBoard *f_grBoard = new VerticalBoard(boardInfo,m_curves,m_drawSettings);
            addTab(f_grBoard,boardInfo->name());
            if(boardInfo->name() == m_forms->activeName()){
                setCurrentWidget(f_grBoard);
            }
        }
    }

    AGraphicBoard *f_board = dynamic_cast<AGraphicBoard *>(currentWidget());
    m_curentBoard = f_board;
    if(m_curentBoard)
        m_curentBoard->activate(true);

    addTab(new QWidget(),"+");
    connect(this,&QTabWidget::currentChanged,this,&GraphicEditor::changeBoard);
}

void GraphicEditor::activate(bool active){
    if(!m_curentBoard)
        return;
    m_curentBoard->activate(active);
}

GraphicEditor::~GraphicEditor(){

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
    AGraphicBoard *f_grBoard = new VerticalBoard(f_newBoard,m_curves,m_drawSettings);
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
    m_forms->setActiveName(tabText(index));
    AGraphicBoard *f_board = dynamic_cast<AGraphicBoard *>(widget(index));
    if(f_board){
        if(m_curentBoard)
            m_curentBoard->activate(false);
        m_curentBoard = f_board;
        if(m_curentBoard)
            m_curentBoard->activate(true);
    }
}

void GraphicEditor::refresh(){
    disconnect(this,&QTabWidget::currentChanged,this,&GraphicEditor::changeBoard);

    int f_count = count() - 1;
    m_curentBoard = nullptr;
    CustomProgressBar f_progressBar;
    f_progressBar.show();
    qreal f_stepPercent = 50.0 / f_count;
    f_progressBar.setRange(0,99);
    f_progressBar.setValue(0);
    f_progressBar.setText(tr("remove"));
    for(int index = f_count; index >= 0;index--){
        f_progressBar.setValue(f_progressBar.value() + f_stepPercent);
        QWidget *f_widget = widget(index);
        f_widget->hide();
        removeTab(index);
        VerticalBoard *f_board = dynamic_cast<VerticalBoard *>(f_widget);
        if(f_board)
            f_board->activate(false);
        delete f_widget;//->deleteLater();
    }
    f_progressBar.setValue(f_progressBar.value() + f_stepPercent);
    if(m_curves){
        m_curves->clear();
    }

    //qDebug() << "all deleted";
    f_progressBar.setText(tr("added"));
    addCurves();
    f_progressBar.setValue(75);
    //qDebug() << "curves added";
    addForms();
    //qDebug() << "forms added";
    f_progressBar.setValue(100);
}
