#include "spectrreader.h"
#include <QGraphicsItem>
#include <QGraphicsView>
#include "verticaltrack.h"
#include <QScrollBar>
#include <QPushButton>
#include <QValidator>
#include <QGraphicsSceneMouseEvent>
#include "Wrapper_python.h"
#include <QDir>
#include <QGraphicsProxyWidget>


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
    m_curentPixmap = new QImage(width,m_spectrItem->board()->pictureHeight(),m_spectrItem->board()->formatPicture());
    m_doublePixMap = new QImage(width,m_spectrItem->board()->pictureHeight(),m_spectrItem->board()->formatPicture());
    m_curentOneWaveImage = new QImage(width,200,m_spectrItem->board()->formatPicture());
    m_curentHeaderImage = new QImage(100,40,m_spectrItem->board()->formatPicture());
    m_curentHeaderImage->fill(0x0);
    QPainter f_painterHeader(m_curentHeaderImage);
    int position = 0;
    m_spectrItem->drawHeader(&f_painterHeader,position,&flag);
    QPainter f_painter(m_curentPixmap);
    m_curentPixmap->fill(0xffffffff);
    m_curentOneWaveImage->fill(0xffffffff);
    QPainter f_painterOneWave(m_curentOneWaveImage);
    drawGrid(&f_painterOneWave ,5 * m_spectrItem->board()->pixelPerMm(),1);
    m_spectrItem->drawOneWawe(&f_painterOneWave,1000,&flag);

    m_spectrItem->drawBody(&f_painter,QRectF(0,m_spectrItem->topValue(),m_curentPixmap->width(),1000),&flag);
    connect(m_spectrItem,&VSpectrItem::dataHardDiscReady,this,&GraphicItemForSpectr::redraw);
}

void GraphicItemForSpectr::paint(QPainter *painter, const QStyleOptionGraphicsItem*, QWidget*){
    if(m_curentPixmap)
        painter->drawImage(QRect(0,m_topPositionPicture,m_curentPixmap->width(),m_curentPixmap->height()),*m_curentPixmap);
    if(m_curentOneWaveImage)
        painter->drawImage(QRect(0,m_visibilitySquare.y() + m_visibilitySquare.height() - m_curentOneWaveImage->height(),m_curentOneWaveImage->width(),m_curentOneWaveImage->height()),*m_curentOneWaveImage);
    if(m_curentHeaderImage)
        painter->drawImage(QRect(m_visibilitySquare.x(),m_visibilitySquare.y(),m_curentHeaderImage->width(),m_curentHeaderImage->height()),*m_curentHeaderImage);
}

QRectF GraphicItemForSpectr::boundingRect()const {
    if(!m_curentPixmap)
        return QRectF();
    int f_upStock = 50;
    int f_height = m_spectrItem->bottomValue() - m_spectrItem->topValue() + m_curentOneWaveImage->height() + f_upStock * 2;
    return QRectF(0,m_spectrItem->topValue() - f_upStock,m_curentPixmap->width(),f_height);
}

void GraphicItemForSpectr::toSetTheLocationOfTheImageAfterDrawing(){
    m_topPositionPicture = static_cast<int>(m_visibilitySquare.y() - m_spectrItem->board()->offsetUp());
}

void GraphicItemForSpectr::changeVisibilityZone(QRectF visibilityZone){
    m_visibilitySquare = visibilityZone;
    redraw();
}

