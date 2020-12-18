#ifndef DRAWINGTHROUGHADISK_H
#define DRAWINGTHROUGHADISK_H
#include <QThread>


class DrawingThroughADisk : public QThread
{
    Q_OBJECT

protected:
    QString m_uid;
    bool m_isEndThread,m_isRedraw;
    qreal m_curentPictureWidth;
    bool m_updatedParam;
    QStringList m_picturePath;
    const uint16_t M_HEIGHT_PICTURE = 16000;
    uint16_t m_lengthOverlay;
    qreal m_curentDrawPersent;
    volatile bool m_saversMoment;


public:
    DrawingThroughADisk();
    virtual ~DrawingThroughADisk()override{}

    virtual void loadDrawingParam(int width){Q_UNUSED(width)}
    virtual void drawOnTheDisk(){}
signals:
    void dataHardDiscReady();
public slots:
    virtual void endThreadHandler();
};

#endif // DRAWINGTHROUGHADISK_H
