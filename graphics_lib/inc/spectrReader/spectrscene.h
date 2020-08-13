#ifndef SPECTRSCENE_H
#define SPECTRSCENE_H
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsScene>
#include "selectingarea.h"



/************************SpectrScene************************************************************/
class SpectrScene : public QGraphicsScene{
    QGraphicsLineItem *m_lineItem;
    QGraphicsTextItem *m_textItem;
    SelectingArea *m_selectingArea;
    bool m_isLeftMouseClick,m_isRightMouseClick;
public:
    SpectrScene();
    ~SpectrScene()override{}

    void mousePressEvent(QGraphicsSceneMouseEvent *event)override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event)override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event)override;

};

#endif // SPECTRSCENE_H
