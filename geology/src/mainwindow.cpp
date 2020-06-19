#include "mainwindow.h"
#include <QFileDialog>
#include "filereader.h"
#include "gfmloader.h"
#include "gfmsaver.h"
#include "interpreterpython.h"


MainWindow::MainWindow(QWidget *parent)
    : WindowForMenu(parent)
{
    m_menu = new Menu(this);
    m_menu->installEventFilter(this);

    m_mainHorLayout = new QHBoxLayout(this);

    m_logDataView = new LogDataView(this);
    m_logDataView->installEventFilter(this);

    m_mainHorLayout->addWidget(m_menu,100,Qt::AlignTop);
    m_mainHorLayout->addWidget(m_logDataView);
    this->setLayout(m_mainHorLayout);
    m_flagHideMenu = false;
}

MainWindow::~MainWindow()
{

}



bool MainWindow::eventFilter(QObject *o, QEvent *e){
    if(e->type() == QEvent::Enter){
        if(o == m_logDataView){
            if(m_flagHideMenu)
                m_menu->hideLeft();
            return true;
        }
        else if(o == m_menu){
                m_menu->showRight();
                return true;
        }
    }
    return false;
}

void MainWindow::openFile(){
    QFileDialog fileDialog;
    QString filePath = fileDialog.getOpenFileName(this, tr("Open File"),"C:/",tr("*.tlm *.gfm"));
    if(filePath == "")
        return;
    FileReader f_file(filePath);
    ILoaderLogData * f_loader = nullptr;
    QSharedPointer<ILogData> f_logData = nullptr;
    if(f_file.getType() == ".gfm"){
        f_loader = new GFMLoader(filePath);
    }
    if(f_loader){
        f_logData = ILogData::createLogData();
        f_logData->setName(filePath);
        m_logDataView->addLogData(f_logData);
        f_logData->setLoader(f_loader);
        f_logData->load();
        m_flagHideMenu = true;
    }
}

void MainWindow::saveGFM(){
    ILogData *f_logData = m_logDataView->curentLogData();
    if(!f_logData)
        return;
    ISaverLogData * gfmSaver = new GFMSaver();
    f_logData->setSaver(gfmSaver);
    f_logData->save();
}

void MainWindow::openConsolePython(){
    ILogData *f_logData = m_logDataView->curentLogData();
    if(!f_logData)
        return;
    if(!f_logData->isInterpreter()){
        IInterpreterLogData *f_interpreter = dynamic_cast<IInterpreterLogData *>(new InterpreterPython());
        f_logData->setInterpreter(f_interpreter);
    }
    f_logData->openInterpreterConsole();
}

void MainWindow::openInterpretations(){
    QDir dir(QDir().absolutePath()+ "/interpretations");
    dir.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
    QFileInfoList f_fileList = dir.entryInfoList();

    foreach(auto file,f_fileList)
        if(file.suffix() != "dll")
            f_fileList.removeOne(file);

    foreach(auto file,f_fileList){
        QString f_path = file.absoluteFilePath();
        QLibrary  lib(f_path);
        lib.load();
        qDebug() << lib.isLoaded() << f_path;
        typedef QString (*Fct) ();
        typedef ILogData *(*F)(ILogData *logData);
        Fct version = (Fct)(lib.resolve("version"));
        Fct name = (Fct)(lib.resolve("name"));
        F interpr = (F)(lib.resolve("interpretation"));
        if(version)
            qDebug() << version();
        if(name)
            qDebug() << name();
        if(interpr){
            QSharedPointer<ILogData> f_logData(interpr(m_logDataView->curentLogData()));
            m_logDataView->addLogData(f_logData);
        }
    }

}
