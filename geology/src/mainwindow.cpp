#include "mainwindow.h"
#include <QFileDialog>
#include "filereader.h"
#include "gfmloader.h"
#include "lasloader.h"
#include "lisloader.h"
#include "gfmsaver.h"
#include "lassaver.h"
#include "lissaver.h"
#include "tabinterpretations.h"
#include "geometrologydb.h"
#include <QProcess>
#include <QMessageBox>
#include "specfiledialog.h"
#include "geoloader.h"
#include "interpretercreater.h"
#include <QInputDialog>

MainWindow::MainWindow(QWidget *parent)
    : WindowForMenu(parent){
    qputenv("PYTHONPATH",QString(QDir().absolutePath() + "/python3/Lib;" +
                                 QDir().absolutePath() + "/python3/Lib/site-packages;" +
                                 QDir().absolutePath() + "/python3/DLLs;" +
                                 QDir().absolutePath() + "/python3;").toLatin1());

    m_menu = new Menu(this);
    m_menu->installEventFilter(this);

    m_mainHorLayout = new QHBoxLayout(this);

    m_logDataView = new LogDataView(this);
    m_logDataView->installEventFilter(this);
    m_logDataView->hide();

    m_mainHorLayout->addWidget(m_menu,0,Qt::AlignTop);
    m_mainHorLayout->addWidget(m_logDataView);
    m_mainHorLayout->setMargin(0);

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
    //SpecFileDialog fileDialog;
    QString f_openPath = m_settings->value("paths/pathOpenFile").toString();
    //QString filePath = fileDialog.specGetOpenFileName(this, tr("Open File"),f_openPath,tr("*.forms *.gfm *.las *.lis"));
    QString filePath = QFileDialog().getOpenFileName(this, tr("Open File"),f_openPath,tr("*.forms *.gfm *.las *.geo *.lis"));
    if(filePath == "")
        return;
    m_settings->setValue("paths/pathOpenFile",filePath);
    FileReader f_file(filePath);
    ILoaderLogData * f_loader = nullptr;
    if(f_file.getType() == ".gfm" || f_file.getType() == ".forms"){
        f_loader = new GFMLoader(filePath);
    }
    else if(f_file.getType() == ".las" || f_file.getType() == ".LAS"){
        f_loader = new LasLoader(filePath);
    }
    /*else if(f_file.getType() == ".lis" || f_file.getType() == ".LIS"){
        f_loader = new LisLoader(filePath);
    }*/
    else if(f_file.getType() == ".geo"){
        f_loader = new GeoLoader(filePath);
    }
    else{
        return;
    }
    m_logDataView->show();
    if(f_loader){
        QSharedPointer<ILogData> f_logData = ILogData::createLogData();
        f_logData->setName(filePath);
        m_logDataView->addLogData(f_logData);
        f_logData->setLoader(f_loader);
        f_logData->load();
        m_flagHideMenu = true;
    }
}

void MainWindow::addFromFile(){
    QString f_openPath = m_settings->value("paths/pathOpenFile").toString();
    QString filePath = QFileDialog().getOpenFileName(this, tr("Open File"),f_openPath,tr("*.forms *.gfm *.las *.geo *.lis"));
    if(filePath == "")
        return;
    m_settings->setValue("paths/pathOpenFile",filePath);
    FileReader f_file(filePath);
    ILoaderLogData * f_loader = nullptr;
    if(f_file.getType() == ".gfm" || f_file.getType() == ".forms"){
        f_loader = new GFMLoader(filePath);
    }
    else if(f_file.getType() == ".las" || f_file.getType() == ".LAS"){
        f_loader = new LasLoader(filePath);
    }
    /*else if(f_file.getType() == ".lis" || f_file.getType() == ".LIS"){
        f_loader = new LisLoader(filePath);
    }*/
    else if(f_file.getType() == ".geo"){
        f_loader = new GeoLoader(filePath);
    }
    else{
        return;
    }
    if(f_loader){
        ILogData *  f_logData = m_logDataView->curentLogData();
        if(f_logData){
            f_logData->setLoader(f_loader);
            f_logData->load();
        }
    }
}

void MainWindow::saveFile(ISaverLogData *saver){
    ILogData *f_logData = m_logDataView->curentLogData();
    if(!f_logData)
        return;
    f_logData->setSaver(saver);
    f_logData->save();
    connect(saver,SIGNAL(ready(QString)),this,SLOT(fileExists(QString)));
}

void MainWindow::saveGFM(){
    saveFile(new GFMSaver());
}

void MainWindow::saveLIS(){
    saveFile(new LisSaver());
}

void MainWindow::saveLAS(){
    saveFile(new LASSaver());
}

void MainWindow::fileExists(QString filePath){
    if(filePath.isEmpty()){
        QMessageBox::warning(this, tr("Error"),tr("Failed to save the file "));
        return;
    }
    QMessageBox::information(this, tr("File exists"),tr("File exists ") + filePath);

}

void MainWindow::openConsolePython(){
    ILogData *f_logData = m_logDataView->curentLogData();
    if(!f_logData)
        return;
    if(!f_logData->isInterpreter()){
        IInterpreterLogData *f_interpreter = InterpreterCreater::create();
        f_logData->setInterpreter(f_interpreter);
    }
    f_logData->openInterpreterConsole();
}

void MainWindow::openEditorPython(){
    ILogData *f_logData = m_logDataView->curentLogData();
    if(!f_logData)
        return;
    if(!f_logData->isInterpreter()){
        IInterpreterLogData *f_interpreter = InterpreterCreater::create();
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

void MainWindow::addLibraryPython(){
    bool bOk;
    QString f_name = QInputDialog::getText( 0, tr("Download python library"),tr("Lybrary name:"),QLineEdit::Normal,"",&bOk);
    InterpreterCreater::create()->addLibrary(f_name);
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

void MainWindow::update(){
    if (QMessageBox::Yes == QMessageBox::question(this, tr("Update?"),
                              tr("The program will close and start updating, and all unsaved data will be lost. Update?"),
                              QMessageBox::Yes|QMessageBox::No)){
        QProcess f_process;
        f_process.startDetached(QDir().currentPath() + "/updater/updater.exe",
                                QStringList() << "http://www.gfm.ru/kedr_files/x64/geology_loader.xml" << ".//" );
        disconnect(qApp, SIGNAL(aboutToQuit()),this, SLOT(quit()));
        qApp->quit();
        //exit(0);
    }
}

void MainWindow::quit(){
    if (QMessageBox::Yes == QMessageBox::question(this, tr("Close?"),
                              tr("The app will close and all unsaved data will be lost. Close?"),
                              QMessageBox::Yes|QMessageBox::No)){
        disconnect(qApp, SIGNAL(aboutToQuit()),this, SLOT(quit()));
        qApp->quit();//exit(0);
    }
    else
        qApp->exec();
}

void MainWindow::closeEvent (QCloseEvent *event){
    event->ignore();
    qApp->quit();
}
