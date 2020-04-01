#ifndef AGRAPHICBOARD_H
#define AGRAPHICBOARD_H
#include <QGraphicsView>
#include "agraphictrack.h"
#include "boardfortrack.h"

class AGraphicBoard : public QGraphicsView,public BoardForTrack
{
    Q_OBJECT
    int m_minimumSize;
protected:

public:
    AGraphicBoard();
    ~AGraphicBoard()override{}

    virtual void newTrack(){}
private:
    virtual void mousePressEvent(QMouseEvent *event)override;
    virtual void mouseMoveEvent(QMouseEvent *event)override;
    virtual void mouseReleaseEvent(QMouseEvent *event)override;
};

#endif // AGRAPHICBOARD_H
