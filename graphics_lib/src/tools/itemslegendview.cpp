#include "itemslegendview.h"
#include <QPainter>
#include <QHeaderView>
#include <QScrollBar>

void ItemsLegendView::init(){
    setAttribute(Qt::WA_TranslucentBackground);
    verticalHeader()->setAttribute(Qt::WA_TranslucentBackground);
    horizontalHeader()->setAttribute(Qt::WA_TranslucentBackground);
    setWindowFlags(Qt::Window | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);

    //horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    horizontalHeader()->setSectionResizeMode( QHeaderView::ResizeToContents );
    //verticalHeader()->setSectionResizeMode( QHeaderView::ResizeToContents );
    resizeColumnsToContents();
    //resizeRowsToContents();
    //m_image = QImage(this->width(),height(),QImage::Format_ARGB4444_Premultiplied);
    m_modelItems = new ModelLegendItems(m_items);
    setModel(m_modelItems);

    setShowGrid(true);
    setFrameShape(NoFrame);
    setMinimumWidth(1000);
    setMinimumHeight(1000);

}


ItemsLegendView::ItemsLegendView(QList<AGraphicItem*> *items,QWidget *parent)
    : QTableView(parent),m_items(items)
{
    init();

}

ItemsLegendView::ItemsLegendView(QMap<QString,AGraphicItem *> *items,QWidget *parent)
: QTableView(parent){
    m_items = new QList<AGraphicItem*>;
    foreach(auto item, *items){
        m_items->push_back(item);
    }
    init();
}

void ItemsLegendView::changeScenePoint(QPointF point){
    /*m_image.fill(0x0);
    QPainter f_painter(&m_image);
    int position = 0;
    bool isEndRedraw = false;

    foreach(auto item,*m_items){
        if(item->is_visible())
            item->drawLegend(&f_painter,position,m_startingPosition,point,&isEndRedraw);
    }
    repaint();*/

    m_modelItems->setCurrentPoint(point);
}

void ItemsLegendView::setStartingScenePoint(QPointF point){
    m_startingPosition = point;
    m_modelItems->setBeginPoint(point);
    m_modelItems->updateVisibleItems();
}


/*void ItemsLegendView::paintEvent(QPaintEvent *event){
    QPainter f_painter(this);
    f_painter.drawImage(rect(),m_image,m_image.rect());
}*/
