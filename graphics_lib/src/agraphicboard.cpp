#include "agraphicboard.h"
#include <QGraphicsScene>

AGraphicBoard::AGraphicBoard()
{
    m_minimumSize = 2000;
    setSceneRect(QRect(0,-10,m_minimumSize,m_minimumSize));
}

void AGraphicBoard::mousePressEvent(QMouseEvent *event){
     QGraphicsView::mousePressEvent(event);
 }

 void AGraphicBoard::mouseMoveEvent(QMouseEvent *event){
     QGraphicsView::mouseMoveEvent(event);
 }

 void AGraphicBoard::mouseReleaseEvent(QMouseEvent *event){
     QGraphicsView::mouseReleaseEvent(event);
 }
