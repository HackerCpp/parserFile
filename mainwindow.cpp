#include "mainwindow.h"
#include "filereader.h"
#include "parsertlm.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent){
    FileReader file("D:\\geofizics05\\kedr-bin\\data\\2019_07_01_14-16-31.tlm");
    ParserTLM parserTlm(file.getHexString());

    //const QString str = parserTlm.getHexString();
    QTextEdit * text = new QTextEdit(parserTlm.getHexString());
    //QTextEdit * text1 = new QTextEdit(file.getHexString());
    text->show();
    //text1->show();

}

MainWindow::~MainWindow(){


}
