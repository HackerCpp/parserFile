#include "inc/mainwindow.h"
#include "inc/filereader.h"
#include "inc/parsers/parsertlm.h"
#include "inc/models/modeltlm.h"
#include <QtWidgets>

MainWindow::MainWindow(QWidget *parent){
    this->setParent(parent);
    FileReader file("D:\\MyQtProgram\\parserGfm\\parserFile\\tlm\\2019_07_01_14-16-31.tlm");
    ParserTLM parserTlm(file.getHexString());

    //QTextEdit * text = new QTextEdit(parserTlm.getHexString());
    ModelTlm *model = new ModelTlm(parserTlm.getBlocks());
    //model->setStringList(QStringList() <<"tfg"<<"tfbt"<<"tbrb"<<"tbrb"<<"tbrb"<<"tbrb");
    QTreeView * trv= new QTreeView();
    trv->setAnimated(true);
    trv->setWordWrap(true);
    trv->setSortingEnabled(true);
    trv->setItemsExpandable(true);
    trv->setAllColumnsShowFocus(true);

    trv->setModel(model);
    QHBoxLayout *blay = new QHBoxLayout(this);
    //blay->addWidget(text);
    blay->addWidget(trv);
    this->setLayout(blay);
}

MainWindow::~MainWindow(){


}
