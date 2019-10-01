#ifndef BASECURVECLASS_H
#define BASECURVECLASS_H

#include <QGraphicsItem>


class BaseCurveClass : public QObject,public QGraphicsItem {
    Q_OBJECT
protected:
    int m_del;
    qreal m_step;
    int m_indexBegin;
    int m_indexEnd;
public:
    BaseCurveClass();
public slots:
    void scrollChange(qreal leftX,qreal topY,qreal rightX,qreal downY);
};

#endif // BASECURVECLASS_H
