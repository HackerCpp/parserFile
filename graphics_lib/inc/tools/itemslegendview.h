#ifndef ITEMSLEGENDVIEW_H
#define ITEMSLEGENDVIEW_H

#include <QWidget>
#include "agraphicitem.h"

class ItemsLegendView : public QWidget
{
    Q_OBJECT

    QList<AGraphicItem*> *m_items;
    QImage m_image;

    void init();
public:
    explicit ItemsLegendView(QList<AGraphicItem*> *items,QWidget *parent = nullptr);
    explicit ItemsLegendView(QMap<QString,AGraphicItem *> *items,QWidget *parent = nullptr);

    void changeScenePoint(QPointF point);
    void paintEvent(QPaintEvent *event)override;
signals:

};

#endif // ITEMSLEGENDVIEW_H
