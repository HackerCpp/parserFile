#include "objectoftheboard.h"
#include <QApplication>
#include <QScreen>
#include <QGraphicsScene>

ObjectOfTheBoard::ObjectOfTheBoard()
    :m_curentPixmap(nullptr),m_doublePixMap(nullptr)
{
    connect(this,&ObjectOfTheBoard::finished,this,&ObjectOfTheBoard::sceneUpdate);
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
    QGraphicsItem::prepareGeometryChange();
    m_visibilitySquare = newVisibilityZone;
    redraw();
}


void ObjectOfTheBoard::redraw(){
    if(!isRunning()){
        m_endRedraw = false;
        start();
    }
    else{
        m_endRedraw = true;
        m_needToRedraw = true;
    }
}
void ObjectOfTheBoard:: toSetTheLocationOfTheImageAfterDrawing()
{
    ;
}
void ObjectOfTheBoard::sceneUpdate(){
    if(m_needToRedraw){
        m_needToRedraw = false;
        m_endRedraw = false;
        start();
    }
    else{
        if(scene())
            scene()->update();
    }
}

void ObjectOfTheBoard::swapPixMap(){
    QImage *ptr = m_curentPixmap;
    if(m_endRedraw){
        ptr = nullptr;
        return;
    }
    m_curentPixmap = m_doublePixMap;
    m_doublePixMap = ptr;
    ptr = nullptr;
    toSetTheLocationOfTheImageAfterDrawing();
}
