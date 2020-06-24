#include "spectrreader.h"
#include <QGraphicsItem>
#include <QGraphicsView>
#include "verticaltrack.h"
#include <QScrollBar>
#include <QPushButton>
#include <QValidator>
#include <QGraphicsSceneMouseEvent>

void drawGrid(QPainter *per,int step,int widthLine){
    QImage *f_image = dynamic_cast<QImage*>(per->device());
    if(!f_image)
        return;
    per->setPen(QPen(Qt::black,widthLine));
    for(int i = f_image->height() - 2;i > 0;i -= step){
        per->drawLine(QPoint(0,i),QPoint(f_image->width(),i));
    }
    for(int i = 0;i < f_image->width();i += step){
        per->drawLine(QPoint(i,0),QPoint(i,f_image->height()));
    }
}

GraphicItemForSpectr::GraphicItemForSpectr(VSpectrItem *spectrItem,int width)
    :m_spectrItem(spectrItem){
    bool flag = false;
    m_curentImage = new QImage(width,m_spectrItem->board()->pictureHeight(),m_spectrItem->board()->formatPicture());
    m_curentOneWaveImage = new QImage(width,200,m_spectrItem->board()->formatPicture());
    QPainter f_painter(m_curentImage);
    m_curentImage->fill(0xffffffff);
    m_curentOneWaveImage->fill(0xffffffff);
    QPainter f_painterOneWave(m_curentOneWaveImage);
    drawGrid(&f_painterOneWave ,5 * m_spectrItem->board()->pixelPerMm(),1);
    m_spectrItem->drawOneWawe(&f_painterOneWave,1000,&flag);

    m_spectrItem->drawBody(&f_painter,QRectF(0,m_spectrItem->topValue(),m_curentImage->width(),1000),&flag);
}

void GraphicItemForSpectr::paint(QPainter *painter, const QStyleOptionGraphicsItem*, QWidget*){
    if(m_curentImage)
        painter->drawImage(QRect(0,m_visibilityZone.y() - m_spectrItem->board()->offsetUp(),m_curentImage->width(),m_curentImage->height()),*m_curentImage);
    if(m_curentOneWaveImage)
        painter->drawImage(QRect(0,m_visibilityZone.y() + m_visibilityZone.height() - m_curentOneWaveImage->height(),m_curentOneWaveImage->width(),m_curentOneWaveImage->height()),*m_curentOneWaveImage);
}

QRectF GraphicItemForSpectr::boundingRect()const {
    if(!m_curentImage)
        return QRectF();
    int f_upStock = 50;
    int f_height = m_spectrItem->bottomValue() - m_spectrItem->topValue() + m_curentOneWaveImage->height() + f_upStock * 2;
    return QRectF(0,m_spectrItem->topValue() - f_upStock,m_curentImage->width(),f_height);
}

void GraphicItemForSpectr::changeVisibilityZone(QRectF visibilityZone){
    m_visibilityZone = visibilityZone;
    QPainter f_painter(m_curentImage);
    m_curentImage->fill(0xffffffff);
    bool flag = false;

    m_spectrItem->drawBody(&f_painter,visibilityZone,&flag);
    QGraphicsItem::prepareGeometryChange();
    QGraphicsItem::update();
}

void GraphicItemForSpectr::changeSize(int width){
    bool flag = false;
    if(m_curentImage){delete m_curentImage; m_curentImage = nullptr;}
    if(m_curentOneWaveImage){delete m_curentOneWaveImage; m_curentOneWaveImage = nullptr;}
    m_curentImage = new QImage(width - 50,m_spectrItem->board()->pictureHeight(),m_spectrItem->board()->formatPicture());
    QPainter f_painter(m_curentImage);
    m_curentImage->fill(0xffffffff);
    m_curentOneWaveImage = new QImage(width - 50,200,m_spectrItem->board()->formatPicture());
    m_curentOneWaveImage->fill(0xffffffff);
    QPainter f_painterOneWave(m_curentOneWaveImage);
    drawGrid(&f_painterOneWave ,5 * m_spectrItem->board()->pixelPerMm(),1);
    m_spectrItem->drawOneWawe(&f_painterOneWave,m_spectrItem->topValue() + 1000,&flag);
    m_spectrItem->drawBody(&f_painter,m_visibilityZone,&flag);
    QGraphicsItem::prepareGeometryChange();
    QGraphicsItem::update();
}

