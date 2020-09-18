#ifndef GRAPHICHEADER_H
#define GRAPHICHEADER_H
#include <QGraphicsView>
#include "agraphicitem.h"
#include "iboard.h"


class GraphicHeader : public QGraphicsView
{
protected:
    QMap<QString,AGraphicItem *> *m_items;
    IBoard *m_boardInfo;
    QGraphicsScene *m_canvas;
public:
    GraphicHeader(IBoard *boardInfo);
    ~GraphicHeader(){}

    void addGraphicsItems(QMap<QString,AGraphicItem *> *items);
};

#endif // GRAPHICHEADER_H
