#include "inc/tabs/tabgfm.h"
#include "inc/fileCreation/creategfm.h"
#include <QStyle>
#include <QDebug>
#include <QDateTime>
#include <QFileDialog>
#include "forms.h"
#include "board.h"
#include "graphics.h"




TabGFM::TabGFM(QString path,QWidget *parent) : AbstractTab(parent){
    m_barHLayout = new QHBoxLayout();
    m_mainVerticalLayout = new QVBoxLayout();
    m_gfm = new GFM(path);
    m_toolBar = new QWidget();
    m_comboBox = new QComboBox();
    m_comboBox->insertItem(0,"Время");
    m_comboBox->insertItem(1,"Глубина");
    m_barHLayout->addWidget(m_comboBox);
    m_toolBar->setLayout(m_barHLayout);
    while(!m_gfm->isReady()){}
    m_tabWidget = new QTabWidget();
    Forms * forms = m_gfm->getForms();
    m_boards = forms->boards();
    foreach(Board *board,*m_boards){
        m_tabWidget->addTab(new Graphics(board,m_gfm->getCurves()),board->name());
    }
    m_mainVerticalLayout->addWidget(m_toolBar);
    m_mainVerticalLayout->addWidget(m_tabWidget);
    setLayout(m_mainVerticalLayout);
    connect(m_comboBox,static_cast<void(QComboBox::*)(int)>(&QComboBox::currentIndexChanged),this,&TabGFM::changeDrawType);
}
void TabGFM::changeDrawType(int index){
    Graphics * graphics = dynamic_cast<Graphics *>(m_tabWidget->currentWidget());
    if(graphics){
        if(index)
            graphics->drawDepth();
        else
            graphics->drawTime();
    }
}
void TabGFM::saveGFM(){
    QDateTime date;
    QString stringDate = date.currentDateTime().toString("dd_MM_yyyy_hh_mm");
    QString fileName = QFileDialog::getSaveFileName(nullptr,"Сохранить файл как",stringDate,"GFM(*.gfm)");
    m_gfm->saveFile(fileName);
}

TabGFM::~TabGFM(){
    if(m_gfm){
        delete m_gfm;
        m_gfm = nullptr;
    }
    if(m_tabWidget){
        delete m_tabWidget;
        m_tabWidget = nullptr;
    }
}
