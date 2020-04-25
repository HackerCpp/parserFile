#include "objectoftheboard.h"
#include <QApplication>
#include <QScreen>

ObjectOfTheBoard::ObjectOfTheBoard()
    :m_curentPixmap(nullptr),m_doublePixMap(nullptr)
{
}

ObjectOfTheBoard::~ObjectOfTheBoard(){
    m_endRedraw = true;
    wait();
    if(m_curentPixmap){
        delete m_curentPixmap; m_curentPixmap = nullptr;
    }
    if(m_doublePixMap){
        delete m_doublePixMap; m_doublePixMap = nullptr;
    }
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
