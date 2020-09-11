#include "mainwindow.h"
#include <QFileDialog>
#include "filereader.h"
#include "gfmloader.h"
#include "lasloader.h"
#include "gfmsaver.h"
#include "interpreterpython.h"
#include "tabinterpretations.h"
#include "geometrologydb.h"


MainWindow::MainWindow(QWidget *parent)
    : WindowForMenu(parent)
{
    qputenv("PYTHONPATH",QString(QDir().absolutePath() + "/python3/Lib").toLatin1());

    m_menu = new Menu(this);
    //m_pythonInterpreter.evalFile(QDir().absolutePath() + "/scripts/mainMenu/mainMenu.py");
    m_menu->installEventFilter(this);

    m_mainHorLayout = new QHBoxLayout(this);

    m_logDataView = new LogDataView(this);
    m_logDataView->installEventFilter(this);
    m_logDataView->hide();

    m_mainHorLayout->addWidget(m_menu,100,Qt::AlignTop);
    m_mainHorLayout->addWidget(m_logDataView);

    this->setLayout(m_mainHorLayout);
    m_flagHideMenu = false;
    m_settings = new QSettings("settings.ini",QSettings::IniFormat);
    QObject::connect(qApp, SIGNAL(aboutToQuit()),this, SLOT(quit()));
}

MainWindow::~MainWindow(){
    if(m_settings){delete m_settings; m_settings = nullptr;}

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
    QString f_openPath = m_settings->value("paths/pathOpenFile").toString();
    QString filePath = fileDialog.getOpenFileName(this, tr("Open File"),f_openPath,tr("*.forms *.gfm *.las"));
    if(filePath == "")
        return;
    m_settings->setValue("paths/pathOpenFile",filePath);
    FileReader f_file(filePath);
    ILoaderLogData * f_loader = nullptr;
    QSharedPointer<ILogData> f_logData = nullptr;
    if(f_file.getType() == ".gfm" || f_file.getType() == ".forms"){
        f_loader = new GFMLoader(filePath);
    }
    else if(f_file.getType() == ".las" || f_file.getType() == ".LAS"){
        f_loader = new LasLoader(filePath);
    }
    else{
        return;
    }
    m_logDataView->show();
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

void MainWindow::saveLIS(){
    QString f_fileName = QDir().absolutePath()+ "/converters/lisConverter.dll";
    //f_fileName = "E:/MyQtProgram/parserGfm/ConverterLis/build-lisConverter-Desktop_Qt_5_14_0_MinGW_64_bit-Release/lisConverter.dll";

    QLibrary  lib(f_fileName);

    //typedef int(*Fu)( char *gfm_filename );
    typedef int(*Fu)();
    Fu f_function = (Fu)lib.resolve("f");
    if(f_function)
        f_function();

    //qDebug() << lib.resolve("f");
    //lib.unload();
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

void MainWindow::openEditorPython(){
    ILogData *f_logData = m_logDataView->curentLogData();
    if(!f_logData)
        return;
    if(!f_logData->isInterpreter()){
        IInterpreterLogData *f_interpreter = dynamic_cast<IInterpreterLogData *>(new InterpreterPython());
        f_logData->setInterpreter(f_interpreter);
    }
    f_logData->openInterpreterEditor();
}

void MainWindow::insertCalibrationInTheScript(){
    ILogData *f_logData = m_logDataView->curentLogData();
    if(!f_logData)
        return;
    QFileDialog fileDialog;
    GeometrologyDB *f_geometrologyDB = new GeometrologyDB();
    f_geometrologyDB->setTypeDB(GeometrologyDB::SQLITE);
    QString f_openPath = m_settings->value("paths/pathOpenDB").toString();
    QString filePath = fileDialog.getOpenFileName(this, tr("Open File"),f_openPath,tr("*.db"));
    if(filePath == "")
        return;
    m_settings->setValue("paths/pathOpenDB",filePath);
    f_geometrologyDB->setNameDB(filePath);
    if(f_geometrologyDB->connectDB())
        qDebug() << "connect";
    else
        return;
    f_geometrologyDB->setInterpreterInterpreter(f_logData->interpreter());
}

void MainWindow::openInterpretations(){
    ILogData *f_urentLogdata = m_logDataView->curentLogData();
    if(!f_urentLogdata)
        return;
    QDir dir(QDir().absolutePath()+ "/interpretations/release");
    dir.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
    QFileInfoList f_fileList = dir.entryInfoList();

    foreach(auto file,f_fileList)
        if(file.suffix() != "dll")
            f_fileList.removeOne(file);
    QString f_path = TabInterpretations().getAbsolutePath(f_fileList);
    if(f_path == nullptr)
        return;
    QLibrary  lib(f_path);
    lib.load();
    typedef ILogData *(*FIlogData)(ILogData *);
    FIlogData interpr = (FIlogData)(lib.resolve("interpretation"));
    if(interpr){
        QSharedPointer<ILogData> f_logData(interpr(f_urentLogdata));
        m_logDataView->addLogData(f_logData);
    }
}

void MainWindow::openConstructor(){

}
