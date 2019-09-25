#include "inc/tabs/tabgfm.h"
#include <QStyle>
#include <QDebug>

TabGFM::TabGFM(FileReader *file,QWidget *parent) : QWidget(parent){

    ParserGFM *pGfm = new ParserGFM(file);
    mainHLayout = new QHBoxLayout();
    QList<BlockGFM> * blocks = pGfm->getGFMBlocks();
    modelGfMScene = new ModelGFM(blocks);
    sceneWidget = new QWidget();
    graphicsView = new QGraphicsView(this);
    graphicsView->setStyleSheet("background:white");
    graphicsView->setOptimizationFlags(QGraphicsView::DontAdjustForAntialiasing|QGraphicsView::DontSavePainterState|QGraphicsView::IndirectPainting);
    mainHLayout = new QHBoxLayout();
    this->setLayout(mainHLayout);
    graphicsView->setScene(modelGfMScene);
    mainHLayout->addWidget(graphicsView);
}
