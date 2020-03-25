#include "verticalboard.h"



VerticalBoard::VerticalBoard(IBoard *board,QMap<QString,ICurve*> *curves)
    :m_board(board)
{
    init();
    QList<ATrack*> tracksInfo = board->getTrack();
    foreach(auto value,tracksInfo){
       m_canvas->addItem(new VerticalTrack(value));
    }
}

VerticalBoard::VerticalBoard(QMap<QString,ICurve*> *curves){
    init();
}

VerticalBoard::VerticalBoard(){
    init();
}

VerticalBoard::~VerticalBoard(){

}

void VerticalBoard::init(){
     m_canvas = new QGraphicsScene();
     setScene(m_canvas);

}

void VerticalBoard::mousePressEvent(QMouseEvent *event){

}

void VerticalBoard::mouseMoveEvent(QMouseEvent *event){

}

void VerticalBoard::mouseReleaseEvent(QMouseEvent *event){

}

