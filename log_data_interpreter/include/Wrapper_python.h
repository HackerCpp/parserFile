#ifndef WRAPPER_H
#define WRAPPER_H


#include "interpreter_global.h"
#include "ainterpreterlogdata.h"
#include "PythonQt.h"
#include <QApplication>
#include<PythonQt_QtAll.h>
#include "gui/PythonQtScriptingConsole.h"

class INTERPRETER_EXPORT WrapperIcurvePython :public QObject{
Q_OBJECT
public Q_SLOTS:
     ICurve* new_ICurve(){return new ICurve();}
     qreal data(ICurve* o, uint& index){return o->data(index);}
     uint setData(ICurve* o,qreal& data){return o->setData(data);}
     uint setData(ICurve* o, qreal& data,uint& index){return o->setData(data,index);}
     uint setData(ICurve* o, const char *dataPrt, uint& numberOfVectors){return o->setData(*dataPrt,numberOfVectors);}
     ICurve *time(ICurve* o){return o->time();}
     ICurve *depth(ICurve* o){return o->depth();}
     ICurve *userBaseValue(ICurve* o){return o->userBaseValue();}
     bool setTime(ICurve* o, const ICurve &time){return o->setTime(time);}
     bool setDepth(ICurve* o, const ICurve &depth){return o->setDepth(depth);}
     bool setUserBaseValue(ICurve* o, const ICurve &userBaseValue){return  o->setUserBaseValue(userBaseValue);}
     qreal maximum(ICurve* o){return o->maximum();}
     qreal minimum(ICurve* o) {return o->minimum();}

};



#endif // WRAPPER_H
