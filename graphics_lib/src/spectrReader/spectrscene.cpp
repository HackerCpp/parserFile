#include "spectrscene.h"
#include "graphicitemforspectr.h"
#include "spectrviewer.h"

void SpectrScene::mousePressEvent(QGraphicsSceneMouseEvent *event){
    QList<QGraphicsItem*> f_items = items();
    foreach(auto item,f_items){
        GraphicItemForSpectr * f_itemForSpectr = dynamic_cast<GraphicItemForSpectr *>(item);
        if(f_itemForSpectr){
            f_itemForSpectr->changePositionOneWave(QPoint(event->scenePos().x(),event->scenePos().y()));
        }
    }
    SpectrViewer *f_viewer = dynamic_cast<SpectrViewer *>(views().first());
    if(f_viewer)
        f_viewer->changePositionOneWave(QPoint(event->scenePos().x(),event->scenePos().y()));
}

void SpectrScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event){
    QList<QGraphicsItem*> f_items = items();
    foreach(auto item,f_items){
        GraphicItemForSpectr * f_itemForSpectr = dynamic_cast<GraphicItemForSpectr *>(item);
        if(f_itemForSpectr){
            f_itemForSpectr->changePositionOneWave(QPoint(event->scenePos().x(),event->scenePos().y()));
        }
    }
    SpectrViewer *f_viewer = dynamic_cast<SpectrViewer *>(views().first());
    if(f_viewer)
        f_viewer->changePositionOneWave(QPoint(event->scenePos().x(),event->scenePos().y()));
}