void GraphicItemForSpectr::changeSize(int width){
    m_endRedraw = true;
    bool flag = false;
    m_spectrItem->updateParam(width);
    wait();
    if(m_curentPixmap){delete m_curentPixmap; m_curentPixmap = nullptr;}
    m_curentPixmap = new QImage(width - 50,m_spectrItem->board()->pictureHeight(),m_spectrItem->board()->formatPicture());

    if(m_doublePixMap){delete m_doublePixMap; m_doublePixMap = nullptr;}
    m_doublePixMap = new QImage(width - 50,m_spectrItem->board()->pictureHeight(),m_spectrItem->board()->formatPicture());
    m_curentPixmap->fill(0xffffffff);
    if(m_curentOneWaveImage){delete m_curentOneWaveImage; m_curentOneWaveImage = nullptr;}
    m_curentOneWaveImage = new QImage(width - 50,200,m_spectrItem->board()->formatPicture());
    m_curentOneWaveImage->fill(0xffffffff);
    QPainter f_painterOneWave(m_curentOneWaveImage);
    drawGrid(&f_painterOneWave ,5 * m_spectrItem->board()->pixelPerMm(),1);
    m_spectrItem->drawOneWawe(&f_painterOneWave,m_spectrItem->topValue() + 1000,&flag);

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

void GraphicItemForSpectr::run(){
    QPainter f_painter(m_doublePixMap);
    m_doublePixMap->fill(0xffffffff);
    m_spectrItem->drawBody(&f_painter,m_visibilitySquare,&m_endRedraw);
    swapPixMap();
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
    m_radioBtnIsActive = new QRadioButton("ACtive",this);
    m_originalSpectr = spectrItem;
    m_experimentalSpectr = new VSpectrItem(*spectrItem);
    if(m_experimentalSpectr){
        m_experimentalSpectr->updateParam(width);
        m_scene->addItem(new GraphicItemForSpectr(m_experimentalSpectr,width));
    }
    else{
        qDebug() << "Не удалось создать копию спектра в редакторе, конструктор копирования вернул nullptr";
    }

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
void SpectrViewer::resizeEvent(QResizeEvent *event){
    scrollChanged();
}
/***************************BASE READER**********************************/
SpectrReader::SpectrReader(VSpectrItem *spectrItem)
{
    if(!spectrItem)
        return;
    PythonQt::init(PythonQt::IgnoreSiteModule | PythonQt::RedirectStdOut,"LogData");
    PythonQt_QtAll::init();
    PythonQt::self()->registerCPPClass("ICurve","","Curves",PythonQtCreateObject<WrapperIcurvePython>);
    m_mainContext = PythonQt::self()->getMainModule();
    setAcceptDrops(true);
    m_widht = 100;
    m_vMainLayout = new QVBoxLayout();
    m_splitterFiltersAndSpectrs = new QSplitter ();

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
    m_comboFilters = new QComboBox();
    m_mainContext.addObject("comboFilter",m_comboFilters);
    m_mainContext.evalFile("scripts/spectrReader/menu.py");
    PythonQtScriptingConsole *m_console  = new PythonQtScriptingConsole(NULL, m_mainContext);
    m_console->append("py> from LogData.Curves import*");
    m_console->show();
    m_btnAddFilter = new QPushButton("add");
    m_toolBar->addWidget(m_sliderWidth);
    m_toolBar->addWidget(m_comboFilters);
    m_toolBar->addWidget(m_btnAddFilter);

    m_filterListModel = new FilterListModel;
    m_vLayoutFilters = new QVBoxLayout();
    m_filterListView = new FilterListView;
    m_filterListView->setModel(m_filterListModel);

    m_widgetFilters = new QWidget;
    m_hLayoutBtnFilters = new QHBoxLayout;
    m_btnApplyFilters = new QPushButton("Apply");
    m_btnRollBack = new QPushButton("Roll back");
    m_hLayoutBtnFilters->addWidget(m_btnApplyFilters);
    m_hLayoutBtnFilters->addWidget(m_btnRollBack);


    m_vLayoutFilters->addWidget(m_filterListView);
    m_vLayoutFilters->addLayout(m_hLayoutBtnFilters);
    m_widgetFilters->setLayout(m_vLayoutFilters);

    m_splitterFiltersAndSpectrs->addWidget(m_spectrSplitter);
    m_splitterFiltersAndSpectrs->addWidget(m_widgetFilters);

    m_vMainLayout->addWidget(m_toolBar);
    m_vMainLayout->addWidget(m_splitterFiltersAndSpectrs);
    setLayout(m_vMainLayout);

    connect(m_sliderWidth, &QSlider::valueChanged, this, &SpectrReader::sliderWidthChange);
    connect(m_btnAddFilter, &QPushButton::pressed, this, &SpectrReader::insertFilter);
    connect(m_btnApplyFilters, &QPushButton::pressed, this, &SpectrReader::applyFilters);
    connect(m_btnRollBack, &QPushButton::pressed, this, &SpectrReader::rollBackFilters);
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
    bool ok = false;
    AGraphicItem* f_item = reinterpret_cast<AGraphicItem*>(event->mimeData()->data("item").toLongLong(&ok));
    VSpectrItem *f_spectrItem = dynamic_cast<VSpectrItem *>(f_item);
    if(f_spectrItem){
        m_listSpectrViewer->push_back(new SpectrViewer(f_spectrItem,m_sliderWidth->value()));
        m_spectrSplitter->addWidget(m_listSpectrViewer->last());
    }
}

void SpectrReader::insertFilter(){
    m_filterListModel->insertFilter(QPair<QString,QString>(m_comboFilters->currentText(),m_comboFilters->currentData().toString()));
}

void SpectrReader::rollBackFilters(){
    if(!m_listSpectrViewer || m_listSpectrViewer->isEmpty())
        return;
    foreach(auto spectrViewer, *m_listSpectrViewer){
        if(!spectrViewer->isActive())
            continue;
        ICurve * f_originalCurve = spectrViewer->originalCurve();
        ICurve * f_experCurve = spectrViewer->experimentalCurve();
        if(!f_originalCurve || !f_experCurve)
            continue;
        for(uint i = 0;i < f_originalCurve->size();++i){
            f_experCurve->setData(f_originalCurve->data(i),i);
        }
        spectrViewer->experimentalSpectr()->updateParam();
    }
}

void SpectrReader::applyFilters(){
    if(!m_listSpectrViewer || m_listSpectrViewer->isEmpty())
        return;
    foreach(auto spectrViewer, *m_listSpectrViewer){
        if(!spectrViewer->isActive())
            continue;
        ICurve * f_experCurve = spectrViewer->experimentalCurve();
        ICurve * f_originalCurve = spectrViewer->originalCurve();
        if(!f_originalCurve || !f_experCurve)
            continue;
        for(int i = 0;i < f_originalCurve->size();++i){
            f_experCurve->setData(f_originalCurve->data(i),i);
        }

        m_mainContext.addObject("curve",f_experCurve);
        QVector<QPair<QString, QString> > * f_listFilters = m_filterListModel->filters();
        if(!f_listFilters)
            return;
        foreach(auto value,*f_listFilters){
            QString f_path = "scripts/spectrReader/" + value.second;
            if(QDir().exists(f_path)){
                m_mainContext.evalFile(f_path);
            }
        }
        spectrViewer->experimentalSpectr()->updateParam();
    }
}

void SpectrReader::apply(){
    if(!m_listSpectrViewer || m_listSpectrViewer->isEmpty())
        return;
    foreach(auto spectrViewer, *m_listSpectrViewer){
        if(!spectrViewer->isActive()){
            continue;
        }
        ICurve *f_originalCurve = spectrViewer->originalCurve();
        ICurve *f_experCurve = spectrViewer->experimentalCurve();
        if(!f_originalCurve || !f_experCurve){
            continue;
        }
        for(uint i = 0;i < f_experCurve->size();++i){
            f_originalCurve->setData(f_experCurve->data(i),i);
        }
        spectrViewer->originalSpectr()->updateParam();
    }
}



