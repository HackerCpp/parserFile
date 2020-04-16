#include "objectoftheboard.h"
#include <QApplication>
#include <QScreen>

ObjectOfTheBoard::ObjectOfTheBoard(){
}

void ObjectOfTheBoard::changingTheVisibilityZone(QRectF newVisibilityZone){
    m_visibilitySquare = newVisibilityZone;
    redraw();
}


void ObjectOfTheBoard::redraw(){
    if(!isRunning()){
        m_endRedraw = false;
        start(QThread::InheritPriority);
    }
    else{
        m_endRedraw = true;
        m_needToRedraw = true;
    }
}
