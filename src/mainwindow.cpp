#include "inc/mainwindow.h"
#include "inc/filereader.h"
#include "inc/parsers/parsertlm.h"
#include "inc/models/modeltlm.h"
#include <QtWidgets>

MainWindow::MainWindow(QWidget *parent){
    this->setParent(parent);
    FileReader file("D:\\Project\\ParserFile\\parserFile\\tlm\\2019_01_18_07-01-51.tlm");
    ParserTLM parserTlm(file.getHexString());

    //QTextEdit * text = new QTextEdit(parserTlm.getHexString());
    ModelTlm *model = new ModelTlm(*parserTlm.getBlocks());
    //model->setStringList(QStringList() <<"tfg"<<"tfbt"<<"tbrb"<<"tbrb"<<"tbrb"<<"tbrb");
    QTreeView * trv= new QTreeView();
    trv->setAnimated(true);
    trv->setWordWrap(true);
    trv->setSortingEnabled(true);
    trv->setItemsExpandable(true);
    trv->setAllColumnsShowFocus(true);

    trv->setModel(model->getTlmModel());
    QHBoxLayout *blay = new QHBoxLayout(this);
    //blay->addWidget(text);
    blay->addWidget(trv);
    this->setLayout(blay);
}

MainWindow::~MainWindow(){


}
