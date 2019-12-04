#include "inc/tabs/tabgfm.h"
#include "inc/fileCreation/creategfm.h"
#include <QStyle>
#include <QDebug>
#include <QDateTime>
#include <QFileDialog>
#include "graphics.h"



TabGFM::TabGFM(QString path,QWidget *parent) : AbstractTab(parent){
    //ParserGFM *pGfm = new ParserGFM(file);
    m_mainHLayout = new QHBoxLayout();
    m_splitter = new QSplitter;
    m_gfm = new GFM(path);
    QDateTime date;
    //QString stringDate = date.currentDateTime().toString("dd_MM_yyyy_hh_mm");
    Graphics * graphics = new Graphics(m_gfm->getCurves());
    m_mainHLayout->addWidget(graphics);
    setLayout(m_mainHLayout);
    //QString fileName = QFileDialog::getSaveFileName(nullptr,"Сохранить файл как",stringDate,"GFM(*.gfm)");

}

void TabGFM::saveGFM(){
    CreateGFM gfmFile(m_blocks);
    gfmFile.create();
}
TabGFM::~TabGFM(){
    delete m_gfm;
    m_gfm = nullptr;
}
