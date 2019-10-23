#ifndef BASECURVECLASS_H
#define BASECURVECLASS_H

#include <QGraphicsItem>
#include "inc/models/modelgfm.h"
#include <cmath>


class BaseCurveClass : public QObject,public QGraphicsItem {
    Q_OBJECT
protected:
    ScaleFactor *m_scaleFactor;
public:
    BaseCurveClass(ScaleFactor *scaleFactor);

};

#endif // BASECURVECLASS_H
