#ifndef SPECTRVIEWER_H
#define SPECTRVIEWER_H
#include <QGraphicsView>
#include "vspectritem.h"
#include <QRadioButton>
#include "spectrscene.h"


class SpectrViewer : public QGraphicsView{
    Q_OBJECT
    SpectrScene *m_scene;
    VSpectrItem *m_originalSpectr,*m_experimentalSpectr;
    QRadioButton *m_radioBtnIsActive;

public:
    SpectrViewer(VSpectrItem *spectrItem,int width);
    ~SpectrViewer()override;

    void changeWidth(int newWidth);
    void changeVisibilityZone(QRectF newVisibilityZone);

    ICurve *originalCurve(){return m_originalSpectr->curve();}
    ICurve *experimentalCurve(){return m_experimentalSpectr->curve();}
    bool isActive(){if(m_radioBtnIsActive){return m_radioBtnIsActive->isChecked();}return false;}
    void resizeEvent(QResizeEvent *event)override;
    VSpectrItem *originalSpectr(){return m_originalSpectr;}
    VSpectrItem *experimentalSpectr(){return m_experimentalSpectr;}
    void changePositionOneWave(QPoint position);

signals:
    void sig_changePositionOneWave(QPoint position);
public slots:
    void scrollChanged();
};

#endif // SPECTRVIEWER_H
