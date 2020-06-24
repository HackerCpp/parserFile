#include "icurve.h"
#include "curve.h"

ICurve::ICurve(){

}

ICurve::~ICurve(){

}

qreal ICurve::data(uint index){
    Q_UNUSED(index)
    return 0;
}
QByteArray ICurve::data(){
    return QByteArray();
}

void ICurve::setData(qreal data){
    Q_UNUSED(data)
}

void ICurve::setData(qreal data,uint index){
    Q_UNUSED(data)
    Q_UNUSED(index)
}

void ICurve::setData(const char *dataPtr,uint numberOfVectors){
    Q_UNUSED(dataPtr)
    Q_UNUSED(numberOfVectors)
}

ICurve *ICurve::time(){
    return nullptr;
}

ICurve *ICurve::depth(){
    return nullptr;
}

ICurve *ICurve::userBaseValue(){
    return nullptr;
}

bool ICurve::setTime(ICurve *time){
    Q_UNUSED(time)
    return false;
}

bool ICurve::setDepth(ICurve *depth){
    Q_UNUSED(depth)
    return false;
}

bool ICurve::setUserBaseValue(ICurve *userBaseValue){
    Q_UNUSED(userBaseValue)
    return false;
}

uint ICurve::size(){
    return 0;
}
qreal ICurve::maximum(){
    return 0;
}

qreal ICurve::minimum(){
    return 0;
}

Desc *ICurve::desc(){
   return nullptr;
}

ShortCut ICurve::shortCut(){
    return ShortCut();
}

QString ICurve::mnemonic(){
    return nullptr;
}

ICurve * ICurve::curveCreater(const ICurve &curve){
    ICurve *f_curve = nullptr;
    if(dynamic_cast<const Curve<uint8_t>*>(&curve)){
        f_curve = new Curve<uint8_t>(dynamic_cast<const Curve<uint8_t>&>(curve));
    }
    else if(dynamic_cast<const Curve<int8_t>*>(&curve)){
        f_curve = new Curve<int8_t>(dynamic_cast<const Curve<int8_t>&>(curve));
    }
    else if(dynamic_cast<const Curve<uint32_t>*>(&curve)){
        f_curve = new Curve<uint32_t>(dynamic_cast<const Curve<uint32_t>&>(curve));
    }
    else if(dynamic_cast<const Curve<int32_t>*>(&curve)){
        f_curve = new Curve<int32_t>(dynamic_cast<const Curve<int32_t>&>(curve));
    }
    else if(dynamic_cast<const Curve<uint16_t>*>(&curve)){
        f_curve = new Curve<uint16_t>(dynamic_cast<const Curve<uint16_t>&>(curve));
    }
    else if(dynamic_cast<const Curve<int16_t>*>(&curve)){
        f_curve = new Curve<int16_t>(dynamic_cast<const Curve<int16_t>&>(curve));
    }
    else if(dynamic_cast<const Curve<float_t>*>(&curve)){
        f_curve = new Curve<float_t>(dynamic_cast<const Curve<float_t>&>(curve));
    }
    else if(dynamic_cast<const Curve<double>*>(&curve)){
        f_curve = new Curve<double>(dynamic_cast<const Curve<double>&>(curve));
    }
    else if(dynamic_cast<const Curve<uint64_t>*>(&curve)){
        f_curve = new Curve<uint64_t>(dynamic_cast<const Curve<uint64_t>&>(curve));
    }
    else if(dynamic_cast<const Curve<int64_t>*>(&curve)){
        f_curve = new Curve<int64_t>(dynamic_cast<const Curve<int64_t>&>(curve));
    }

    return f_curve;
}




