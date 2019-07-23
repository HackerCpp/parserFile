#include "inc/mainwindow.h"
#include "inc/filereader.h"
#include "inc/parsers/parsertlm.h"
#include "inc/models/modeltlm.h"
#include <QtWidgets>

MainWindow::MainWindow(QWidget *parent){
    this->setParent(parent);
    FileReader file("D:\\geofizics05\\kedr-bin\\data\\2019_06_28_10-03-23.tlm");
    ParserTLM parserTlm(file.getHexString());

    //QTextEdit * text = new QTextEdit(parserTlm.getHexString());
    ModelTlm *model = new ModelTlm();
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
