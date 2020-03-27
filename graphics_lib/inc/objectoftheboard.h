#ifndef OBJECTOFTHEBOARD_H
#define OBJECTOFTHEBOARD_H
#include <QGraphicsItem>
#include <QDebug>
#include <QThread>

class ObjectOfTheBoard : public QThread,public QGraphicsItem
{
    Q_OBJECT
protected:
    static qreal m_pixelPerMm;
    QRect m_visibilitySquare;

    virtual QRectF boundingRect()const{return m_visibilitySquare;}
public:
    ObjectOfTheBoard();
    ~ObjectOfTheBoard(){}
public slots:
    void changingTheVisibilityZone(QRect newVisibilityZone);
};

#endif // OBJECTOFTHEBOARD_H
