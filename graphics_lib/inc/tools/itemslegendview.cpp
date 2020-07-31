#include "itemslegendview.h"
#include <QPainter>

void ItemsLegendView::init(){
    setAttribute(Qt::WA_TranslucentBackground);
    setWindowFlags(Qt::Window | Qt::FramelessWindowHint | Qt::Tool | Qt::WindowStaysOnTopHint);
    setMinimumSize(400,2000);
    setMaximumWidth(400);
    m_image = QImage(this->width(),height(),QImage::Format_ARGB4444_Premultiplied);
}


ItemsLegendView::ItemsLegendView(QList<AGraphicItem*> *items,QWidget *parent)
    : QWidget(parent),m_items(items)
{
    init();

}

ItemsLegendView::ItemsLegendView(QMap<QString,AGraphicItem *> *items,QWidget *parent)
: QWidget(parent){
    m_items = new QList<AGraphicItem*>;
    foreach(auto item, *items){
        m_items->push_back(item);
    }
    init();
}

void ItemsLegendView::changeScenePoint(QPointF point){
    m_image.fill(0x0);
    QPainter f_painter(&m_image);
    int position = 0;
    bool isEndRedraw = false;

    foreach(auto item,*m_items){
        if(item->is_visible())
            item->drawLegend(&f_painter,position,point,&isEndRedraw);
    }
    repaint();
}


void ItemsLegendView::paintEvent(QPaintEvent *event){
    QPainter f_painter(this);
    f_painter.drawImage(rect(),m_image,m_image.rect());
}
