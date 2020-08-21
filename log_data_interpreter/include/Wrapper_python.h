#ifndef WRAPPER_H
#define WRAPPER_H

#include "interpreter_global.h"
#include "ainterpreterlogdata.h"
#include "PythonQt.h"
#include <QApplication>
#include<PythonQt_QtAll.h>
#include "gui/PythonQtScriptingConsole.h"
#include <QMap>


class INTERPRETER_EXPORT WrapperIcurvePython :public QObject{
Q_OBJECT
public Q_SLOTS:
     ICurve* new_ICurve(){return new ICurve();}
     qreal data(ICurve* o, uint& index){return o->data(index);}
     void setData(ICurve* o,qreal& data){o->setData(data);}
     void setData(ICurve* o, qreal& data,uint& index){o->setData(data,index);}
     void setData(ICurve* o, const char *dataPrt, uint& numberOfVectors){o->setData(*dataPrt,numberOfVectors);}
     ICurve *time(ICurve* o){return o->time();}
     ICurve *depth(ICurve* o){return o->depth();}
     ICurve *userBaseValue(ICurve* o){return o->userBaseValue();}
     bool setTime(ICurve* o,  ICurve *time){return o->setTime(time);}
     bool setDepth(ICurve* o, ICurve *depth){return o->setDepth(depth);}
     bool setUserBaseValue(ICurve* o,ICurve *userBaseValue){return  o->setUserBaseValue(userBaseValue);}
     qreal maximum(ICurve* o){return o->maximum();}
     qreal minimum(ICurve* o) {return o->minimum();}
     uint size(ICurve* o) {return o->size();}
     uint sizeOffset(ICurve* o) {return o->sizeOffset();}
     Desc *desc(ICurve* o){return o->desc();}
     QString mnemonic(ICurve* o){return o->mnemonic();}
};



#endif // WRAPPER_H
