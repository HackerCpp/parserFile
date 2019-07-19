
#include "filereader.h"


FileReader::FileReader(QString path):m_path(path){
   filestream.setFileName(path);
   filestream.open(QIODevice::ReadOnly);
   this->byteArrayFile = filestream.read(filestream.size());
   filestream.close();
   QString bom = byteArrayFile.mid(0,2).toHex();
   this->hexStringFile = byteArrayFile.toHex();
}
QString FileReader::getHexString(){
    return this->hexStringFile;
}
