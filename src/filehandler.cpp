#include "inc/filehandler.h"
#include "inc/filereader.h"
#include "inc/parsers/parsertlm.h"
#include "inc/models/modeltlm.h"
#include "inc/parsers/parserDataCm.h"
#include "inc/parsers/parser38k.h"
#include <QSplitter>



FileHandler::FileHandler(QString path,QWidget *parent){
    this->widget = new QWidget();
    this->horBoxLayout = new QHBoxLayout();
    FileReader *file = new FileReader(path);
    if(file->getType() == ".tlm"){
        ParserTLM *parserTlm = new ParserTLM(file->getHexString());
        delete file;
        file = nullptr;
        Parser38k *deviceData = new Parser38k(parserTlm->getBlocks());
        if(deviceData->getProbabilityOfError() > 20){
            delete widget;
            widget = nullptr;
            return;
        }
        delete parserTlm;
        parserTlm = nullptr;
        model = new Model38k(deviceData->getModulesData());
        delete deviceData;
        deviceData = nullptr;
        table = new QTableView();
        textEdit = new QPlainTextEdit();
        textEdit->setFont(QFont("arial",16));
        table->setModel(model);
        QSplitter *sp = new QSplitter(Qt::Horizontal);
        sp->addWidget(table);
        sp->addWidget(textEdit);
        horBoxLayout->addWidget(sp);
        this->widget->setLayout(horBoxLayout);
        QObject::connect(table, SIGNAL(activated(QModelIndex const&)),this, SLOT(showText(QModelIndex const&)));
    }
}
void FileHandler::showText(QModelIndex const& index){
    QString str = this->model->data(model->index(index.row(),11,index.parent())).toString();
    this->textEdit->setPlainText(str);
}
