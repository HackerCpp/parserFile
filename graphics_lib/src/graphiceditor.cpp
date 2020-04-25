#include "graphiceditor.h"



GraphicEditor::GraphicEditor(QMap<QString,ICurve*> *curves,FormsBlock *forms,QWidget *parent)
    : QTabWidget(parent),AGraphicEditor(curves,forms){
    this->setStyleSheet("QGraphicsView{background-color:white;}");
    QList<ABoard*> *boards = m_forms->boards();
    if(!boards){
        qDebug() << "FormsBlock Вернул нулевой указатель на борды";
        return;
    }
    foreach(auto boardInfo,*boards){
        AGraphicBoard *f_grBoard = new VerticalBoard(boardInfo,curves);
        addTab(f_grBoard,boardInfo->name());
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
    f_track->setNumber(0);
    f_track->setType(Types::LINEAR);
    f_track->setBegin(0);
    f_track->setWidth(40);
    f_track->setIsGreed(true);
    f_newBoard->setTrack(f_track);
    m_forms->boards()->push_back(f_newBoard);
    AGraphicBoard *f_grBoard = new VerticalBoard(f_newBoard,m_curves);
    m_curentBoard = f_grBoard;
    insertTab(count() - 1,f_grBoard,f_newBoard->name());
    setCurrentWidget(m_curentBoard);
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
