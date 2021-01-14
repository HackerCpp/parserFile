#include "graphiceditor.h"
#include "logdata.h"
#include "datablock.h"
#include "formsblock.h"
#include <stdio.h>
#include <customprogressbar.h>
#include <QInputDialog>

GraphicEditor::GraphicEditor(QSharedPointer<ILogData> logData,DrawSettings *drawSettings,QWidget *parent)
    : QTabWidget(parent),AGraphicEditor(logData),m_forms(nullptr),m_drawSettings(drawSettings){
    this->setStyleSheet("QGraphicsView{background-color:white;}");
    m_curves = new QMap<QString,ICurve*>;
    m_lastTabClicked = -1;
    m_tabMenu = QPointer<QMenu>(new QMenu(tr("&Forms menu")));
    m_tabMenu->addAction(tr("&Rename board"),this, SLOT(renameBoard()));
    m_tabMenu->addAction(tr("&Delete board"),this, SLOT(deleteBoard()));
    m_tabMenu->setMaximumSize(1000,1000);
    addCurves();
    addForms();
    tabBar()->installEventFilter(this); // установка фильтра обработки событий
    connect(this,&QTabWidget::tabBarClicked,this,&GraphicEditor::setCurrentIndexClick);
}

bool GraphicEditor::eventFilter(QObject *watched, QEvent *event){
    if (event->type() == QEvent::ContextMenu) {
        if(m_lastTabClicked == -1)
            return QObject::eventFilter(watched, event);
        m_tabMenu->move(cursor().pos());
        m_tabMenu->show();
    }
    else if(event->type() == QEvent::MouseButtonRelease){
        m_tabMenu->hide();
    }
    return QObject::eventFilter(watched, event); // обработка события по-умолчанию
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

    m_curentBoard = dynamic_cast<AGraphicBoard *>(currentWidget());
    if(m_curentBoard)
        m_curentBoard->activate(true);
    connect(this,&QTabWidget::currentChanged,this,&GraphicEditor::changeBoard);
    addTab(new QWidget(),"+");

}

void GraphicEditor::activate(bool active){
    if(!m_curentBoard)
        return;
    m_curentBoard->activate(active);
}

GraphicEditor::~GraphicEditor(){

}

void GraphicEditor::newBoard(){
    if(!m_forms){
        m_forms = dynamic_cast<FormsBlock*>(IBlock::blockCreater(IBlock::FORMS_BLOCK));
        m_logData->blocks()->push_front(m_forms);
    }
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

void GraphicEditor::setCurrentIndexClick(int index){
    m_lastTabClicked = index;
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
    blockSignals(true);
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
        if(f_board){
            f_board->activate(false);
            //delete f_board;//->deleteLater();
        }
        f_widget->deleteLater();
    }
    f_progressBar.setValue(f_progressBar.value() + f_stepPercent);
    if(m_curves){
        m_curves->clear();
    }
    f_progressBar.setText(tr("added"));
    addCurves();
    f_progressBar.setValue(75);
    addForms();
    f_progressBar.setValue(100);
    blockSignals(false);
}

void GraphicEditor::renameBoard(){
    AGraphicBoard *f_board = dynamic_cast<AGraphicBoard *>(widget(m_lastTabClicked));
    if(!f_board)
        return;

    bool bOk;
    QString f_name = QInputDialog::getText( 0, tr("Rename"),tr("New name:"),QLineEdit::Normal,
                                         f_board->boardInfo()->name(),&bOk);
    if (!bOk)
        return;

    tabBar()->setTabText(m_lastTabClicked,f_name);
    f_board->boardInfo()->setName(f_name);

}

void GraphicEditor::deleteBoard(){
    AGraphicBoard *f_board = dynamic_cast<AGraphicBoard *>(widget(m_lastTabClicked));
    if(!f_board)
        return;
    m_forms->boards()->removeOne(dynamic_cast<ABoard *>(f_board->boardInfo()));
    f_board->hide();
    removeTab(m_lastTabClicked);
    f_board->activate(false);
    delete f_board;f_board = nullptr;
}
