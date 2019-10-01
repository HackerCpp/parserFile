#include "inc/tabs/graphicsview.h"
#include <QDebug>
#include <QRect>
#include <QPolygonF>
#include <QScrollBar>




OGLGraphicsView::OGLGraphicsView(QWidget *parent): QGraphicsView(parent){
    this->setupViewport(new QGLWidget(QGLFormat(QGL::DoubleBuffer)));
    connect(this->horizontalScrollBar(), &QScrollBar::valueChanged, this, &OGLGraphicsView::scrollBar);
    connect(this->verticalScrollBar(), &QScrollBar::valueChanged, this, &OGLGraphicsView::scrollBar);
}
void OGLGraphicsView::scrollBar(){
    QPolygonF rect = mapToScene(QRect(0,0,width(),height()));
    if(rect.isEmpty())
        return;
    emit scrollChange(rect.first().x(),rect.first().y(),(rect.begin()+2)->x(),(rect.begin()+2)->y());
    this->setSceneRect(QRect(-50,0,width()-50,sceneRect().height()));
}
