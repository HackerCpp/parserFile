#include "inc/tabs/tabgfm.h"
#include "inc/fileCreation/creategfm.h"
#include <QStyle>
#include <QDebug>
#include <QDateTime>
#include <QFileDialog>
#include "graphics.h"



TabGFM::TabGFM(QString path,QWidget *parent) : AbstractTab(parent){
    m_mainHLayout = new QHBoxLayout();
    m_gfm = new GFM(path);
    Graphics * graphics = new Graphics(m_gfm->getCurves());
    m_mainHLayout->addWidget(graphics);
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
