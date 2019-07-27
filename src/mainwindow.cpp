#include "inc/mainwindow.h"
#include "inc/filereader.h"
#include "inc/parsers/parsertlm.h"
#include "inc/models/modeltlm.h"
#include "inc/parsers/parserDataCm.h"
#include <QtWidgets>
#include <QDebug>


MainWindow::MainWindow(QWidget *parent){
    this->setParent(parent);

    FileReader file("D:\\Project\\ParserFile\\parserFile\\tlm\\2019_07_25_09-40-06.tlm");

    //FileReader file("D:\\MyQtProgram\\parserGfm\\parserFile\\tlm\\2019_07_25_09-40-06.tlm");

    ParserTLM parserTlm(file.getHexString());

    ModelTlm *model = new ModelTlm(parserTlm.getBlocks());
    ParserDataCm deviceData(parserTlm.getBlocks());
    QTreeView * trv= new QTreeView();
    QTableView *table = new QTableView();
    trv->setAnimated(true);
    QVBoxLayout *verticalLayout = new QVBoxLayout(this);
    QWidget *header = new QWidget();
    QVBoxLayout *verticalLayoutHeader = new QVBoxLayout();
    header->setMinimumHeight(100);

    header->setLayout(verticalLayoutHeader);
    table->setModel(model);
    trv->setModel(model);
    QHBoxLayout *blay = new QHBoxLayout();

    mnuBar = new QMenuBar();
    QMenuBar *mnuBar2 = new QMenuBar();
    QVBoxLayout *g = new QVBoxLayout();
    mnuBar->setMaximumHeight(30);
    mnuBar->setMaximumWidth(60);
    mnuBar2->setMaximumWidth(60);
    QMenu*   pmnu   = new QMenu("&Menu");
    QMenu*   pmn   = new QMenu("&Menu");
    g->addWidget(mnuBar);
    g->addWidget(mnuBar2);

    pmnu->addAction("&About Qt", qApp,SLOT(aboutQt()),Qt::CTRL + Qt::Key_Q);
    pmnu->addAction("&About Qt", qApp,SLOT(aboutQt()),Qt::CTRL + Qt::Key_Q);
    pmnu->addAction("&About Qt", qApp,SLOT(aboutQt()),Qt::CTRL + Qt::Key_Q);
    mnuBar->addMenu(pmnu);
    mnuBar2->addMenu(pmn);

    blay->addLayout(g);
    blay->addWidget(trv);
    blay->addWidget(table);

    verticalLayout->addWidget(header);
    verticalLayout->addLayout(blay);
    this->setLayout(verticalLayout);
    qApp->setStyleSheet("QWidget {background-color:#FFFACD;position:absolute;left:20px;}"
                        "QTreeView:header {background-color:green;position:absolute;left:20px;}");


}

MainWindow::~MainWindow(){


}
