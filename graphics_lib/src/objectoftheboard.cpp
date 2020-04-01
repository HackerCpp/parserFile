#include "objectoftheboard.h"
#include <QApplication>
#include <QScreen>

ObjectOfTheBoard::ObjectOfTheBoard(){
}

void ObjectOfTheBoard::changingTheVisibilityZone(QRect newVisibilityZone){
    m_visibilitySquare = newVisibilityZone;
    redraw();
}


void ObjectOfTheBoard::redraw(){
    if(!isRunning())
        start(QThread::InheritPriority);
    else
        m_needToRedraw = true;
}
