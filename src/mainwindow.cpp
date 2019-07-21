#include "inc/mainwindow.h"
#include "inc/filereader.h"
#include "inc/parsers/parsertlm.h"
#include "inc/models/modeltlm.h"
#include <QtWidgets>

MainWindow::MainWindow(QWidget *parent){
    this->setParent(parent);
    FileReader file("D:\\Project\\ParserFile\\parserFile\\tlm\\2019_07_01_14-16-31.tlm");
    ParserTLM parserTlm(file.getHexString());

    //QTextEdit * text = new QTextEdit(parserTlm.getHexString());
    ModelTlm *model = new ModelTlm(*parserTlm.getBlocks());
    //model->setStringList(QStringList() <<"tfg"<<"tfbt"<<"tbrb"<<"tbrb"<<"tbrb"<<"tbrb");
    QTreeView * trv= new QTreeView();
    trv->setModel(model->getTlmModel());
    QHBoxLayout *blay = new QHBoxLayout(this);
    //blay->addWidget(text);
    blay->addWidget(trv);
    this->setLayout(blay);
}

MainWindow::~MainWindow(){


}
