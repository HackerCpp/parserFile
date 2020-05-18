#include "mainwindow.h"
#include <QFileDialog>
#include "filereader.h"
#include "gfmloader.h"


MainWindow::MainWindow(QWidget *parent)
    : WindowForMenu(parent)
{
    m_menu = new Menu(this);
    m_menu->installEventFilter(this);

    m_mainHorLayout = new QHBoxLayout(this);

    m_logDataView = new LogDataView(this);
    m_logDataView->installEventFilter(this);
    m_logDataView->setMinimumSize(100,100);

    m_mainHorLayout->addWidget(m_menu,100,Qt::AlignTop);
    m_mainHorLayout->addWidget(m_logDataView);
    this->setLayout(m_mainHorLayout);

}

MainWindow::~MainWindow()
{

}



bool MainWindow::eventFilter(QObject *o, QEvent *e){
    if(e->type() == QEvent::Enter){
        if(o == m_logDataView){
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

    }
}

void MainWindow::saveGFM(){

}

void MainWindow::openConsolePython(){

}


