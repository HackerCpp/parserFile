#include "icurve.h"

ICurve::ICurve(){

}

ICurve::~ICurve(){

}

qreal ICurve::data(uint index){
    return 0;
}

uint ICurve::setData(qreal data){
    return 0;
}

uint ICurve::setData(qreal data,uint index){
    qDebug() << "setData interf curve";
    return 0;
}

uint ICurve::setData(const char *dataPtr,uint numberOfVectors){
    qDebug() << "setData interf curve";
    return 0;
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
    return false;
}

bool ICurve::setDepth(ICurve *depth){
    return false;
}

bool ICurve::setUserBaseValue(ICurve *userBaseValue){
    return false;
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




