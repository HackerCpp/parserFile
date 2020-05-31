#ifndef BOARDFORTRACK_H
#define BOARDFORTRACK_H
#include <qvariant.h>
#include <QImage>

enum InsertPossition{RIGHT,LEFT};
class BoardForTrack{

protected:
    qreal m_pixelPerMm, m_scalePixelPerMm;
    uint m_pictureHeight,m_offsetUp;
    qreal m_top;
    qreal m_length;
    qreal m_scaleForDepth, m_scaleForTime;
    bool m_isDrawTime;
    int m_positionHeader;
    QImage::Format m_formatImg;

public:

    BoardForTrack();
    ~BoardForTrack(){}

    void setScaleForTime(qreal scale){m_scaleForTime = scale * (m_pixelPerMm * m_scalePixelPerMm);}
    void setScaleForDepth(qreal scale){m_scaleForDepth = scale * (m_pixelPerMm * m_scalePixelPerMm);}
    virtual void setPictureHeightMM(int heightMM);
    void setPositionHeader(int newPos){m_positionHeader = newPos;}
    virtual void setFormatPicture(QImage::Format format){m_formatImg = format;}
    virtual void setScalePixelPerMm(qreal scalePixelPerMm){m_scalePixelPerMm = scalePixelPerMm;}

    void setFormatDepth(){}

    virtual void setDrawTime(){m_isDrawTime = true;}
    virtual void setDrawDepth(){m_isDrawTime = false;}

    qreal pixelPerMm(){return (m_pixelPerMm * m_scalePixelPerMm);}
    uint pictureHeight(){return m_pictureHeight;}
    uint offsetUp(){return m_offsetUp;}
    int top(){return m_top;}
    uint length(){return m_length;}
    bool isDrawTime(){return m_isDrawTime;}
    int positionHeader(){return m_positionHeader;}
    QImage::Format formatPicture(){return m_formatImg;}
    qreal scale();
    virtual void resize(){}
    virtual void insertNewTrack(int curentTrackNumber,InsertPossition position = InsertPossition::RIGHT)
        {Q_UNUSED(curentTrackNumber) Q_UNUSED(position)}
    virtual void openCurveSettings(){}
};

#endif // BOARDFORTRACK_H
