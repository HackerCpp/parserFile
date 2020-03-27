#include "interpreterPython.h"
#include <QApplication>
#include "QWidget"
#include <PythonQt.h>
#include <PythonQt_QtAll.h>
#include "gui/PythonQtScriptingConsole.h"
//#include "wrapper_curve.h"
#include "Wrapper_python.h"

InterpreterPython::InterpreterPython(){
    PythonQt::init(PythonQt::IgnoreSiteModule | PythonQt::RedirectStdOut,"LogData");
    PythonQt_QtAll::init();
    PythonQt::self()->registerCPPClass("ICurve","","Curves",PythonQtCreateObject<WrapperIcurvePython>);
    //from LogData.Curves import*
    m_mainContext = PythonQt::self()->getMainModule();
    m_console = new PythonQtScriptingConsole(NULL, m_mainContext);
    m_console->setStyleSheet("PythonQtScriptingConsole{background-color:black;color:white;font-size: 24px;}");
}

InterpreterPython::~InterpreterPython(){

}

bool InterpreterPython::openConsole(){
    int i=0;
    foreach (QString key, m_curves->keys())

    {
       QString m = key;

       m=m.remove(":");
       m=m.remove(")");
       m=m.remove("(");
       m="A_"+m;
       m=m.remove("_");
       m=m.remove("-");
       m=m.remove(".");

      ICurve* value=m_curves->value(key);
      m_mainContext.addObject(m, value);
      i++;

    }



    m_console->show();



    return true;
}

bool InterpreterPython::openScript(){

    qDebug() << "script python";
    return false;
}
