#include "ainterpreterlogdata.h"

AinterpreterLogData::AinterpreterLogData(){

}

AinterpreterLogData::~AinterpreterLogData(){

}

bool AinterpreterLogData::openConsole(){
    return false;
}

bool AinterpreterLogData::openScript(){
    return false;
}

bool AinterpreterLogData::setCurves(QMap<QString,ICurve*> *curves){
    m_curves = curves;
    return true;
}
