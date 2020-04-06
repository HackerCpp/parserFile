#ifndef BOARDFORTRACK_H
#define BOARDFORTRACK_H
#include <qvariant.h>


class BoardForTrack{
protected:
    qreal m_pixelPerMm;
    uint m_pictureHeight,m_offsetUp;
    int m_top;
    uint m_length;
    qreal m_scaleForDepth, m_scaleForTime;
    bool m_isDrawTime;

public:
    enum FormatTime{MSEC_SM_100 = 10,SEC_SM_1 = 1000,SEC_SM_5 = 5000,SEC_SM_10 = 10000,
                   SEC_SM_30 = 30000,MIN_SM_1 = 60000,MIN_SM_5 = 300000,
                    MIN_SM_10 = 600000,MIN_SM_30 = 1800000};
    BoardForTrack();
    ~BoardForTrack(){}

    void setScaleForTime(qreal scale){m_scaleForTime = scale * m_pixelPerMm;}
    void setScaleForDepth(qreal scale){m_scaleForDepth = scale * m_pixelPerMm;}
    void setFormatTime(FormatTime format){setScaleForTime(1.f/qreal(format));}
    void setFormatDepth(){}

    virtual void setDrawTime(){m_isDrawTime = true;}
    virtual void setDrawDepth(){m_isDrawTime = false;}

    qreal pixelPerMm(){return m_pixelPerMm;}
    uint pictureHeight(){return m_pictureHeight;}
    uint offsetUp(){return m_offsetUp;}
    int top(){return m_top;}
    uint length(){return m_length;}
    bool isDrawTime(){return m_isDrawTime;}
    qreal scale();
    virtual void resize(){}
};

#endif // BOARDFORTRACK_H
