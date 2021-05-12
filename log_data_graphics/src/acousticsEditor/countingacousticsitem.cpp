#include "countingacousticsitem.h"
#include "agraphicitem.h"
#include "vacuitem.h"

CountingAcousticsItem::CountingAcousticsItem(DataCountingAcoustics *dataAcoustics,int width)
    : m_dataAcoustics(dataAcoustics)
{
    bool flag = false;
    AGraphicItem *f_item = nullptr;
    if(m_dataAcoustics->acuItemOne())
        f_item = m_dataAcoustics->acuItemOne();
    else if(m_dataAcoustics->acuItemTwo())
        f_item = m_dataAcoustics->acuItemTwo();
    if(f_item){
        m_curentPixmap = new QImage(width,f_item->board()->pictureHeight(),f_item->board()->formatPicture());
        m_doublePixMap = new QImage(width,f_item->board()->pictureHeight(),f_item->board()->formatPicture());

        QPainter f_painter(m_curentPixmap);
        m_curentPixmap->fill(0xffffffff);
        f_item->updateParam(width);
        f_item->drawBody(&f_painter,QRectF(0,f_item->topValue(),m_curentPixmap->width(),1000),&flag);
        connect(static_cast<VAcuItem *>(f_item),&VAcuItem::dataHardDiscReady,this,&CountingAcousticsItem::redraw);
    }
}

void CountingAcousticsItem::paint(QPainter *painter, const QStyleOptionGraphicsItem*, QWidget*){
    if(m_curentPixmap)
        painter->drawImage(QRect(0,m_topPositionPicture,m_curentPixmap->width(),m_curentPixmap->height()),*m_curentPixmap);
}

QRectF CountingAcousticsItem::boundingRect()const {
    if(!m_curentPixmap)
        return QRectF();
    int f_upStock = 50;
    QVector<AGraphicItem *> f_items = m_dataAcoustics->items();
    int f_bottom = INT_MIN;
    int f_top = INT_MAX;
    foreach(auto item,f_items){
        if(!item)
            continue;
        f_top = item->topValue() < f_top ?   item->topValue() : f_top;
        f_bottom = item->bottomValue() > f_bottom ?   item->bottomValue() : f_bottom;
    }
    if(f_bottom == INT_MIN || f_top == INT_MAX){
        f_bottom = f_top = 0;

    }
    int f_height = f_bottom - f_top + f_upStock * 2;
    return QRectF(0,f_top - f_upStock,m_curentPixmap->width(),f_height);
}

void CountingAcousticsItem::changeVisibilityZone(QRectF visibilityZone){
    m_visibilitySquare = visibilityZone;
    redraw();
}

void CountingAcousticsItem::changeSize(int width){
    m_endRedraw = true;
    bool flag = false;
    QVector<AGraphicItem *> f_items = m_dataAcoustics->items();
    foreach(auto item,f_items){
        if(!item)
            continue;
        item->updateParam(width);
    }
    wait();
    AGraphicItem *f_item = nullptr;
    if(m_dataAcoustics->acuItemOne())
        f_item = m_dataAcoustics->acuItemOne();
    else if(m_dataAcoustics->acuItemTwo())
        f_item = m_dataAcoustics->acuItemTwo();
    if(f_item){
        if(m_curentPixmap){delete m_curentPixmap; m_curentPixmap = nullptr;}
        m_curentPixmap = new QImage(width - 50,f_item->board()->pictureHeight(),f_item->board()->formatPicture());

        if(m_doublePixMap){delete m_doublePixMap; m_doublePixMap = nullptr;}
        m_doublePixMap = new QImage(width - 50,f_item->board()->pictureHeight(),f_item->board()->formatPicture());
        m_curentPixmap->fill(0xffffffff);

        QGraphicsItem::prepareGeometryChange();
        QGraphicsItem::update();
    }
}

void CountingAcousticsItem::toSetTheLocationOfTheImageAfterDrawing(){
    AGraphicItem *f_item = nullptr;
    if(m_dataAcoustics->acuItemOne())
        f_item = m_dataAcoustics->acuItemOne();
    else if(m_dataAcoustics->acuItemTwo())
        f_item = m_dataAcoustics->acuItemTwo();
    if(f_item){
        m_topPositionPicture = static_cast<int>(m_visibilitySquare.y() - f_item->board()->offsetUp());
    }
}

void CountingAcousticsItem::run(){
    if(!m_doublePixMap)
        return;
    QPainter f_painter(m_doublePixMap);
    m_doublePixMap->fill(0xffffffff);
    QVector<AGraphicItem *> f_items = m_dataAcoustics->items();
    foreach(auto item,f_items){
        if(!item)
            continue;
        item->drawBody(&f_painter,m_visibilitySquare,&m_endRedraw);
    }
    swapPixMap();
}
