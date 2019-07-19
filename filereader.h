#ifndef FILEREADER_H
#define FILEREADER_H

#include <QFile>
#include <QString>
#include <list>
#include <QChar>

using namespace std;

/*!
 * \brief Открывает файл,формирует строку и отправляет в парсер.
 * \author Пряников Алексей Владимирович
 */


class FileReader{
    QFile filestream;
    QString m_path;
    QString hexStringFile;
    QByteArray byteArrayFile;
public:
    FileReader(QString path);
    QString getHexString();
};

#endif // FILEREADER_H
