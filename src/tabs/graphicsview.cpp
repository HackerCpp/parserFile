#include "inc/tabs/graphicsview.h"
#include <QDebug>
#include <QRect>
#include <QPolygonF>
#include <QScrollBar>
#include <QResizeEvent>




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
}

void OGLGraphicsView::resizeEvent( QResizeEvent * e){
    scrollBar();
}
