#ifndef MAINVALUESCONTAINER_H
#define MAINVALUESCONTAINER_H
#include "mainvalue.h"

class MainValuesContainer{
    QList<MainValue*> *m_mainValues;
public:
    MainValuesContainer();
    MainValue *addMainValue(Curve *mainTime,Curve *mainDepth);
    void setMainTime();
    void setMainDepth();
    void setScale(qreal scale);
    qreal maximum();
    qreal minimum();
    qreal scale();
    ~MainValuesContainer();
};

#endif // MAINVALUESCONTAINER_H
