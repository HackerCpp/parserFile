#include "interpretercreater.h"
#ifndef MINI_VERSION
#include "interpreterpython.h"
#endif


IInterpreterLogData *InterpreterCreater::create(InterpreterType type){
#ifndef MINI_VERSION
    switch (type) {
        case PYTHON:
            return new InterpreterPython();
    }
#endif
    return nullptr;
}

bool InterpreterCreater::move(IInterpreterLogData *interpreter,InterpreterType type){
#ifndef MINI_VERSION
    if(interpreter){
        delete interpreter;
    }
    switch (type) {
        case PYTHON:
            interpreter = new InterpreterPython();
            return true;
    }
#endif
    return true;
}
