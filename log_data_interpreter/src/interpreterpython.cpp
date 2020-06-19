#include "interpreterPython.h"
#include <QApplication>
#include "QWidget"
#include <PythonQt.h>
#include <PythonQt_QtAll.h>
#include "gui/PythonQtScriptingConsole.h"
//#include "wrapper_curve.h"
#include "Wrapper_python.h"
#include <QFileDialog>
#include <datablock.h>

InterpreterPython::InterpreterPython(){
    PythonQt::init(PythonQt::IgnoreSiteModule | PythonQt::RedirectStdOut,"LogData");
    PythonQt_QtAll::init();
    PythonQt::self()->registerCPPClass("ICurve","","Curves",PythonQtCreateObject<WrapperIcurvePython>);

    //from LogData.Curves import*

    m_mainContext = nullptr;
    m_console = nullptr;

}

InterpreterPython::~InterpreterPython(){
    if(m_mainContext){delete m_mainContext;m_mainContext = nullptr;}
    if(m_console){delete m_console;m_console = nullptr;}
}

void InterpreterPython::init(){
    if(!m_mainContext){
        m_mainContext = PythonQt::self()->getMainModule();
        m_console = new PythonQtScriptingConsole(NULL, m_mainContext);
    }
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
            if(!m_mainContext.getVariable(f_curveNameForPython).isValid())
                m_mainContext.addObject(f_curveNameForPython, curve);
        }

    }

}

bool InterpreterPython::openConsole(){
    init();
    m_console->append("py> from LogData.Curves import*");
    m_console->show();
    return true;
}

bool InterpreterPython::openScript(){
    init();
    QString fileName = QFileDialog::getOpenFileName(nullptr,"Выберите скрипт","*.py","PYTHON(*.py)");
    m_mainContext.evalFile(fileName);
    return false;
}

void InterpreterPython::dataUpdate(){
   init();
}
