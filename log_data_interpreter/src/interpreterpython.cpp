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
#include <QFile>
#include "translaterrustoing.h"


InterpreterPython::InterpreterPython()
: m_pythonEditor(nullptr){
    qputenv("PYTHONPATH",QString(QDir().absolutePath() + "/python3/Lib;" +
                                 QDir().absolutePath() + "/python3/Lib/site-packages;" +
                                 QDir().absolutePath() + "/python3/DLLs;" +
                                 QDir().absolutePath() + "/python3;" +
                                 QDir().absolutePath() + "/python3/Scripts;").toLatin1());
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
    TranslaterRusToIng f_translater;
    foreach(auto block,*m_blocks){
        DataBlock *f_block = dynamic_cast<DataBlock *>(block);
        if(!f_block)
            continue;
        foreach(auto curve,*f_block->curves()){
            QString f_curveNameForPython = "C_" + curve->mnemonic() + "_" + curve->shortCut().device() + curve->shortCut().dateTime();
            f_curveNameForPython = f_curveNameForPython.remove("[");
            f_curveNameForPython = f_curveNameForPython.remove("]");
            f_curveNameForPython = f_curveNameForPython.remove("(");
            f_curveNameForPython = f_curveNameForPython.remove(")");
            f_curveNameForPython = f_curveNameForPython.remove("-");
            f_curveNameForPython = f_curveNameForPython.remove("/");
            if(!m_mainContext->getVariable(f_curveNameForPython).isValid())
                m_mainContext->addObject(f_translater.translate(f_curveNameForPython), curve);
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

InterpreterEditor *InterpreterPython::editor(){
    init();
    if(!m_pythonEditor)
        m_pythonEditor = new PythonEditor(this,nullptr);
    return m_pythonEditor;
}

bool InterpreterPython::addLibrary(QString nameLibrary){
    QProcess *f_process = new QProcess();
    QFile file(QDir().currentPath() + "/python3/lastCommand.bat");
    file.open(QIODevice::WriteOnly);
    file.write(QString("start " + QDir().currentPath() + "/python3/python.exe -m pip install " +
    nameLibrary).toLatin1());
    file.close();
    f_process->startDetached(QDir().currentPath() + "/python3/lastCommand.bat",QStringList());
    connect(f_process,&QProcess::readyReadStandardOutput,[=](){qDebug() << f_process->readAllStandardOutput();});
    return true;
}

bool InterpreterPython::executeScriptFromFile(const QString& filename){
    m_mainContext->evalFile(filename);
    return true;
}

bool InterpreterPython::executeScriptFromString(const QString& script){
    m_mainContext->evalScript(script);
    return true;
}
