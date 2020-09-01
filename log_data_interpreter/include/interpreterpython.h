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

    bool addObject(const QString &name, QObject *object)override;
    bool addVariable(const QString &name, const QVariant &v)override;
    void dataUpdate()override;

    bool executeScriptFromFile(const QString& filename)override;
    bool executeScriptFromString(const QString& script)override;

    PythonQtObjectPtr *context(){return m_mainContext;}
    PythonQtScriptingConsole *console(){return m_console;}
};

#endif // INTERPRETER_H
