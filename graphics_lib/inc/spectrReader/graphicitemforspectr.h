#ifndef GRAPHICITEMFORSPECTR_H
#define GRAPHICITEMFORSPECTR_H
#include "vspectritem.h"
#include "objectoftheboard.h"

class GraphicItemForSpectr : public ObjectOfTheBoard{
    VSpectrItem * m_spectrItem;
    QImage *m_curentHeaderImage;
    QImage *m_curentOneWaveImage;

public:
    GraphicItemForSpectr(VSpectrItem *spectrItem,int width);
    ~GraphicItemForSpectr()override;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem*, QWidget*)override;
    virtual QRectF boundingRect()const override;
    void changeVisibilityZone(QRectF visibilityZone);
    void changeSize(int width);
    void changePositionOneWave(QPoint position);
    void toSetTheLocationOfTheImageAfterDrawing()override;
    void run()override;
};

#endif // GRAPHICITEMFORSPECTR_H
