#ifndef OBJECTOFTHEBOARD_H
#define OBJECTOFTHEBOARD_H
#include <QGraphicsItem>
#include <QDebug>
#include <QThread>

class ObjectOfTheBoard : public QThread,public QGraphicsItem
{
    Q_OBJECT
protected:

    QRect m_visibilitySquare;
    bool m_needToRedraw;
    QImage *m_curentPixmap,*m_doublePixMap;

    virtual QRectF boundingRect()const{return m_visibilitySquare;}
    void redraw();
public:
    ObjectOfTheBoard();
    ~ObjectOfTheBoard(){}
public slots:
    void changingTheVisibilityZone(QRect newVisibilityZone);
};

#endif // OBJECTOFTHEBOARD_H
