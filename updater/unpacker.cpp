#include "unpacker.h"
#include <libzippp/libzippp.h>
#include <QDir>
#include <vector>
#include <QVector>
#include <QDebug>
#include <QByteArray>
#include <QFile>

using namespace  libzippp;
using namespace  std;

void Unpacker::unpack(QString file,QString where){
    ZipArchive z1(file.toStdString());
    z1.open(ZipArchive::READ_ONLY);

    QVector<ZipEntry>f_entries =  QVector<ZipEntry>::fromStdVector( z1.getEntries());
    QDir().mkdir(where);
    foreach(auto entry,f_entries){
        QByteArray f_byteArray = QByteArray::fromRawData((char *)z1.readEntry(entry, true),entry.getSize());
        QString f_filePath = where + "/" + QString::fromStdString(entry.getName());
        qDebug() << QString::fromStdString(entry.getName())  << f_filePath << f_byteArray.size();
        if(!QDir().exists(QFileInfo(f_filePath).path()))
            qDebug() << QDir().mkdir(QFileInfo(f_filePath).path()) << QFileInfo(f_filePath).path();
        QFile f_file(f_filePath);

        if(!f_file.open(QIODevice::WriteOnly)){
            qDebug() << "no openn";
            continue;
        }
        f_file.write(f_byteArray);
        f_file.close();
    }


}


