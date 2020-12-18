#include "interpreterpython.h"
#include <QApplication>
#include "QWidget"
#include <PythonQt.h>
#include <PythonQt_QtAll.h>
#include "Wrapper_python.h"
#include <QFileDialog>
#include <datablock.h>
#include "gui/PythonQtScriptingConsole.h"
#include "pythoneditor.h"
#include <QWidget>


InterpreterPython::InterpreterPython()
: m_pythonEditor(nullptr){
    PythonQt::init(PythonQt::IgnoreSiteModule | PythonQt::RedirectStdOut,"LogData");
    PythonQt_QtAll::init();

    PythonQt::self()->registerCPPClass("ICurve","","Curves",PythonQtCreateObject<WrapperIcurvePython>);

    m_mainContext = new PythonQtObjectPtr(PythonQt::self()->createUniqueModule());
    m_mainContext->evalScript("from LogData.Curves import*");
    m_console = new PythonQtScriptingConsole(NULL, *m_mainContext);
}

InterpreterPython::~InterpreterPython(){
    //if(m_mainContext){delete m_mainContext;m_mainContext = nullptr;}
    if(m_console){delete m_console;m_console = nullptr;}
}

void InterpreterPython::init(){
    if(!m_blocks)
        return;
    foreach(auto block,*m_blocks){
        DataBlock *f_block = dynamic_cast<DataBlock *>(block);
        if(!f_block)
            continue;
        foreach(auto curve,*f_block->curves()){
            QString f_curveNameForPython = "C_" + curve->mnemonic() + "_" + curve->shortCut().device();
            f_curveNameForPython = f_curveNameForPython.remove("[");
            f_curveNameForPython = f_curveNameForPython.remove("]");
            f_curveNameForPython = f_curveNameForPython.remove("(");
            f_curveNameForPython = f_curveNameForPython.remove(")");
            f_curveNameForPython = f_curveNameForPython.remove("-");
            f_curveNameForPython = f_curveNameForPython.remove("/");
            if(!m_mainContext->getVariable(f_curveNameForPython).isValid())
                m_mainContext->addObject(f_curveNameForPython, curve);
        }

    }

}

bool InterpreterPython::openConsole(){
    init();
    m_console->show();
    return true;
}

bool InterpreterPython::openScript(){
    init();
    QString fileName = QFileDialog::getOpenFileName(nullptr,"Выберите скрипт","*.py","PYTHON(*.py)");
    m_mainContext->evalFile(fileName);
    return false;
}

bool InterpreterPython::openEditor(){
    init();
    if(!m_pythonEditor)
        m_pythonEditor = new PythonEditor(this,nullptr);
    m_pythonEditor->show();
    return true;
}

bool InterpreterPython::addObject(const QString &name, QObject *object){
    m_mainContext->addObject(name, object);
    return true;
}

bool InterpreterPython::addVariable(const QString &name, const QVariant &v){
    m_mainContext->addVariable(name, v);
    return true;
}

void InterpreterPython::dataUpdate(){
   init();
}

bool InterpreterPython::executeScriptFromFile(const QString& filename){
    m_mainContext->evalFile(filename);
    return true;
}

bool InterpreterPython::executeScriptFromString(const QString& script){
    m_mainContext->evalScript(script);
    return true;
}
