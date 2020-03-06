#include "interpreterPython.h"
#include <QApplication>
#include "QWidget"
#include <PythonQt.h>
#include <PythonQt_QtAll.h>
#include "gui/PythonQtScriptingConsole.h"
//#include "wrapper_curve.h"
#include "Wrapper_python.h"

InterpreterPython::InterpreterPython(){
    PythonQt::init(PythonQt::IgnoreSiteModule | PythonQt::RedirectStdOut);
    PythonQt_QtAll::init();
    PythonQt::self()->registerCPPClass("ICurve","","example",PythonQtCreateObject<WrapperIcurvePython>);
    m_mainContext = PythonQt::self()->getMainModule();
    m_console = new PythonQtScriptingConsole(NULL, m_mainContext);

}

InterpreterPython::~InterpreterPython(){

}

bool InterpreterPython::openConsole(){

/*
    exp.insert("aaa","bbbb");
    exp.insert("aaaa","bbbb");
    exp.insert("aa","bbbb");
    foreach (QString key, exp.keys())

    {

      QString value=exp.value(key);

      qDebug() << key << ":" << value;

    }
    */
//    if(!m_curves)
//    {
    //    qDebug()<<"невозможно открыть интерпретатор, кривые не найдены";
//        return false;
 //   }
  //  qDebug() << m_curves->size();
    m_console->show();



    return true;
}

bool InterpreterPython::openScript(){

    qDebug() << "script python";
    return false;
}
