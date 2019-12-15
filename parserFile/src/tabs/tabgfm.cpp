#include "inc/tabs/tabgfm.h"
#include "inc/fileCreation/creategfm.h"
#include <QStyle>
#include <QDebug>
#include <QDateTime>
#include <QFileDialog>
#include "forms.h"
#include "board.h"
#include "graphics.h"
#include <QTabBar>
#include <QTabWidget>
#include <QThread>



TabGFM::TabGFM(QString path,QWidget *parent) : AbstractTab(parent){
    m_mainHLayout = new QHBoxLayout();
    m_gfm = new GFM(path);
    while(!m_gfm->isReady()){}
    QTabWidget * tabWidget = new QTabWidget();
    Forms * forms = m_gfm->getForms();
    QList<Board*>*boards = forms->boards();
    foreach(Board *board,*boards){
        tabWidget->addTab(new Graphics(board,m_gfm->getCurves()),board->name());
    }
    m_mainHLayout->addWidget(tabWidget);
    setLayout(m_mainHLayout);
}

void TabGFM::saveGFM(){
    QDateTime date;
    QString stringDate = date.currentDateTime().toString("dd_MM_yyyy_hh_mm");
    QString fileName = QFileDialog::getSaveFileName(nullptr,"Сохранить файл как",stringDate,"GFM(*.gfm)");
    m_gfm->saveFile(fileName);
}

TabGFM::~TabGFM(){
    delete m_gfm;
    m_gfm = nullptr;
}
