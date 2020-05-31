#ifndef AGRAPHICBOARD_H
#define AGRAPHICBOARD_H
#include <QGraphicsView>
#include "agraphictrack.h"
#include "boardfortrack.h"
#include <QMap>
#include "iboard.h"

class AGraphicBoard : public QGraphicsView,public BoardForTrack
{
    Q_OBJECT

    int m_dividersTime[9] = {10,1000,5000,10000,30000,60000,300000,600000,1800000};
    int m_dividersDepth[9] = {10,50,100,200,500,1000,2000,5000,10000};
    int m_lengtgPicture[3] = {3000,16200,32500};
    int m_minimumSize;
protected:
    QMap<QString,AGraphicItem *> *m_items;
    QMap<QString,ICurve*> *m_curves;
    IBoard *m_boardInfo;

public:
    enum FormatTime{MSEC_SM_100, SEC_SM_1, SEC_SM_5, SEC_SM_10,
                   SEC_SM_30, MIN_SM_1, MIN_SM_5,
                    MIN_SM_10, MIN_SM_30};
    enum FormatDepth{F1_10, F1_50, F1_100, F1_200,
                   F1_500, F1_1000, F1_2000,
                    F1_5000, F1_10000};
    enum LengthPicture{MIN,AWERAGE,MAX};

    AGraphicBoard(IBoard *boardInfo,QMap<QString,ICurve*> *curves);
    ~AGraphicBoard()override;

    virtual void insertNewTrack(int curentTrackNumber,InsertPossition position = InsertPossition::RIGHT)override
        {Q_UNUSED(curentTrackNumber) Q_UNUSED(position)}
    virtual void newTrack(){}

    virtual void resize()override;
    virtual void resizePicture();
    virtual void redraw(){}
    virtual void setDrawTime()override{m_isDrawTime = true;redraw();resize();}
    virtual void setDrawDepth()override{m_isDrawTime = false;redraw(); resize();}
    virtual void setFormatTime(FormatTime format);
    virtual void setFormatDepth(FormatDepth format);
    virtual void setLengthPicture(LengthPicture format);
    virtual void setFormatPicture(QImage::Format format)override;
    void setScalePixelPerMm(qreal scalePixelPerMm)override;
    virtual void activate(bool activate);
    virtual void distributionOfItemsBetweenTracks(){}
    void updateItemsParam();
    void openCurveSettings()override;

private:
    virtual void mousePressEvent(QMouseEvent *event)override;
    virtual void mouseMoveEvent(QMouseEvent *event)override;
    virtual void mouseReleaseEvent(QMouseEvent *event)override;

public slots:
    void curveUpdate();
};

#endif // AGRAPHICBOARD_H
