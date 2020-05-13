#ifndef OBJECTOFTHEBOARD_H
#define OBJECTOFTHEBOARD_H
#include <QGraphicsItem>
#include <QDebug>
#include <QThread>
#include <QDragEnterEvent>

class ObjectOfTheBoard : public QThread,public QGraphicsItem
{
    Q_OBJECT
protected:

    QRectF m_visibilitySquare;
    bool m_endRedraw,m_needToRedraw;
    QImage *m_curentPixmap,*m_doublePixMap;

    virtual QRectF boundingRect()const override{return m_visibilitySquare;}
    void redraw();
    virtual void sceneUpdate();


public:
    ObjectOfTheBoard();
    virtual ~ObjectOfTheBoard();
    virtual void resize(){}
    virtual void resizePictures(){}
    virtual void swapPixMap();
public slots:
    void changingTheVisibilityZone(QRectF newVisibilityZone);
};

#endif // OBJECTOFTHEBOARD_H
