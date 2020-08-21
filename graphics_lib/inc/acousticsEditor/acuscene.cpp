#include "acuscene.h"
#include <QGraphicsLineItem>
#include <QGraphicsSceneMouseEvent>
#include "acuview.h"

AcuScene::AcuScene():m_isLeftMouseClick(false),m_isRightMouseClick(false){
    m_lineItem = new QGraphicsLineItem;
    m_lineItem->setPen(QPen(Qt::black,2));
    m_lineItem->setZValue(100);
    m_textItem = new QGraphicsTextItem;
    m_textItem->setZValue(100);
    addItem(m_lineItem);
    addItem(m_textItem);
}


void AcuScene::mousePressEvent(QGraphicsSceneMouseEvent *event){
    if(event->button() == Qt::LeftButton){
        m_lineItem->setLine(0,event->scenePos().y(),width() - 10,event->scenePos().y());
        m_textItem->setPos(event->scenePos().x(),event->scenePos().y() - 40);
        m_isLeftMouseClick = true;
    }
    else if(event->button() == Qt::RightButton){

        m_isRightMouseClick = true;
    }
}

void AcuScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event){
    if(m_isLeftMouseClick){
        m_lineItem->setLine(0,event->scenePos().y(),width() - 10,event->scenePos().y());
        m_textItem->setPos(event->scenePos().x(),event->scenePos().y() - 40);
        m_textItem->setPlainText(QString::number(event->scenePos().y()));

        AcuView *f_viewer = dynamic_cast<AcuView *>(views().first());
        if(f_viewer){
            f_viewer->changePositionOneWave(QPoint(event->scenePos().x(),event->scenePos().y()));
        }
    }
    if(m_isRightMouseClick){

    }
}

void AcuScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event){
    if(event->button() == Qt::LeftButton)
        m_isLeftMouseClick = false;
    else if(event->button() == Qt::RightButton){
        m_isRightMouseClick = false;
    }
    update();
}
