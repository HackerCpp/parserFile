#ifndef VERTICALBOARD_H
#define VERTICALBOARD_H
#include "agraphicboard.h"
#include "icurve.h"
#include "iboard.h"
#include "verticaltrack.h"
#include <QGraphicsScene>

class VerticalBoard : public AGraphicBoard
{
    IBoard *m_board;
    bool m_isDrawTime;
    int headerTopOffset;
    QGraphicsScene *m_canvas;

public:
    VerticalBoard(IBoard *board,QMap<QString,ICurve*> *curves);
    VerticalBoard(QMap<QString,ICurve*> *curves);
    VerticalBoard();
    ~VerticalBoard()override;

    void newTrack()override;
    bool addCurve(ICurve *curve,int indexTab);
private:
    void init();

    void mousePressEvent(QMouseEvent *event)override;
    void mouseMoveEvent(QMouseEvent *event)override;
    void mouseReleaseEvent(QMouseEvent *event)override;
};

#endif // VERTICALBOARD_H
