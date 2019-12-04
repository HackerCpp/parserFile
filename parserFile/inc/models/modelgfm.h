#ifndef MODELGFM_H
#define MODELGFM_H

#include <QGraphicsScene>
#include <inc/parsers/parsergfm.h>
#include <QObject>

struct ScaleFactor{
    int m_mainValueMax;
    int m_mainValueMin;
    int m_width;
    int m_indexBegin;
    int m_indexEnd;
    int m_scaleY;
};
class ModelGFM : public QGraphicsScene{
    Q_OBJECT

    ScaleFactor scaleFactor;
    QVector<qreal>* m_mainValue;
    QList<DataBlockCurve> *m_curves;
public:
    ModelGFM(DataBlockCurve *mainValue,QList<DataBlockCurve> *curves);
    void connectView();
protected:
    virtual void keyPressEvent(QKeyEvent *event);
    void scrollChange(qreal leftX,qreal topY,qreal rightX,qreal downY);

};

#endif // MODELGFM_H
