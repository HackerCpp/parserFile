#ifndef VERTICALBOARD_H
#define VERTICALBOARD_H
#include "agraphicboard.h"
#include "icurve.h"
#include "iboard.h"
#include "verticaltrack.h"
#include <QGraphicsScene>
#include "itemslegendview.h"
#include "canvas.h"

class VerticalBoard : public AGraphicBoard
{
    Q_OBJECT

    bool m_isDrawTime;
    int headerTopOffset;
    Canvas *m_canvas;
    ItemsLegendView *m_legend;
    bool m_isShowLegend;
    QGraphicsLineItem *m_beginLineLegend, *m_currentLineLegend;
    QTimer m_timerLeftClick;
    QPoint m_posLeftClick;
public:
    VerticalBoard(IBoard *boardInfo,QMap<QString,ICurve*> *curves,DrawSettings *drawSettings);
    VerticalBoard(QMap<QString,ICurve*> *curves,DrawSettings *drawSettings);
    VerticalBoard();
    virtual ~VerticalBoard()override;

    void newTrack()override;
    bool addCurve(ICurve *curve,int indexTab);
    virtual void redraw()override;
    void updateItems();


    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

private:
    void init();
    virtual void resizeEvent(QResizeEvent *event)override;
    virtual void insertNewTrack(int curentTrackNumber,InsertPossition position = InsertPossition::RIGHT)override;
    virtual  void distributionOfItemsBetweenTracks()override;
public slots:
    void scrollChanged();
    void timerLeftClick();

signals:
    void changingTheVisibilityZone(QRectF visibleArea);
    void needToRedraw();

};

#endif // VERTICALBOARD_H
