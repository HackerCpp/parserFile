#include "graphiceditor.h"
//#include "agraphicboard.h"
#include "SFML/Graphics.hpp"
using namespace sf;


GraphicEditor::GraphicEditor(QMap<QString,ICurve*> *curves,FormsBlock *forms,QWidget *parent)
    : QTabWidget(parent),AGraphicEditor(curves,forms){
    this->setStyleSheet("QGraphicsView{background-color:white;}");
    QList<ABoard*> *boards = forms->boards();
    if(!boards){
        qDebug() << "FormsBlock Вернул нулевой указатель на борды";
        return;
    }
    foreach(auto boardInfo,*boards){
        AGraphicBoard *grBoard = new VerticalBoard(boardInfo,curves);
        addTab(grBoard,boardInfo->name());
    }
    m_curentBoard = nullptr;
    connect(this,&QTabWidget::currentChanged,this,&GraphicEditor::changeBoard);
}

GraphicEditor::~GraphicEditor(){

}

void GraphicEditor::setDrawTime(){
    for(int i = 0; i < count();++i){
        AGraphicBoard * editor = dynamic_cast<AGraphicBoard *>(widget(i));
        if(editor)
            editor->setDrawTime();
        else{
            qDebug() << "Не удалось установить отрисовкупо времени ";
        }
    }
}

void GraphicEditor::setDrawDepth(){
    for(int i = 0; i < count();++i){
        AGraphicBoard * editor = dynamic_cast<AGraphicBoard *>(widget(i));
        if(editor)
            editor->setDrawDepth();
        else{
            qDebug() << "Не удалось установить отрисовку по глубине ";
        }
    }
}

void GraphicEditor::setFormatTime(AGraphicBoard::FormatTime format){
    for(int i = 0; i < count();++i){
        AGraphicBoard * editor = dynamic_cast<AGraphicBoard *>(widget(i));
        if(editor)
            editor->setFormatTime(format);
        else{
            qDebug() << "Не удалось установить отрисовку по глубине ";
        }
    }
}
void GraphicEditor::setFormatDepth(AGraphicBoard::FormatDepth format){
    for(int i = 0; i < count();++i){
        AGraphicBoard * editor = dynamic_cast<AGraphicBoard *>(widget(i));
        if(editor)
            editor->setFormatDepth(format);
        else{
            qDebug() << "Не удалось установить отрисовку по глубине ";
        }
    }
}

void GraphicEditor::setLengthPicture(AGraphicBoard::LengthPicture format){
    for(int i = 0; i < count();++i){
        AGraphicBoard * editor = dynamic_cast<AGraphicBoard *>(widget(i));
        if(editor)
            editor->setLengthPicture(format);
        else{
            qDebug() << "Не удалось установить длину картинки ";
        }
    }
}

void GraphicEditor::setFormatPicture(QImage::Format format){
    for(int i = 0; i < count();++i){
        AGraphicBoard * editor = dynamic_cast<AGraphicBoard *>(widget(i));
        if(editor)
            editor->setFormatPicture(format);
        else{
            qDebug() << "Не удалось установить формат картинки";
        }
    }
}

void GraphicEditor::changeBoard(int index){
    if(m_curentBoard)
        m_curentBoard->activate(false);
    AGraphicBoard *f_board = dynamic_cast<AGraphicBoard *>(widget(index));
    if(f_board){
        m_curentBoard = f_board;
        m_curentBoard->activate(true);
    }
}
