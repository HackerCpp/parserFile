#include "graphicitemforspectr.h"



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

    m_curentHeaderImage = new QImage(100,40,m_spectrItem->board()->formatPicture());
    m_curentHeaderImage->fill(0x0);
    QPainter f_painterHeader(m_curentHeaderImage);
    int position = 0;
    m_spectrItem->drawHeader(&f_painterHeader,position,&flag);
    QPainter f_painter(m_curentPixmap);
    m_curentPixmap->fill(0xffffffff);

    m_spectrItem->drawBody(&f_painter,QRectF(0,m_spectrItem->topValue(),m_curentPixmap->width(),1000),&flag);
    connect(m_spectrItem,&VSpectrItem::dataHardDiscReady,this,&GraphicItemForSpectr::redraw);
}

GraphicItemForSpectr::~GraphicItemForSpectr(){
    m_endRedraw = true;
    m_needToRedraw = false;
    wait();
    if(m_curentHeaderImage){delete m_curentHeaderImage;m_curentHeaderImage = nullptr;}
}

void GraphicItemForSpectr::paint(QPainter *painter, const QStyleOptionGraphicsItem*, QWidget*){
    if(m_curentPixmap)
        painter->drawImage(QRect(0,m_topPositionPicture,m_curentPixmap->width(),m_curentPixmap->height()),*m_curentPixmap);
    if(m_curentHeaderImage)
        painter->drawImage(QRect(m_visibilitySquare.x(),m_visibilitySquare.y(),m_curentHeaderImage->width(),m_curentHeaderImage->height()),*m_curentHeaderImage);
}

QRectF GraphicItemForSpectr::boundingRect()const {
    if(!m_curentPixmap)
        return QRectF();
    int f_upStock = 50;
    int f_height = m_spectrItem->bottomValue() - m_spectrItem->topValue() + f_upStock * 2;
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
    //bool flag = false;
    wait();
    m_spectrItem->updateParam(width - 50);

    if(m_curentPixmap){delete m_curentPixmap; m_curentPixmap = nullptr;}
    m_curentPixmap = new QImage(width - 50,m_spectrItem->board()->pictureHeight(),m_spectrItem->board()->formatPicture());

    if(m_doublePixMap){delete m_doublePixMap; m_doublePixMap = nullptr;}
    m_doublePixMap = new QImage(width - 50,m_spectrItem->board()->pictureHeight(),m_spectrItem->board()->formatPicture());
    m_curentPixmap->fill(0xffffffff);

    QGraphicsItem::prepareGeometryChange();
    QGraphicsItem::update();
}

void GraphicItemForSpectr::run(){
    QPainter f_painter(m_doublePixMap);
    m_doublePixMap->fill(0xffffffff);
    m_spectrItem->drawBody(&f_painter,m_visibilitySquare,&m_endRedraw);
    swapPixMap();
}
