#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "interpreter_global.h"
#include "ainterpreterlogdata.h"
#include "PythonQt.h"
#include <QApplication>
#include<PythonQt_QtAll.h>
#include "gui/PythonQtScriptingConsole.h"

class INTERPRETER_EXPORT InterpreterPython : public AinterpreterLogData{
     PythonQtObjectPtr  m_mainContext;
    PythonQtScriptingConsole *m_console;
    void init();
public:
    QMap<QString,QString> exp;
    InterpreterPython();
    ~InterpreterPython()override;

    bool openConsole()override;
    bool openScript()override;

    void dataUpdate()override;
};

#endif // INTERPRETER_H
