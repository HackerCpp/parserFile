#include "spectrscene.h"
#include "graphicitemforspectr.h"
#include "spectrviewer.h"

SpectrScene::SpectrScene(){
     m_lineItem = new QGraphicsLineItem;
     m_lineItem->setPen(QPen(Qt::black,2));
     m_lineItem->setZValue(100);
     m_textItem = new QGraphicsTextItem;
     m_textItem->setZValue(100);
     addItem(m_lineItem);
     addItem(m_textItem);
}

void SpectrScene::mousePressEvent(QGraphicsSceneMouseEvent *event){
    m_lineItem->setLine(0,event->scenePos().y(),width() - 10,event->scenePos().y());
    m_textItem->setPos(event->scenePos().x(),event->scenePos().y() - 40);

    QList<QGraphicsItem*> f_items = items();
    foreach(auto item,f_items){
        GraphicItemForSpectr * f_itemForSpectr = dynamic_cast<GraphicItemForSpectr *>(item);
        if(f_itemForSpectr){

            f_itemForSpectr->changePositionOneWave(QPoint(event->scenePos().x(),event->scenePos().y()));
        }
    }
    SpectrViewer *f_viewer = dynamic_cast<SpectrViewer *>(views().first());
    if(f_viewer){
        QPair<QString,qreal> f_mainVAlue = f_viewer->experimentalSpectr()->mainValueFromScene(event->scenePos());
        m_textItem->setPlainText(QString::number(f_mainVAlue.second) + f_mainVAlue.first);
        f_viewer->changePositionOneWave(QPoint(event->scenePos().x(),event->scenePos().y()));
    }
}

void SpectrScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event){
    m_lineItem->setLine(0,event->scenePos().y(),width() - 10,event->scenePos().y());
    m_textItem->setPos(event->scenePos().x(),event->scenePos().y() - 40);
    m_textItem->setPlainText(QString::number(event->scenePos().y()));
    QList<QGraphicsItem*> f_items = items();
    foreach(auto item,f_items){
        GraphicItemForSpectr * f_itemForSpectr = dynamic_cast<GraphicItemForSpectr *>(item);
        if(f_itemForSpectr){
            f_itemForSpectr->changePositionOneWave(QPoint(event->scenePos().x(),event->scenePos().y()));
        }
    }
    SpectrViewer *f_viewer = dynamic_cast<SpectrViewer *>(views().first());
    if(f_viewer){
        QPair<QString,qreal> f_mainVAlue = f_viewer->experimentalSpectr()->mainValueFromScene(event->scenePos());
        m_textItem->setPlainText(QString::number(f_mainVAlue.second) + f_mainVAlue.first);
        f_viewer->changePositionOneWave(QPoint(event->scenePos().x(),event->scenePos().y()));
    }
}
