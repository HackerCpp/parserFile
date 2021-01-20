#ifndef AGRAPHICBOARD_H
#define AGRAPHICBOARD_H
#include <QGraphicsView>
#include "agraphictrack.h"
#include "boardfortrack.h"
#include <QMap>
#include "iboard.h"
#include "basestandartwidget.h"

class LabelBlock;

class AGraphicBoard : public QGraphicsView,public BoardForTrack
{
    Q_OBJECT

    int m_minimumSize;
protected:
    QMap<QString,AGraphicItem *> *m_items;
    QMap<QString,ICurve*> *m_curves;
    IBoard *m_boardInfo;

    QVector<BaseStandartWidget *> *m_standartWidgets;
    bool m_isStandartWidget;

public:


    AGraphicBoard(IBoard *boardInfo,QMap<QString,ICurve*> *curves,DrawSettings *drawSettings);
    virtual ~AGraphicBoard()override;

    virtual void insertNewTrack(int curentTrackNumber,InsertPossition position = InsertPossition::RIGHT)override
        {Q_UNUSED(curentTrackNumber) Q_UNUSED(position)}
    virtual void newTrack(){}
    void customUpdate()override{redraw();}

    QString name()override{return m_boardInfo->name();}
    virtual void resize()override;
    virtual void resizePicture();
    virtual void redraw(){}
    virtual void activate(bool activate);
    virtual void distributionOfItemsBetweenTracks(){}
    void updateItemsParam();
    void openCurveSettings()override;
    IBoard *boardInfo(){return m_boardInfo;}

protected:
    virtual void mousePressEvent(QMouseEvent *event)override;
    virtual void mouseMoveEvent(QMouseEvent *event)override;
    virtual void mouseReleaseEvent(QMouseEvent *event)override;

public slots:
    void curveUpdate();
};

#endif // AGRAPHICBOARD_H
