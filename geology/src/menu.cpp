#include "inc/menu.h"
#include <QCoreApplication>

Menu::Menu(QWidget *parent)
    : QWidget(parent){

    m_parentWindow = dynamic_cast<WindowForMenu *>(parent);
    if(!m_parentWindow)
        return;

    this->mnuBarArray = new QVector<QMenuBar*>;
    this->mnuArray = new QVector<QMenu*>;
    this->layoutForMenu = new QVBoxLayout();
    QMenu * mainMenu= new QMenu (tr("&Menu"),this);
    mainMenu->setObjectName("Menu");
    mainMenu->addAction (tr("&About Qt"),qApp, SLOT(aboutQt()), Qt::CTRL + Qt::Key_Q);
    mainMenu->addAction (tr("&ApplyStyle"),this, SIGNAL(applyStyle()), Qt::CTRL + Qt::Key_A);
    mainMenu->addSeparator();
    mainMenu->addAction (tr("&Interpretations"),m_parentWindow, SLOT(openInterpretations()), Qt::CTRL + Qt::Key_W);
    mainMenu->addAction (tr("&Constructor"),m_parentWindow, SLOT(openConstructor()), Qt::CTRL + Qt::Key_K);
    mainMenu->addSeparator();
    mainMenu->addAction (tr("&Exit"), qApp, SLOT(quit()),Qt::Key_Escape);
    mnuArray->push_back(mainMenu);
    QMenu * fileMenu= new QMenu (tr("&File"),this);
    fileMenu->setObjectName("File");
    fileMenu->addAction(tr("&Open file"),m_parentWindow, SLOT(openFile()));
    QMenu *saveFileMenu = new QMenu (tr("Save"),this);
    saveFileMenu->addAction (tr("&GFM"),m_parentWindow, SLOT(saveGFM()));
    saveFileMenu->addAction (tr("&LIS"),m_parentWindow, SLOT(saveLIS()));
    fileMenu->addMenu(saveFileMenu);
    mnuArray->push_back(fileMenu);
    QMenu * interpreterMenu= new QMenu (tr("&Script"),this);
    interpreterMenu->setObjectName("Script");
    QMenu *pythonMenu = new QMenu (tr("Python"),this);
    pythonMenu->addAction (tr("&OpenConsole"),m_parentWindow, SLOT(openConsolePython()));
    pythonMenu->addAction (tr("&OpenEditor"),m_parentWindow, SLOT(openEditorPython()));
    pythonMenu->addAction (tr("&AddDataCalib"),m_parentWindow, SLOT(insertCalibrationInTheScript()));
    interpreterMenu->addMenu(pythonMenu);
    mnuArray->push_back(interpreterMenu);
    foreach(auto mnu, *mnuArray){
        QMenuBar *bar = new QMenuBar();
        bar->addMenu(mnu);
        mnuBarArray->push_back(bar);
        //pythonContext->addObject(mnu->objectName(),mnu);
    }
    foreach(auto mnuBar, *mnuBarArray){
        this->layoutForMenu->addWidget(mnuBar);
    }
    layoutForMenu->addStretch(1000);
    this->setLayout(this->layoutForMenu);
    this->setMaximumWidth(120);
    this->setMaximumHeight(40 * mnuBarArray->size());
}

void Menu::hideLeft(){
    this->setMaximumWidth(30);
}
void Menu::showRight(){
    this->setMaximumWidth(120);
}
Menu::~Menu(){
    delete this->mnuArray;
    mnuArray = nullptr;
    delete this->mnuBarArray;
    this->mnuBarArray = nullptr;
    delete this->layoutForMenu;
    this->layoutForMenu = nullptr;
}
