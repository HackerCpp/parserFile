#include "interpreterpython.h"
#include <QApplication>
#include <PythonQt.h>
#include <PythonQt_QtAll.h>
#include "gui/PythonQtScriptingConsole.h"
InterpreterPython::InterpreterPython()
{

}

InterpreterPython::~InterpreterPython(){

}

bool InterpreterPython::openConsole(){
    qDebug() << "Console interpreter python";
    PythonQt::init(PythonQt::IgnoreSiteModule | PythonQt::RedirectStdOut);
    PythonQt_QtAll::init();

    PythonQtObjectPtr  mainContext = PythonQt::self()->getMainModule();
    PythonQtScriptingConsole console(NULL, mainContext);
    //PythonQt::self()->addDecorators(new PyExampleDecorators());
   // PythonQt::self()->registerCPPClass("MyClass","", "example",PythonQtCreateObject<PyExampleDecorators>);
    mainContext.evalFile(":example.py");

    console.show();
    return true;
}

bool InterpreterPython::openScript(){
    return true;
}
