#ifndef VERTICALBOARD_H
#define VERTICALBOARD_H
#include "agraphicboard.h"
#include "icurve.h"
#include "iboard.h"
#include "verticaltrack.h"
#include <QGraphicsScene>

class VerticalBoard : public AGraphicBoard
{
    Q_OBJECT
    IBoard *m_board;
    bool m_isDrawTime;
    int headerTopOffset;
    QGraphicsScene *m_canvas;

public:
    VerticalBoard(IBoard *boardInfo,QMap<QString,ICurve*> *curves);
    VerticalBoard(QMap<QString,ICurve*> *curves);
    VerticalBoard();
    ~VerticalBoard()override;

    void newTrack()override;
    bool addCurve(ICurve *curve,int indexTab);
    virtual void redraw()override{emit scrollChanged();}
private:
    void init();
    virtual void resizeEvent(QResizeEvent *event)override;
    virtual void insertNewTrack(int curentTrackNumber,InsertPossition position = InsertPossition::RIGHT)override;

public slots:
    void scrollChanged();

signals:
    void changingTheVisibilityZone(QRectF visibleArea);

};

#endif // VERTICALBOARD_H
