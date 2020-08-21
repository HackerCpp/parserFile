#ifndef LINKING_H
#define LINKING_H

#include <QObject>
#include "icurve.h"

class Linking : public QObject
{
    Q_OBJECT
public:
    explicit Linking(QObject *parent = nullptr);

    ICurve *createTime(uint timeBegin_min,uint timeEnd_min,qreal step_sec);
    ICurve *createDepth(int depthBegin_m,int depthEnd_m,qreal step_m);
    ICurve *linkTime(ICurve *mainTime,ICurve *curve);
    ICurve *linkDepth(ICurve *mainDepth,ICurve *curve);

signals:

};

#endif // LINKING_H
