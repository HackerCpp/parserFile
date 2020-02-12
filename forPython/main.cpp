//#include "mainwindows.h"

#include <QApplication>
#include <PythonQt.h>
#include <PythonQt_QtAll.h>
#include "gui/PythonQtScriptingConsole.h"

int main(int argc, char *argv[]){
    QApplication a(argc, argv);
    //MainWindows w;

    PythonQt::init(PythonQt::IgnoreSiteModule | PythonQt::RedirectStdOut);
    PythonQt_QtAll::init();

    PythonQtObjectPtr  mainContext = PythonQt::self()->getMainModule();
    PythonQtScriptingConsole console(NULL, mainContext);
    //PythonQt::self()->addDecorators(new PyExampleDecorators());
   // PythonQt::self()->registerCPPClass("MyClass","", "example",PythonQtCreateObject<PyExampleDecorators>);
    mainContext.evalFile(":example.py");

    console.show();
    //w.show();
    return a.exec();
}