void GraphicItemForSpectr::changePositionOneWave(QPoint position){
     bool flag = false;
     m_curentOneWaveImage->fill(0xffffffff);
    QPainter f_painterOneWave(m_curentOneWaveImage);
    drawGrid(&f_painterOneWave ,5 * m_spectrItem->board()->pixelPerMm(),1);
    m_spectrItem->drawOneWawe(&f_painterOneWave,position.y() ,&flag);
    QGraphicsItem::prepareGeometryChange();
    QGraphicsItem::update();
}
/************************SpectrScene************************************************************/
void SpectrScene::mousePressEvent(QGraphicsSceneMouseEvent *event){
    QList<QGraphicsItem*> f_items = items();
    foreach(auto item,f_items){
        GraphicItemForSpectr * f_itemForSpectr = dynamic_cast<GraphicItemForSpectr *>(item);
        if(f_itemForSpectr){
            f_itemForSpectr->changePositionOneWave(QPoint(event->scenePos().x(),event->scenePos().y()));
        }
    }
}

void SpectrScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event){
    QList<QGraphicsItem*> f_items = items();
    foreach(auto item,f_items){
        GraphicItemForSpectr * f_itemForSpectr = dynamic_cast<GraphicItemForSpectr *>(item);
        if(f_itemForSpectr){
            f_itemForSpectr->changePositionOneWave(QPoint(event->scenePos().x(),event->scenePos().y()));
        }
    }
}
/**************************SpectrWiever************************/
SpectrViewer::SpectrViewer(VSpectrItem *spectrItem,int width){
    m_scene = new SpectrScene;
    m_scene->addItem(new GraphicItemForSpectr(spectrItem,width));

    setScene(m_scene);

    connect(horizontalScrollBar(), &QScrollBar::valueChanged, this, &SpectrViewer::scrollChanged);
    connect(verticalScrollBar(), &QScrollBar::valueChanged, this, &SpectrViewer::scrollChanged);
}

SpectrViewer::~SpectrViewer(){

}

void SpectrViewer::changeWidth(int newWidth){
    QList<QGraphicsItem*> f_items = m_scene->items();
    foreach(auto item,f_items){
        GraphicItemForSpectr * f_itemForSpectr = dynamic_cast<GraphicItemForSpectr *>(item);
        if(f_itemForSpectr){
            f_itemForSpectr->changeSize(newWidth);
            setSceneRect(f_itemForSpectr->boundingRect());
        }
    }
}
void SpectrViewer::changeVisibilityZone(QRectF newVisibilityZone){
    QList<QGraphicsItem*> f_items = m_scene->items();
    foreach(auto item,f_items){
        GraphicItemForSpectr * f_itemForSpectr = dynamic_cast<GraphicItemForSpectr *>(item);
        if(f_itemForSpectr){
            f_itemForSpectr->changeVisibilityZone(newVisibilityZone);
            setSceneRect(f_itemForSpectr->boundingRect());
        }
    }
}

void SpectrViewer::scrollChanged(){
    QPolygonF f_rect = mapToScene(QRect(x(),y(),width(),height()));
    QRectF f_rectForScene = QRectF(f_rect[0].x(),f_rect[0].y(),f_rect[2].x() - f_rect[0].x(), f_rect[2].y() - f_rect[0].y());
    changeVisibilityZone(f_rectForScene);
}

/*void SpectrViewer::mousePressEvent(QMouseEvent *event){
    QList<QGraphicsItem*> f_items = m_scene->items();
    foreach(auto item,f_items){
        GraphicItemForSpectr * f_itemForSpectr = dynamic_cast<GraphicItemForSpectr *>(item);
        if(f_itemForSpectr){
            f_itemForSpectr->changePositionOneWave(QPoint(event->pos().x(),event->pos().y()));
        }
    }
}

void SpectrViewer::mouseMoveEvent(QMouseEvent *event){
    QList<QGraphicsItem*> f_items = m_scene->items();
    foreach(auto item,f_items){
        GraphicItemForSpectr * f_itemForSpectr = dynamic_cast<GraphicItemForSpectr *>(item);
        if(f_itemForSpectr){
            f_itemForSpectr->changePositionOneWave(QPoint(event->pos().x(),event->pos().y()));
        }
    }
}*/


