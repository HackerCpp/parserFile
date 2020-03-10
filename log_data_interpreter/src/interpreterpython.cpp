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

}

InterpreterPython::~InterpreterPython(){

}

bool InterpreterPython::openConsole(){

    qDebug()<< "******************************************";
   qDebug() << m_curves->size();
    int i=0;
    foreach (QString key, m_curves->keys())

    {
       QString m = "A"+QString::number(i);
      ICurve* value=m_curves->value(key);
      m_mainContext.addObject(m, value);
      qDebug() << key << ":" << value;
        i++;

    }



    m_console->show();



    return true;
}

bool InterpreterPython::openScript(){

    qDebug() << "script python";
    return false;
}
