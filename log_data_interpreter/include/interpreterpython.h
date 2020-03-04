#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "interpreter_global.h"
#include "ainterpreterlogdata.h"
#include "PythonQt.h"

class INTERPRETER_EXPORT InterpreterPython : public AinterpreterLogData{
public:
    InterpreterPython();
    ~InterpreterPython()override;

    bool openConsole()override;
    bool openScript()override;
};

#endif // INTERPRETER_H
