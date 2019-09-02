#include "inc/fileCreation/csv.h"
#include "QFileDialog"
#include "QTextDocumentWriter"
#include "QTextEdit"

CSV::CSV(QList<QString> header,QList<QList<QString>> data){

}

CSV::CSV(QList<PacketModulesData38k> *modulesData38k,ushort type){
    foreach(PacketModulesData38k data,modulesData38k){

    }


    QFileDialog fileDialog;
    QTextEdit * ptxt = new QTextEdit();
    ptxt->setFontPointSize(6);
    ptxt->setFontFamily("Courier New");
    QString filePath = fileDialog.getSaveFileName(nullptr, "Save File","C:/","*.csv");
    QTextDocumentWriter writer;
    writer.setFormat("plaintext");
    QString docPath = filePath + ".csv";
    writer.setFileName(docPath);
    bool ok = writer.write(ptxt->document());
    delete ptxt;
}
