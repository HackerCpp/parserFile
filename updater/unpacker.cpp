#include "unpacker.h"
#include <libzippp/libzippp.h>
#include <QDir>
#include <vector>
#include <QVector>
#include <QDebug>
#include <QByteArray>
#include <QFile>
#include "customprogressbar.h"

using namespace  libzippp;
using namespace  std;

bool Unpacker::unpack(QString file,QString where,bool isDeleted){
    ZipArchive z1(file.toStdString());
    if(!z1.open(ZipArchive::READ_ONLY))
        return false;

    QVector<ZipEntry>f_entries =  QVector<ZipEntry>::fromStdVector( z1.getEntries());
    QDir().mkdir(where);

    CustomProgressBar f_bar;
    qreal f_unitPercent = 100.0 / qreal(f_entries.size());
    qreal f_currentPercent = 0;
    f_bar.setRange(0,100);
    f_bar.setValue(f_currentPercent);

    foreach(auto entry,f_entries){
        f_bar.setText(QString::fromStdString(entry.getName()));
        QByteArray f_byteArray = QByteArray::fromRawData((char *)z1.readEntry(entry, true),entry.getSize());
        QString f_filePath = where + "/" + QString::fromStdString(entry.getName());
        if(!QDir().exists(QFileInfo(f_filePath).path()))
            QDir().mkdir(QFileInfo(f_filePath).path());
        QFile f_file(f_filePath);
        if(!f_file.open(QIODevice::WriteOnly)){
            continue;
        }
        f_file.write(f_byteArray);
        f_file.close();
        f_currentPercent += f_unitPercent;
        f_bar.setValue(f_currentPercent);
    }
    f_bar.setText("close");
    f_bar.hide();
    if(isDeleted)
        z1.unlink();
    return true;
}


