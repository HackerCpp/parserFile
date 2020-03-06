#include "iinterpreterlogdata.h"

IInterpreterLogData::IInterpreterLogData(){

}

IInterpreterLogData::~IInterpreterLogData(){

}

bool IInterpreterLogData::openConsole(){
    return false;
}

bool IInterpreterLogData::openScript(){
     return false;
}

bool IInterpreterLogData::setCurves(QMap<QString,ICurve*> *curves){
    return false;
}
