#include "inc/tabs/tabgfm.h"
#include <QStyle>
#include <QDebug>


TabGFM::TabGFM(FileReader *file,QWidget *parent) : QWidget(parent){

    ParserGFM *pGfm = new ParserGFM(file);
    mainHLayout = new QHBoxLayout();
    QList<BlockGFM> * blocks = pGfm->getGFMBlocks();
    modelGfMScene = new ModelGFM(blocks);
    sceneWidget = new QWidget();
    graphicsView = new OGLGraphicsView(this);
    graphicsView->setStyleSheet("background:white");
    mainHLayout = new QHBoxLayout();
    this->setLayout(mainHLayout);
    graphicsView->setScene(modelGfMScene);
    modelGfMScene->connectView();
    mainHLayout->addWidget(graphicsView);
    connect(this,&TabGFM::tabGFMNewSize,graphicsView,&OGLGraphicsView::scrollBar);
}
void TabGFM::resizeEvent ( QResizeEvent * e){
    emit this->tabGFMNewSize(e->size());
    QWidget::resizeEvent(e);
}
