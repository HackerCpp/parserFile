#include "unpacker.h"
#include <QDir>
#include <vector>
#include <QVector>
#include <QDebug>
#include <QByteArray>
#include <QFile>
#include <QFileInfo>
#include "customprogressbar.h"
#include "QFileInfo"

#ifdef USE_LIBZIP
#include <libzippp.h>

using namespace  libzippp;
using namespace  std;
#else
#include "private\qzipreader_p.h"
#include "private\qzipwriter_p.h"
#endif



bool Unpacker::unpack(QString file,QString where,bool isDeleted){
#ifdef USE_LIBZIP
    ZipArchive z1(file.toStdString());
    if(!z1.open(ZipArchive::ReadOnly))
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
#else
    QZipReader zip_r(file);
    if (!zip_r.exists())
        return false;
    QVector<QZipReader::FileInfo> f_entries =  zip_r.fileInfoList();
    QDir().mkdir(where);

    CustomProgressBar f_bar;
    qreal f_unitPercent = 100.0 / qreal(f_entries.size());
    qreal f_currentPercent = 0;
    f_bar.setRange(0,100);
    f_bar.setValue(f_currentPercent);

    foreach(auto entry,f_entries){
        f_bar.setText(entry.filePath);
        QString f_filePath = where + "/" + entry.filePath;
        if(entry.isDir){
            QDir().mkpath(f_filePath);
            continue;
        }
        QByteArray f_byteArray = zip_r.fileData(entry.filePath);
        QFile f_file(f_filePath);
        if(!f_file.open(QIODevice::WriteOnly)){
            QFile f_logs("logUpdater.txt");
            if(f_logs.open(QIODevice::Append)){
                f_logs.write((f_filePath + "\n").toLocal8Bit());
                qDebug() << "no open file" << f_filePath;
            }
            f_logs.close();
        }
        f_file.write(f_byteArray);
        f_file.close();

        f_currentPercent += f_unitPercent;
        f_bar.setValue(f_currentPercent);
    }
    f_bar.setText("close");
    f_bar.hide();
    //zip_r.extractAll(where);
    zip_r.close();
    if(isDeleted)
        QFile::remove(file);
#endif
    return true;
}


