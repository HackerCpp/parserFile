#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "interpreter_global.h"
#include "ainterpreterlogdata.h"

class PythonEditor;
class PythonQtObjectPtr;
class PythonQtScriptingConsole;

class INTERPRETER_EXPORT InterpreterPython : public AinterpreterLogData{
    PythonQtObjectPtr *m_mainContext;
    PythonQtScriptingConsole *m_console;
    PythonEditor *m_pythonEditor;
    void init();
public:
    QMap<QString,QString> exp;
    InterpreterPython();
    ~InterpreterPython()override;

    bool openConsole()override;
    bool openScript()override;
    bool openEditor()override;

    void dataUpdate()override;
};

#endif // INTERPRETER_H
