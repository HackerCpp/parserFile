#ifndef INTERPRETERCREATER_H
#define INTERPRETERCREATER_H
#include "interpreter_global.h"

class IInterpreterLogData;

class INTERPRETER_EXPORT InterpreterCreater{
    InterpreterCreater(){}
public:

    enum InterpreterType{PYTHON};
    static IInterpreterLogData *create(InterpreterType type = PYTHON);
    static bool move(IInterpreterLogData *interpreter,InterpreterType type = PYTHON);
};

#endif // INTERPRETERCREATER_H
