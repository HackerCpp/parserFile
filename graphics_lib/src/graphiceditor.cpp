#include "graphiceditor.h"
#include "verticalboard.h"

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
