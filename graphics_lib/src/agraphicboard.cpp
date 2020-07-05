#include "agraphicboard.h"
#include <QGraphicsScene>
#include "browsergraphicitems.h"

AGraphicBoard::AGraphicBoard(IBoard *boardInfo,QMap<QString,ICurve*> *curves,DrawSettings *drawSettings)
    : BoardForTrack(drawSettings),m_curves(curves),m_boardInfo(boardInfo){
    m_items = new QMap<QString,AGraphicItem *>;
    m_minimumSize = 2000;

}

AGraphicBoard::~AGraphicBoard(){
    if(m_items){
        foreach(auto item,*m_items){
           if(item){delete item;item = nullptr;}
        }
        delete m_items;m_items = nullptr;
    }

   //if(m_curves){delete m_curves;m_curves = nullptr;}
    m_boardInfo = nullptr;
}

void AGraphicBoard::resize(){
    QList<QGraphicsItem *> m_items = this->items();
    int f_width = 0;
    qreal f_topPosition = 1000000000000000000;
    qreal f_bottomPosition = -1000000000000000000;
    foreach(auto item, m_items){
        int rightPosition = item->boundingRect().x() + item->boundingRect().width();
        AGraphicTrack *f_track = dynamic_cast<AGraphicTrack *>(item);
        if(f_track){
            f_topPosition = f_topPosition < f_track->topValue() ? f_topPosition : f_track->topValue();
            f_bottomPosition = f_bottomPosition > f_track->bottomValue() ? f_bottomPosition : f_track->bottomValue();
        }
        f_width = (f_width > rightPosition ? f_width : rightPosition);
    }
    if(f_topPosition == 1000000000000000000){
        f_topPosition = -20;
        f_bottomPosition = 800;
    }
    m_top = f_topPosition - (20 * m_drawSettings->pixelPerMm());
    m_length = f_bottomPosition - m_top + (20 * m_drawSettings->pixelPerMm());
    if(m_length < 800)
        m_length = 800;
    setSceneRect(QRect(0,m_top,f_width,m_length));
    foreach(auto item, m_items){
        AGraphicTrack *f_track = dynamic_cast<AGraphicTrack *>(item);
        if(f_track){
            f_track->resize();
        }
        else{
            //qDebug() << "не удалось преобразовать QGraphicItem in AGraphicTrack;";
        }
    }
}


void AGraphicBoard::resizePicture(){
    QList<QGraphicsItem *> m_items = this->items();
    foreach(auto item, m_items){
        ObjectOfTheBoard *f_objectOfTheBoard = dynamic_cast<ObjectOfTheBoard *>(item);
        if(f_objectOfTheBoard){
           f_objectOfTheBoard->resizePictures();
        }
    }
}

void AGraphicBoard::activate(bool activate){
    QList<QGraphicsItem *> m_items = this->items();
    foreach(auto item, m_items){
        AGraphicTrack *f_track = dynamic_cast<AGraphicTrack *>(item);
        if(f_track){
           f_track->activate(activate);
        }
    }
}

void AGraphicBoard::updateItemsParam(){
    QList<QGraphicsItem *> m_items = this->items();
    foreach(auto item, m_items){
        AGraphicTrack *f_track = dynamic_cast<AGraphicTrack *>(item);
        if(f_track){
           f_track->updateItemsParam();
        }
    }
}

void AGraphicBoard::openCurveSettings(){
    BrowserGraphicItems *f_curveBrowser = new BrowserGraphicItems(m_boardInfo,m_items);
    connect(f_curveBrowser,&BrowserGraphicItems::changeSettings,this,&AGraphicBoard::curveUpdate);
    f_curveBrowser->show();
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

 void AGraphicBoard::curveUpdate(){
     distributionOfItemsBetweenTracks();
     updateItemsParam();
     redraw();
 }