/*************************************************************/
SpectrReader::SpectrReader(VSpectrItem *spectrItem)
{
    if(!spectrItem)
        return;
    setAcceptDrops(true);
    m_widht = 100;
    m_vMainLayout = new QVBoxLayout();

    m_spectrSplitter = new QSplitter();
    m_sliderWidth = new QSlider(Qt::Horizontal);
    m_sliderWidth->setRange(100,4000);
    m_sliderWidth->setValue(200);
    m_listSpectrViewer = new QList<SpectrViewer *>;

    m_listSpectrViewer->push_back(new SpectrViewer(spectrItem,m_sliderWidth->value()));
    foreach(auto value,*m_listSpectrViewer){
        m_spectrSplitter->addWidget(value);
    }
    m_toolBar = new QToolBar();

    m_toolBar->addWidget(m_sliderWidth);
    m_toolBar->addWidget(new QPushButton("btn2"));
    m_toolBar->addWidget(new QPushButton("btn3"));
    m_vMainLayout->addWidget(m_toolBar);
    m_vMainLayout->addWidget(m_spectrSplitter);

    setLayout(m_vMainLayout);

    connect(m_sliderWidth, &QSlider::valueChanged, this, &SpectrReader::sliderWidthChange);
}
void SpectrReader::changrVisibilityZone(QRectF visibilityRect){
    foreach(auto value,*m_listSpectrViewer){
        value->changeVisibilityZone(visibilityRect);
    }

}

void SpectrReader::resizeEvent(QResizeEvent *event){
    Q_UNUSED(event)
    /*QList<QGraphicsItem*> f_items = m_scene->items();
    foreach(auto item,f_items){
        GraphicItemForSpectr * f_itemForSpectr = dynamic_cast<GraphicItemForSpectr *>(item);
        if(f_itemForSpectr){
            f_itemForSpectr->changeSize(this->width());
        }
    }*/
    //scrollChanged();
}

void SpectrReader::sliderWidthChange(int width){
    foreach(auto value,*m_listSpectrViewer){
        value->changeWidth(width);
    }
}
void SpectrReader::dragEnterEvent(QDragEnterEvent *event){
    bool ok = false;
    AGraphicItem* f_item = reinterpret_cast<AGraphicItem*>(event->mimeData()->data("item").toLongLong(&ok));
    VSpectrItem *f_spectrItem = dynamic_cast<VSpectrItem *>(f_item);
    if(f_spectrItem){
        return event->setAccepted(true);
    }
    event->setAccepted(false);
}

void SpectrReader::dragMoveEvent(QDragMoveEvent *event){
    bool ok = false;
    AGraphicItem* f_item = reinterpret_cast<AGraphicItem*>(event->mimeData()->data("item").toLongLong(&ok));
    VSpectrItem *f_spectrItem = dynamic_cast<VSpectrItem *>(f_item);
    if(f_spectrItem){
        return event->setAccepted(true);
    }
    event->setAccepted(false);
}

void SpectrReader::dropEvent(QDropEvent *event){
    qDebug() << "drop";
    bool ok = false;
    AGraphicItem* f_item = reinterpret_cast<AGraphicItem*>(event->mimeData()->data("item").toLongLong(&ok));
    //AGraphicItem* f_item = reinterpret_cast<AGraphicItem*>(event->mimeData()->text().toLongLong(&ok));
    VSpectrItem *f_spectrItem = dynamic_cast<VSpectrItem *>(f_item);
    if(f_spectrItem){
        m_listSpectrViewer->push_back(new SpectrViewer(f_spectrItem,m_sliderWidth->value()));
        m_spectrSplitter->addWidget(m_listSpectrViewer->last());
    }
}


