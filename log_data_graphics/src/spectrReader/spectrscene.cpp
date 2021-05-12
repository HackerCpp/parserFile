#include "spectrscene.h"
#include "graphicitemforspectr.h"
#include "spectrviewer.h"

SpectrScene::SpectrScene()
    :m_isLeftMouseClick(false),m_isRightMouseClick(false){
     m_lineItem = new QGraphicsLineItem;
     m_selectingArea = new SelectingArea(QRectF(0,0,1,1));
     m_selectingArea->setZValue(100);
     m_lineItem->setPen(QPen(Qt::black,2));
     m_lineItem->setZValue(100);
     m_textItem = new QGraphicsTextItem;
     m_textItem->setZValue(100);
     addItem(m_lineItem);
     addItem(m_textItem);
     addItem(m_selectingArea);
}

void SpectrScene::mousePressEvent(QGraphicsSceneMouseEvent *event){
    if(event->button() == Qt::LeftButton){
        m_lineItem->setLine(0,event->scenePos().y(),width() - 10,event->scenePos().y());
        m_textItem->setPos(event->scenePos().x(),event->scenePos().y() - 40);
        QList<QGraphicsItem*> f_items = items();
        SpectrViewer *f_viewer = dynamic_cast<SpectrViewer *>(views().first());
        if(f_viewer){
            QPair<QString,qreal> f_mainVAlue = f_viewer->experimentalSpectr()->mainValueFromScene(event->scenePos());
            m_textItem->setPlainText(QString::number(f_mainVAlue.second) + f_mainVAlue.first);
            f_viewer->changePositionOneWave(QPoint(event->scenePos().x(),event->scenePos().y()));
        }
        m_isLeftMouseClick = true;
    }
    else if(event->button() == Qt::RightButton){
        m_selectingArea->setPosition(event->scenePos());
        m_selectingArea->setWidth(1);
        m_selectingArea->setHeight(1);
        m_selectingArea->show();
        SpectrViewer *f_viewer = dynamic_cast<SpectrViewer *>(views().first());
        if(f_viewer){
            f_viewer->changeSelectedArea(m_selectingArea->boundingRect());
        }

        m_isRightMouseClick = true;
    }
}

void SpectrScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event){
    if(m_isLeftMouseClick){
        m_lineItem->setLine(0,event->scenePos().y(),width() - 10,event->scenePos().y());
        m_textItem->setPos(event->scenePos().x(),event->scenePos().y() - 40);
        m_textItem->setPlainText(QString::number(event->scenePos().y()));

        QList<QGraphicsItem*> f_items = items();
        SpectrViewer *f_viewer = dynamic_cast<SpectrViewer *>(views().first());
        if(f_viewer){
            QPair<QString,qreal> f_mainVAlue = f_viewer->experimentalSpectr()->mainValueFromScene(event->scenePos());
            m_textItem->setPlainText(QString::number(f_mainVAlue.second) + f_mainVAlue.first);
            f_viewer->changePositionOneWave(QPoint(event->scenePos().x(),event->scenePos().y()));
        }
    }
    if(m_isRightMouseClick){
        m_selectingArea->setCurrentPosition(event->scenePos());
        SpectrViewer *f_viewer = dynamic_cast<SpectrViewer *>(views().first());
        if(f_viewer){
            f_viewer->changeSelectedArea(m_selectingArea->boundingRect());
        }
        update();
    }
}

void SpectrScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event){
    if(event->button() == Qt::LeftButton)
        m_isLeftMouseClick = false;
    else if(event->button() == Qt::RightButton){
        //m_selectingArea->hide();
        m_isRightMouseClick = false;
    }
    update();
}
