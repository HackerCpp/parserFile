#include "acuview.h"
#include "acousticsEditor/countingacousticsitem.h"
#include <QScrollBar>

AcuView::AcuView(DataCountingAcoustics *dataCounting)
{
    m_scene = new AcuScene();
    m_scene->addItem(new CountingAcousticsItem(dataCounting,500));
    this->setScene(m_scene);

    connect(horizontalScrollBar(), &QScrollBar::valueChanged, this, &AcuView::scrollChanged);
    connect(verticalScrollBar(), &QScrollBar::valueChanged, this, &AcuView::scrollChanged);
}

AcuView::~AcuView(){

}

void AcuView::changeWidth(int newWidth){
    QList<QGraphicsItem*> f_items = m_scene->items();
    foreach(auto item,f_items){
        CountingAcousticsItem * f_item = dynamic_cast<CountingAcousticsItem *>(item);
        if(f_item){
            f_item->changeSize(newWidth);
            setSceneRect(f_item->boundingRect());
        }
    }
}

void AcuView::changeVisibilityZone(QRectF newVisibilityZone){
    QList<QGraphicsItem*> f_items = m_scene->items();
    foreach(auto item,f_items){
        CountingAcousticsItem * f_item = dynamic_cast<CountingAcousticsItem *>(item);
        if(f_item){
            f_item->changeVisibilityZone(newVisibilityZone);
            setSceneRect(f_item->boundingRect());
        }
    }
}

void AcuView::resizeEvent(QResizeEvent *event){
    scrollChanged();
}

void AcuView::changePositionOneWave(QPoint position){
    emit sig_changePositionOneWave(position);
}

void AcuView::changeSelectedArea(QRectF rectSelectedArea){

}

void AcuView::scrollChanged(){
    QPolygonF f_rect = mapToScene(QRect(x(),y(),width(),height()));
    QRectF f_rectForScene = QRectF(f_rect[0].x(),f_rect[0].y(),f_rect[2].x() - f_rect[0].x(), f_rect[2].y() - f_rect[0].y());
    changeVisibilityZone(f_rectForScene);
}
