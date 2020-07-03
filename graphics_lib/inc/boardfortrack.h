#ifndef BOARDFORTRACK_H
#define BOARDFORTRACK_H
#include <qvariant.h>
#include <QImage>
#include "drawsettings.h"

enum InsertPossition{RIGHT,LEFT};
class BoardForTrack{

protected:
    //qreal m_pixelPerMm, m_scalePixelPerMm;
    //uint m_pictureHeight,m_offsetUp;
    qreal m_top;
    qreal m_length;
    //qreal m_scaleForDepth, m_scaleForTime;
    //bool m_isDrawTime;
    int m_positionHeader;
    //QImage::Format m_formatImg;
    DrawSettings *m_drawSettings;

public:

    BoardForTrack(DrawSettings *drawSettings);
    virtual ~BoardForTrack(){}

    void setPositionHeader(int newPos){m_positionHeader = newPos;}
    virtual void customUpdate(){}

    qreal pixelPerMm(){return m_drawSettings->pixelPerMm();}
    uint pictureHeight(){return m_drawSettings->pictureHeight();}
    uint offsetUp(){return m_drawSettings->offsetUp();}
    bool isDrawTime(){return m_drawSettings->isDrawTime();}
    QImage::Format formatPicture(){return m_drawSettings->formatPicture();}
    qreal scale(){return m_drawSettings->scale();}

    int top(){return m_top;}
    uint length(){return m_length;}
    int positionHeader(){return m_positionHeader;}
    virtual void resize(){}
    virtual void insertNewTrack(int curentTrackNumber,InsertPossition position = InsertPossition::RIGHT)
        {Q_UNUSED(curentTrackNumber) Q_UNUSED(position)}
    virtual void openCurveSettings(){}

};

#endif // BOARDFORTRACK_H
