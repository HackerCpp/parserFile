#include "inc/menu.h"
#include <QCoreApplication>

Menu::Menu(QWidget *parent)
    : QWidget(parent){
    this->mnuBarArray = new QVector<QMenuBar*>;
    this->mnuArray = new QVector<QMenu*>;
    this->layoutForMenu = new QVBoxLayout();
    QMenu * mainMenu= new QMenu("&Menu");
    mainMenu->addAction("&About Qt",qApp, SLOT(aboutQt()), Qt::CTRL + Qt::Key_Q);
    mainMenu->addAction("&ApplyStyle",this, SIGNAL(applyStyle()), Qt::CTRL + Qt::Key_A);
    mainMenu->addSeparator();
    mainMenu->addAction("&Exit", qApp, SLOT(quit()),Qt::Key_Escape);
    mnuArray->push_back(mainMenu);
    QMenu * fileMenu= new QMenu("&File");
    fileMenu->addAction("&Open file",this->parent(), SLOT(openFile()));
    mnuArray->push_back(fileMenu);
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


Menu::~Menu(){
    delete this->mnuArray;
    mnuArray = nullptr;
    delete this->mnuBarArray;
    this->mnuBarArray = nullptr;
    delete this->layoutForMenu;
    this->layoutForMenu = nullptr;
}
