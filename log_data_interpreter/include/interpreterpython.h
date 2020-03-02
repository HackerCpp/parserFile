#ifndef INTERPRETERPYTHON_H
#define INTERPRETERPYTHON_H

#include "ainterpreterlogdata.h"

class InterpreterPython : public AinterpreterLogData{
public:
    InterpreterPython();
    ~InterpreterPython()override;

   bool openConsole()override;
   bool openScript()override;

};

#endif // INTERPRETERPYTHON_H
