#include "itemslegendview.h"

ItemsLegendView::ItemsLegendView(QList<AGraphicItem*> *items,QWidget *parent)
    : QWidget(parent),m_items(items)
{
    setWindowFlag(Qt::ToolTip);

}

void ItemsLegendView::changeScenePoint(QPointF point){

}


void ItemsLegendView::paintEvent(QPaintEvent *event){

}
