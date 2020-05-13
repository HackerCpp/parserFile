#include "inc/menu.h"
#include <QCoreApplication>

Menu::Menu(QWidget *parent)
    : QWidget(parent){
    this->mnuBarArray = new QVector<QMenuBar*>;
    this->mnuArray = new QVector<QMenu*>;
    this->layoutForMenu = new QVBoxLayout();
    QMenu * mainMenu= new QMenu("&Menu",this);
    mainMenu->addAction("&About Qt",qApp, SLOT(aboutQt()), Qt::CTRL + Qt::Key_Q);
    mainMenu->addAction("&ApplyStyle",this, SIGNAL(applyStyle()), Qt::CTRL + Qt::Key_A);
    mainMenu->addSeparator();
    mainMenu->addAction("&Exit", qApp, SLOT(quit()),Qt::Key_Escape);
    mnuArray->push_back(mainMenu);
    QMenu * fileMenu= new QMenu("&File",this);
    fileMenu->addAction("&Open file",this->parent(), SLOT(openFile()));
    QMenu *saveFileMenu = new QMenu("Save",this);
    saveFileMenu->addAction("&CSV",this->parent(), SLOT(saveCSV()));
    saveFileMenu->addAction("&GFM",this->parent(), SLOT(saveGFM()));
    fileMenu->addMenu(saveFileMenu);
    mnuArray->push_back(fileMenu);
    QMenu * interpreterMenu= new QMenu("&Script",this);
    QMenu *pythonMenu = new QMenu("Python",this);
    pythonMenu->addAction("&OpenConsole",this->parent(), SLOT(openConsolePython()));
    interpreterMenu->addMenu(pythonMenu);
    mnuArray->push_back(interpreterMenu);
    for(auto mnu = mnuArray->begin(); mnu < mnuArray->end(); mnu++){
        QMenuBar *bar = new QMenuBar();
        bar->addMenu(*mnu);
        mnuBarArray->push_back(bar);
    }
    for(auto mnuBar = mnuBarArray->begin(); mnuBar < mnuBarArray->end(); mnuBar ++){
        this->layoutForMenu->addWidget(*mnuBar);
    }
    layoutForMenu->addStretch(1000);
    this->setLayout(this->layoutForMenu);
    this->setMaximumWidth(100);
    this->setMaximumHeight(40 * mnuBarArray->size());

}

void Menu::hideLeft(){
    this->setMaximumWidth(30);
}
void Menu::showRight(){
    this->setMaximumWidth(100);
}
Menu::~Menu(){
    delete this->mnuArray;
    mnuArray = nullptr;
    delete this->mnuBarArray;
    this->mnuBarArray = nullptr;
    delete this->layoutForMenu;
    this->layoutForMenu = nullptr;
}
