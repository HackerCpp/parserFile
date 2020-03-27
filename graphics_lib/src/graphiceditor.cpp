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
