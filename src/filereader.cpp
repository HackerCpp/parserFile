#include "inc/filereader.h"
#include "QMessageBox"


FileReader::FileReader(QString path):m_path(path){
   filestream.setFileName(path);
   this->type = m_path.mid(m_path.indexOf(".",0));
}

QByteArray FileReader::getByteArray(){
   if(!filestream.isOpen())
       if(!filestream.open(QIODevice::ReadOnly)){
           QString mess = "Файл " + m_path + " не может быть открыт. <br>" + filestream.errorString();
           QMessageBox::about(nullptr,"Warning", mess);
           return nullptr;
       }
   QByteArray byteArrayFile = filestream.read(filestream.size());
   filestream.close();
   return byteArrayFile;
}
