#include "inc/mainwindow.h"
#include "inc/filereader.h"
#include "inc/parsers/parsertlm.h"
#include "inc/models/modeltlm.h"
#include "inc/parsers/parserDeviceDataTlm.h"
#include <QtWidgets>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent){
    this->setParent(parent);
<<<<<<< HEAD
    FileReader file("D:\\Project\\ParserFile\\parserFile\\tlm\\2019_07_01_14-16-31.tlm");
=======
    FileReader file("D:\\MyQtProgram\\parserGfm\\parserFile\\tlm\\2019_07_25_09-40-06.tlm");
>>>>>>> 4e5b86eab649a5a559c095eadaa52e1bc84af264
    ParserTLM parserTlm(file.getHexString());

    ModelTlm *model = new ModelTlm(parserTlm.getBlocks());
    ParserDeviceDataTlm deviceData(parserTlm.getBlocks());
    QTreeView * trv= new QTreeView();
    trv->setAnimated(true);
    trv->setWordWrap(true);
    trv->setSortingEnabled(true);
    trv->setItemsExpandable(true);
    trv->setAllColumnsShowFocus(true);

    trv->setModel(model);
    QHBoxLayout *blay = new QHBoxLayout(this);
    blay->addWidget(trv);
    this->setLayout(blay);
}

MainWindow::~MainWindow(){


}
