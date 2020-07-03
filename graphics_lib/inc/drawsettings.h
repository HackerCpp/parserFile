#ifndef DRAWSETTINGS_H
#define DRAWSETTINGS_H
#include <QObject>
#include <QImage>
#include <QSettings>
#include <QApplication>

class DrawSettings : public QObject
{
    Q_OBJECT
    qreal m_pixelPerMm, m_scalePixelPerMm;
    uint m_pictureHeight,m_offsetUp;
    qreal m_scaleForDepth, m_scaleForTime;
    bool m_isDrawTime;
    QImage::Format m_formatImg;

    QSettings *m_settings;

    QVector<int> m_dividersTime;
    QVector<int> m_dividersDepth;
    QVector<int> m_lengthPicture;
public:
    enum FormatTime{MSEC_SM_100, SEC_SM_1, SEC_SM_5, SEC_SM_10,
                   SEC_SM_30, MIN_SM_1, MIN_SM_5,
                    MIN_SM_10, MIN_SM_30};
    enum FormatDepth{F1_10, F1_50, F1_100, F1_200,
                   F1_500, F1_1000, F1_2000,
                    F1_5000, F1_10000};
    enum LengthPicture{MIN,AVERAGE,MAX};

    DrawSettings();
    virtual ~DrawSettings();

    DrawSettings::FormatTime curentFormatTime();
    DrawSettings::FormatDepth curentFormatDepth();
    DrawSettings::LengthPicture curentPictureHeight();
    qreal curentScalePixelPerMm(){return m_scalePixelPerMm;}

    virtual void setDrawTime(){m_isDrawTime = true;}
    virtual void setDrawDepth(){m_isDrawTime = false;}
    void setScaleForTime(qreal scale){m_scaleForTime = scale;}
    void setScaleForDepth(qreal scale){m_scaleForDepth = scale;}
    virtual void setPictureHeightPix(uint heightPix){m_pictureHeight = heightPix; m_offsetUp = m_pictureHeight / 2;}

    qreal pixelPerMm(){return (m_pixelPerMm * m_scalePixelPerMm);}
    uint pictureHeight(){return m_pictureHeight;}
    uint offsetUp(){return m_offsetUp;}
    bool isDrawTime(){return m_isDrawTime;}
    QImage::Format formatPicture(){return m_formatImg;}
    qreal scale(){return (m_isDrawTime ? m_scaleForTime : m_scaleForDepth) * pixelPerMm();}
public slots:
    virtual void setFormatTime(FormatTime format);
    virtual void setFormatDepth(FormatDepth format);
    virtual void setLengthPicture(LengthPicture format);
    virtual void setFormatPicture(QImage::Format format);//{m_formatImg = format;}
    virtual void setScalePixelPerMm(qreal scalePixelPerMm);//{m_scalePixelPerMm = scalePixelPerMm;}
    virtual void setDrawType(int drawType);


};

#endif // DRAWSETTINGS_H
