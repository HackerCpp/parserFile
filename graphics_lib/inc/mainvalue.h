#ifndef MAINVALUE_H
#define MAINVALUE_H
#include "curve.h"

class MainValue{
    Curve *m_mainTime;
    Curve *m_mainDepth;
    Curve *m_mainValue;
    qreal m_scaleForTime, m_scaleForDepth,m_curentScale;
    bool m_isMainTime;

public:
    MainValue(Curve *mainTime,Curve *mainDepth);
    Curve *getTime(){return m_mainTime;}
    Curve *getDepth(){return m_mainDepth;}
    qreal maximumTime();
    qreal minimumTime();
    qreal maximumDepth();
    qreal minimumDepth();
    qreal maximumTimeForScale();
    qreal minimumTimeForScale();
    qreal maximumDepthForScale();
    qreal minimumDepthForScale();
    qreal minimumForScale();
    qreal maximumForScale();
    Curve *mainValue(){return m_mainValue;}
    void setMainTime();
    void setMainDepth();
    bool isMainTime();
    void setScale(qreal scale);
    uint size();
    qreal scale();
    bool checkPoint(Curve *time,Curve *depth);
    qreal operator[](int index);
    qreal data(int index);
};

#endif // MAINVALUE_H
