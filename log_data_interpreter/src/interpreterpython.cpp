#include "interpreterpython.h"

InterpreterPython::InterpreterPython()
{

}

InterpreterPython::~InterpreterPython(){

}

bool InterpreterPython::openConsole(){
    qDebug() << "Console interpreter python";
    return true;
}

bool InterpreterPython::openScript(){
    return true;
}
