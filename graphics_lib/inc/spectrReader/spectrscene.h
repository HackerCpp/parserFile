#ifndef SPECTRSCENE_H
#define SPECTRSCENE_H
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsScene>



/************************SpectrScene************************************************************/
class SpectrScene : public QGraphicsScene{
public:
    SpectrScene(){}
    ~SpectrScene()override{}

    void mousePressEvent(QGraphicsSceneMouseEvent *event)override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event)override;

};

#endif // SPECTRSCENE_H
